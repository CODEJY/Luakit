//
// Created by 吴佳雨 on 2018/11/12.
//

#include "jni.h"
#include <string>
#pragma once
extern "C" {
#include "lua.h"
#include "lauxlib.h"
}
#define LUA_SERVICE_METATABLE_NAME "lua_service"

extern int luaopen_service(lua_State* L);

extern int responseToLua(uint32_t threadId, jlong task, const std::string& resp);

extern "C"
JNIEXPORT void JNICALL
Java_com_moschat_mobile_framework_service_LuaSvcPBRequester_onResponse(JNIEnv *env, jclass type, jlong requestId, jlong threadId
        ,jstring response);