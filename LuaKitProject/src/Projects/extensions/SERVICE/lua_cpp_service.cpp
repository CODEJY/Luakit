//
// Created by 吴佳雨 on 2018/11/12.
//
#include "lua_cpp_service.h"
#include "base/threading/thread_restrictions.h"
#include "tools/lua_helpers.h"
#include "JniEnvWrapper.h"
#include "java_weak_ref.h"
#include "common/base_lambda_support.h"
#include "network/async_cgi_task_dispatcher.h"

extern "C" int request(lua_State *L);

static int __newindex(lua_State *L)
{
    BEGIN_STACK_MODIFY(L);
    // Add value to the userdata's environment table.
    lua_getfenv(L, 1);
    lua_insert(L, 2);
    lua_rawset(L, 2);
    END_STACK_MODIFY(L, 0);
    return 0;
}

static int __index(lua_State *L)
{
    BEGIN_STACK_MODIFY(L);
    lua_getfenv(L, -2);
    lua_pushvalue(L, -2);
    lua_rawget(L, 3);
    lua_insert(L, 1);
    lua_settop(L, 1);
    END_STACK_MODIFY(L, 1);
    return 1;
}

static const struct luaL_Reg metaFunctions[] = {
    {"__newindex",__newindex},
    {"__index",__index},
    {NULL, NULL}
};

static const struct luaL_Reg functions[] = {
    {"request", request},
    {NULL, NULL}
};

static bool pushCallback(lua_State *L, const char *callbackName, int tableIndex) {
    lua_getfield(L, tableIndex, callbackName);
    if (lua_isnil(L, -1)) {
        lua_pop(L, 1);
        return false;
    }
    else {
        return true;
    }
}

// lua调用
extern "C"
int request(lua_State *L) {
    BEGIN_STACK_MODIFY(L);

    std::string reqJson = "";
    lua_getfield(L, 1, "reqJson");
    if(!lua_isnil(L, -1)){
        reqJson = luaL_checkstring(L, -1);
    }
    lua_pop(L, 1);

    BusinessThreadID now_thread_identifier;
    BusinessThread::GetCurrentThreadIdentifier(&now_thread_identifier);

    JniEnvWrapper env;
    jclass svcRequester = env->FindClass("com/moschat/mobile/framework/service/jni/LuaSvcPBRequester");
    if (svcRequester == NULL) {
        LOG(WARNING)<<"svcRequester null";
    }
    jobject requesterObject = env->AllocObject(svcRequester);
    requesterObject = env->NewGlobalRef(requesterObject);

    size_t nbytes = sizeof(void *);
    void ** instanceUserdata = (void **)lua_newuserdata(L, nbytes);
    *instanceUserdata = requesterObject;

    luaL_getmetatable(L, LUA_SERVICE_METATABLE_NAME);
    lua_setmetatable(L, -2);

    // give it a nice clean environment
    lua_newtable(L);
    lua_setfenv(L, -2);
    pushStrongUserdataTable(L);
    lua_pushlightuserdata(L, requesterObject);
    lua_pushvalue(L, -3);
    lua_rawset(L, -3);
    lua_pop(L, 1);

    if (pushCallback(L, "onResponse", 1)) {
        lua_setfield(L, -2, "onResponse");
    }
    lua_pop(L, 1);

    //调java请求
    LOG(WARNING)<<"send request";
    jmethodID methodId= env->GetMethodID(svcRequester, "sendRequest", "(JJLjava/lang/String;)V");
    jstring jstr = env->NewStringUTF(reqJson.c_str());
    env->CallVoidMethod(requesterObject, methodId, (jlong)requesterObject, (jlong)now_thread_identifier, jstr);

    END_STACK_MODIFY(L, 0);
    return 0;
}

// 返回内容
extern int responseToLua(uint32_t threadId, jlong task, const std::string& resp) {
    std::string response = resp;
    BusinessThread::PostTask(threadId, FROM_HERE, base::BindLambda([=](){
        lua_State * state = BusinessThread::GetCurrentThreadLuaState();
        JniEnvWrapper env;

        LOG(WARNING)<<"get response";
        BEGIN_STACK_MODIFY(state);

        pushStrongUserdataTable(state);
        lua_pushlightuserdata(state, (jobject)task);
        lua_rawget(state, -2);
        lua_remove(state, -2);//盏顶是userdata
        if (lua_isuserdata(state, -1)) {
            LOG(WARNING)<<"get response userdata";
            lua_getfield(state, -1, "onResponse");//盏顶是onResponse函数

            if (lua_isnil(state, -1)) {
                lua_pop(state, 1);
                LOG(WARNING)<<"get response error:userdata is nil";
            } else {

                //-1 function -2 userdata
                lua_newtable(state);

                //push resp
                lua_pushstring(state, "responseData");
                lua_pushstring(state, response.c_str());
                lua_rawset(state, -3);
                lua_pcall(state, 1, 0, 0);
                LOG(WARNING)<<"set response data to lua";
            }

            lua_pop(state, 1);
            //在强表清除userdata
            pushStrongUserdataTable(state);
            lua_pushlightuserdata(state, (jobject)task);
            lua_pushnil(state);
            lua_rawset(state, -3);
            lua_pop(state, 1);
        } else {
            LOG(WARNING)<<"get response: top is not userdata";
            lua_pop(state, 1);
        }
        env->DeleteGlobalRef((jobject)task);
        END_STACK_MODIFY(state, 0);
    }));
    return 0;
}

/**
 * service请求回调，把message和requestId传递给lua
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_moschat_mobile_framework_service_jni_LuaSvcPBRequester_onResponse(JNIEnv *env, jclass type, jlong requestId, jlong threadId
        ,jstring response) {
        //LOG(WARNING)<<"onResponse";
        const char *charStr = env->GetStringUTFChars(response, JNI_FALSE);
        std::string resp = charStr;
        responseToLua(threadId, requestId, resp);
        env->ReleaseStringUTFChars(response, charStr);
}

extern int luaopen_service(lua_State *L) {
    BEGIN_STACK_MODIFY(L);
    luaL_newmetatable(L, LUA_SERVICE_METATABLE_NAME);
    luaL_register(L, NULL, metaFunctions);
    luaL_register(L, LUA_SERVICE_METATABLE_NAME, functions);
    lua_pushvalue(L, -2);
    lua_setmetatable(L, -2); // Set the metatable for the module
    END_STACK_MODIFY(L, 0);
    return 0;
}