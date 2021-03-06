extern "C" {
#include "lua.h"
#include "lauxlib.h"
}

#if defined(OS_ANDROID)
#include "tools/lua_helpers.h"
#else
#include <LuakitPod/lua_helpers.h>
#endif

#include "lua_yoga.h"
#include "luaYogaBridge.h"

#if defined(OS_ANDROID)
#include "base/logging.h"
#else
#include <LuakitPod/logging.h>
#endif

#include <vector>
#include <string>
#include <tuple>





enum ActionType {
    ACTION_NONE,
    ADD_VIEW,
    LIST_RELOAD,
    VIEW_RELOAD_YOGA,
    VIEW_REMOVE_FROM_PARENT,
};

static void addYogaEnum(lua_State *L);

static std::vector<float> process_Color(lua_State *L);

struct YogaFunction {
    void * view;
    YogaType type;
    ActionType action;
    void * root;
};


static LuaModel getValueFromState(lua_State *state,LuaValueType valueType, std::string luaKey){
    struct LuaModel result;
    result.type = valueType;

    
    switch (valueType) {
        case Value_String:{
            lua_pushstring(state, luaKey.c_str());
            lua_rawget(state,-2);
            if (!lua_isnil(state, -1)) {
                result.value_string = lua_tostring(state, -1);
            }else{
                result.value_string = "";
            }
            lua_pop(state, 1);
        }
            break;
        case Value_Number:{
            lua_pushstring(state, luaKey.c_str());
            lua_rawget(state, -2);
            if (!lua_isnil(state, -1)) {
                result.value_float = lua_tonumber(state, -1);
            }else{
                result.value_float = (luaKey == "a")?1:0;
            }
            lua_pop(state, 1);
        }
            break;
        case Value_Boolean:{
            lua_pushstring(state, luaKey.c_str());
            lua_rawget(state, -2);
            
            result.value_bool = lua_toboolean(state, -1);

            lua_pop(state, 1);
        }
            break;
        default:
            break;
    }
    
    return result;
    
}

static std::tuple<std::string, std::string> process_ImageTable(lua_State *L){
    
    typedef std::tuple<std::string, std::string> ImageTuple;
    
    std::string imageName_normal = getValueFromState(L, Value_String, "imageName").value_string;
    std::string imageName_highlighted = getValueFromState(L, Value_String, "imageName_hl").value_string;
    
    ImageTuple tuple(imageName_normal, imageName_highlighted);
    
    return tuple;
}


static std::vector<float> process_Color(lua_State *L){
    std::vector<float> color;
    
    color.push_back(getValueFromState(L, Value_Number, "r").value_float);
    color.push_back(getValueFromState(L, Value_Number, "g").value_float);
    color.push_back(getValueFromState(L, Value_Number, "b").value_float);
    color.push_back(getValueFromState(L, Value_Number, "a").value_float);
    
    
    return color;
}

static int __yogaViewNewIndex(lua_State *L)
{
    BEGIN_STACK_MODIFY(L);
    YogaInfo *viewInfo = (YogaInfo *)luaL_checkudata(L, 1, LUA_YOGA_VIEW_METATABLE_NAME);
    if (!viewInfo->isDead) {
        std::string name = lua_tostring(L, 2);
        
        if (name == BACKGROUND_COLOR)
        {
            std::vector<float> color = process_Color(L);
            setBackgroundColor(viewInfo->view, color[0], color[1], color[2], color[3]);
        }
        else if(name == YOGA_IS_ENABLE) {
            bool b = lua_toboolean(L, -1);
            setYogaProperty(viewInfo->view, viewInfo->type ,name, b);
        }
        else if (name == ImageView_Name){
            
            std::string c_imageName =  lua_tostring(L, -1);
            
            setImageName(viewInfo->view, c_imageName);
            
        }
        else if (name == ImageView_Path){
            std::string c_imagePath = lua_tostring(L, -1);
            
            setImagePath(viewInfo->view, c_imagePath);
            
        }
        else if (name == ImageView_Name_HL){
            
            std::string c_imageName =  lua_tostring(L, -1);
            
            setImageName_hl(viewInfo->view, c_imageName);
            
        }
        else if (name == ImageView_ContentMode){
            
            long contentMode  =  lua_tointeger(L, -1);
            
            setImageViewContentMode(viewInfo->view, contentMode);
            
        }
        else if (name == ImageView_Image){
            
            std::tuple<std::string, std::string> imageTuble = process_ImageTable(L);
            
            setImageTable(viewInfo->view,
                          std::get<0>(imageTuble),
                          std::get<1>(imageTuble));
            
        }
        else if (name == ImageView_ColorImage){
            std::vector<float> color ;
            std::vector<float> color_gl ;

            lua_pushstring(L, "color");
            lua_rawget(L, -2);
            if (!lua_isnil(L, -1)) {
                color = process_Color(L);
            }
            lua_pop(L, 1);
            
            lua_pushstring(L, "color_hl");
            lua_rawget(L, -2);
            if (!lua_isnil(L, -1)) {
                color_gl = process_Color(L);
            }
            lua_pop(L, 1);
            
            setImageColorTable(viewInfo->view,color,color_gl); 

        }else if (name == Text_Table){
            
            std::string fontSize = "fontSize";
            std::string isBold = "isBold";
            std::string alignment = "alignment";
            std::string numberOfLines = "numberOfLines";
            std::string fontName = "fontName";

            long textFontSize = getValueFromState(L, Value_Number, fontSize).value_float;
            bool textBold = getValueFromState(L, Value_Boolean, isBold).value_bool;
            long textAlignment = getValueFromState(L, Value_Number, alignment).value_float;
            long lines = getValueFromState(L, Value_Number, numberOfLines).value_float;
            std::string textFontName = getValueFromState(L, Value_String, fontName).value_string;
            
            std::vector<float> color ;
            std::vector<float> color_gl ;
            
            lua_pushstring(L, "color");
            lua_rawget(L, -2);
            if (!lua_isnil(L, -1)) {
                color = process_Color(L);
                setTextColor(viewInfo->view, color);
            }
            lua_pop(L, 1);
            
            lua_pushstring(L, "color_hl");
            lua_rawget(L, -2);
            if (!lua_isnil(L, -1)) {
                color_gl = process_Color(L);
                setTextHighlightedColor(viewInfo->view, color_gl);
            }
            lua_pop(L, 1);

            if (textFontSize > 0) {
                setTextFont(viewInfo->view,getValueFromState(L,Value_String,textFontName).value_string ,textFontSize, textBold);
            }
            
            if (textAlignment >= 0) {
                setTextAlignment(viewInfo->view, textAlignment);
            }
            
            setTextNumberOfLines(viewInfo->view, lines);
            
        }else if (name == Text_NumberOfLines){
            long numberOfLines =lua_tointeger(L, -1);
            setTextNumberOfLines(viewInfo->view, numberOfLines);
        }
        else if (name == View_Cliping){
            
            long isCliping  =  lua_tointeger(L, -1);
            
            setCliping(viewInfo->view, isCliping);
            
        }else if (name == Text_Alignment){
            
            long alignment  =  lua_tointeger(L, -1);
            
            setTextAlignment(viewInfo->view, alignment);
            
        }else if (name == Text_Text){
            
            std::string contentText  =  lua_tostring(L, -1);
            
            setText(viewInfo->view, contentText);
            
        }else if (name == Text_TextColor){
            
            std::vector<float> color ;
            std::vector<float> color_gl ;

            lua_pushstring(L, "color");
            lua_rawget(L, -2);
            if (!lua_isnil(L, -1)) {
                color = process_Color(L);
                setTextColor(viewInfo->view, color);
            }
            lua_pop(L, 1);
            
            
            
        }else if (name == Text_TextFont){
            std::string fontName = "fontName";

            long fontSize =  lua_tointeger(L, -1);

            setTextFont(viewInfo->view,getValueFromState(L,Value_String,fontName).value_string,fontSize, 0);
            
            
        }else if (name == View_Highlighted){
            
            long isHighlighted  =  lua_tointeger(L, -1);
            
            setHighlighted(viewInfo->view, isHighlighted);
            
        }else if (name == View_CornerRadius){

            long cornerRadius  =  lua_tointeger(L, -1);

            setViewCornerRadius(viewInfo->view, cornerRadius);
            
        }else if (name == List_SeperatorColor){
            std::vector<float> color = process_Color(L);
 
            
            setListSeperatorColor(viewInfo->view, color[0], color[1], color[2], color[3]);
            
        } else if (name == TAP_FUNCTION){
            addTapGesture(viewInfo->view, viewInfo->root);
            lua_getfenv(L, 1);
            lua_insert(L, 2);
            lua_rawset(L, 2);
        } else if (name == LONGPRESS_FUNCTION){
            addLongPressGesture(viewInfo->view, viewInfo->root);
            lua_getfenv(L, 1);
            lua_insert(L, 2);
            lua_rawset(L, 2);
        }
        
        else {
            float value = lua_tonumber(L, -1);
            bool hasSetProperty = setYogaProperty(viewInfo->view, viewInfo->type ,name, value);
            if (!hasSetProperty) {
                LOG(WARNING)<<" set table env"<<name<<"--"<<viewInfo;
                lua_getfenv(L, 1);
                lua_insert(L, 2);
                lua_rawset(L, 2);
            }
        }
    }
    END_STACK_MODIFY(L, 0);
    return 0;
}

static void processUserData(lua_State *state,
                            YogaInfo *viewInfo,
                            YogaType type,
                            ActionType actionType,
                            bool isDead){
    size_t nbytes = sizeof(YogaFunction);
    YogaFunction *yf = (YogaFunction *)lua_newuserdata(state, nbytes);
    luaL_getmetatable(state, LUA_YOGA_FUNCTION_METATABLE_NAME);
    lua_setmetatable(state, -2);
    yf->view = viewInfo->view;
    yf->type = type;
    yf->root = viewInfo->root;
    yf->action = actionType;
    viewInfo->isDead = isDead;
}

static int __yogaViewIndex(lua_State *L)
{
    BEGIN_STACK_MODIFY(L);
    YogaInfo *viewInfo = (YogaInfo *)luaL_checkudata(L, 1, LUA_YOGA_VIEW_METATABLE_NAME);
    std::string name = lua_tostring(L, 2);
    
    if (!viewInfo->isDead) {
        if(name == ADD_CONTAINER){
            
            processUserData(L, viewInfo, CONTAINER,ADD_VIEW,false);
        }
        else if(name == ADD_ListView){
            
            processUserData(L, viewInfo, LIST,ADD_VIEW,false);
        }
        else if(name == ADD_CollectionView){
            
            processUserData(L, viewInfo, COLLECTIONVIEW,ADD_VIEW,false);

        }else if (name == RELOAD_YOGA){
            
            processUserData(L, viewInfo, OTHER,VIEW_RELOAD_YOGA,false);

        }
        else if (name == REMOVE_FROM_PARENT){
            
             processUserData(L, viewInfo, OTHER,VIEW_REMOVE_FROM_PARENT,true);
            
        }
        else if(name == ADD_ImageView){
            
            processUserData(L, viewInfo, IMAGE,ADD_VIEW,false);
        }
        else if(name == ADD_TEXT){
            
            processUserData(L, viewInfo, TEXT,ADD_VIEW,false);

        }
        else if(name == List_Reload){
            
            processUserData(L, viewInfo, OTHER,LIST_RELOAD,false);

        }
        else if (name == WIDTH ||
                 name == HEIGHT){
            float ret = getYogaProperty(viewInfo->view, viewInfo->type, name);
            lua_pushnumber(L, ret);
        }
        else if (name == IS_DEAD){
            lua_pushboolean(L, viewInfo->isDead);
        }
        else {
            lua_getfenv(L, -2);
            LOG(WARNING)<<" get table env"<<lua_tostring(L, -2) <<"--"<<viewInfo;;
            lua_pushvalue(L, -2);
            lua_rawget(L, 3);
        }
    } else {
        if(name == ADD_CONTAINER 
            || name == ADD_ListView 
            || name == ADD_ImageView 
            || name == ADD_TEXT
            || name == ADD_CollectionView
            || name == RELOAD_YOGA
            || name == REMOVE_FROM_PARENT
            || name == List_Reload
            ){
            size_t nbytes = sizeof(YogaFunction);
            YogaFunction *yf = (YogaFunction *)lua_newuserdata(L, nbytes);
            luaL_getmetatable(L, LUA_YOGA_FUNCTION_METATABLE_NAME);
            lua_setmetatable(L, -2);
            yf->view = NULL;
        } else {
            lua_pushnumber(L, 0);
        }
    }
    END_STACK_MODIFY(L, 1)
    return 1;
}

static int __yogaFuncCall(lua_State *L)
{
    BEGIN_STACK_MODIFY(L);
    YogaFunction *yf = (YogaFunction *)luaL_checkudata(L, 1, LUA_YOGA_FUNCTION_METATABLE_NAME);
    if(yf->view != NULL){
        if (yf->action == ADD_VIEW) {
            void * root = NULL;
            if (yf->root != NULL) {
                root = yf->root;
            } else {
                root = yf->view;
            }
            void * child = addView(yf->view, yf->type, root);
            size_t nbytes = sizeof(YogaInfo);
            YogaInfo *yi = (YogaInfo *)lua_newuserdata(L, nbytes);
            luaL_getmetatable(L, LUA_YOGA_VIEW_METATABLE_NAME);
            lua_setmetatable(L, -2);
            
            lua_newtable(L);
            lua_setfenv(L, -2);

            yi->view = child;
            yi->type = yf->type;
            yi->isDead = false;
            yi->root = root;
            pushUserdataInStrongTable(L,yi->root);
            lua_pushlightuserdata(L, child);
            lua_pushvalue(L, -3);
            lua_rawset(L, -3);
            lua_pop(L, 1);
        } else if(yf->action == LIST_RELOAD){
            listReload(yf->view);
            lua_pushnil(L);
        } else if(yf->action == VIEW_RELOAD_YOGA){
            reloadYoga(yf->view);
            lua_pushnil(L);
        } else if(yf->action == VIEW_REMOVE_FROM_PARENT){
            removeFromParent(yf->view);
            lua_pushnil(L);
        }
    } else {
        lua_pushnil(L);
    }
    END_STACK_MODIFY(L, 1)
    return 1;
}

static const struct luaL_Reg yogaViewMetaFunctions[] = {
    {"__newindex",__yogaViewNewIndex},
    {"__index",__yogaViewIndex},
    {NULL, NULL}
};

static const struct luaL_Reg yogaViewFunctions[] = {
    {NULL, NULL}
};

static const struct luaL_Reg yogaFuncMetaFunctions[] = {
    {"__call",__yogaFuncCall},
    {NULL, NULL}
};

static const struct luaL_Reg yogaFuncFunctions[] = {
    {NULL, NULL}
};

extern int luaopen_yoga(lua_State *L) {
    BEGIN_STACK_MODIFY(L);
    luaL_newmetatable(L, LUA_YOGA_VIEW_METATABLE_NAME);
    luaL_register(L, NULL, yogaViewMetaFunctions);
    luaL_register(L, LUA_YOGA_VIEW_METATABLE_NAME, yogaViewFunctions);
    lua_pushvalue(L, -2);
    lua_setmetatable(L, -2);
    addYogaEnum(L);
    END_STACK_MODIFY(L, 0)
    return 0;
}

extern int luaopen_yoga_func(lua_State *L) {
    BEGIN_STACK_MODIFY(L);
    luaL_newmetatable(L, LUA_YOGA_FUNCTION_METATABLE_NAME);
    luaL_register(L, NULL, yogaFuncMetaFunctions);
    luaL_register(L, LUA_YOGA_FUNCTION_METATABLE_NAME, yogaFuncFunctions);
    lua_pushvalue(L, -2);
    lua_setmetatable(L, -2);
    END_STACK_MODIFY(L, 0)
    return 0;
}

extern int heightForTextTable(lua_State *L) {
    BEGIN_STACK_MODIFY(L);
    
    std::string text = getValueFromState(L, Value_String, "text").value_string;
   
    std::string fontName = getValueFromState(L, Value_String, "fontName").value_string;
    
    float textFontSize = getValueFromState(L, Value_Number, "fontSize").value_float;
    
    float textWidth = getValueFromState(L, Value_Number, "textWidth").value_float;

    float result = heightForTextTable(text, textWidth, textFontSize, fontName);
    
    lua_pushnumber(L, result);
    
    END_STACK_MODIFY(L, 1)
    
    return 1;
}

extern int goFlutter(lua_State *L) {
    BEGIN_STACK_MODIFY(L);
    
    std::string module = lua_tostring(L, 1);
    
    int number = lua_gettop(L);

    if (number == 4) {
        std::string version = lua_tostring(L, 2);
        
        std::string type = lua_tostring(L, 3);

        std::string url = lua_tostring(L, 4);

        goFlutter(module, version, type, url);
    } else if (number == 3) {
        std::string version = lua_tostring(L, 2);
        
        std::string type = lua_tostring(L, 3);
        
        goFlutter(module, version, type, "");
        
    } else if (number == 2) {
        
        std::string version = lua_tostring(L, 2);
        
        goFlutter(module, version, "flutter", "");
        
    } else {
        goFlutter(module, "", "flutter", "");
    }
    
    
    
    END_STACK_MODIFY(L, 0)
    
    return 0;
}

extern int widthForTextTable(lua_State *L) {
    BEGIN_STACK_MODIFY(L);
    
    std::string text = getValueFromState(L, Value_String, "text").value_string;
    
    std::string fontName = getValueFromState(L, Value_String, "fontName").value_string;
    
    float textHeight = getValueFromState(L, Value_Number, "textHeight").value_float;
    
    float textFontSize = getValueFromState(L, Value_Number, "textFontSize").value_float;
    
    float result = widthForTextTable(text, textHeight, textFontSize, fontName);
    
    lua_pushnumber(L, result);
    
    END_STACK_MODIFY(L, 1)
    
    return 1;
}


extern int showToast(lua_State *state) {
    
    BEGIN_STACK_MODIFY(state);
   
    showToast(lua_tostring(state, -1));
    
    END_STACK_MODIFY(state, 0)
    
    return 0;
}

extern void callbackToYoga(int type, void * v) {
    if (type == 0) {
        onTapGesture(v);
    } else if (type == 1) {
        onLongPressGesture(v);
    }
}

static void addYogaEnum(lua_State *L) {
    //    YGAlign
    lua_pushinteger(L, 0);
    lua_setglobal(L, "YGAlignAuto");
    lua_pushinteger(L, 1);
    lua_setglobal(L, "YGAlignFlexStart");
    lua_pushinteger(L, 2);
    lua_setglobal(L, "YGAlignCenter");
    lua_pushinteger(L, 3);
    lua_setglobal(L, "YGAlignFlexEnd");
    lua_pushinteger(L, 4);
    lua_setglobal(L, "YGAlignStretch");
    lua_pushinteger(L, 5);
    lua_setglobal(L, "YGAlignBaseline");
    lua_pushinteger(L, 6);
    lua_setglobal(L, "YGAlignSpaceBetween");
    lua_pushinteger(L, 7);
    lua_setglobal(L, "YGAlignSpaceAround");
    
    //    YGDirection
    lua_pushinteger(L, 0);
    lua_setglobal(L, "YGDirectionInherit");
    lua_pushinteger(L, 1);
    lua_setglobal(L, "YGDirectionLTR");
    lua_pushinteger(L, 2);
    lua_setglobal(L, "YGDirectionRTL");
    
    //    YGDisplay
    lua_pushinteger(L, 0);
    lua_setglobal(L, "YGDisplayFlex");
    lua_pushinteger(L, 1);
    lua_setglobal(L, "YGDisplayNone");
    
    //    YGFlexDirection
    lua_pushinteger(L, 0);
    lua_setglobal(L, "YGFlexDirectionColumn");
    lua_pushinteger(L, 1);
    lua_setglobal(L, "YGFlexDirectionColumnReverse");
    lua_pushinteger(L, 2);
    lua_setglobal(L, "YGFlexDirectionRow");
    lua_pushinteger(L, 3);
    lua_setglobal(L, "YGFlexDirectionRowReverse");
    
    //    YGJustify
    lua_pushinteger(L, 0);
    lua_setglobal(L, "YGJustifyFlexStart");
    lua_pushinteger(L, 1);
    lua_setglobal(L, "YGJustifyCenter");
    lua_pushinteger(L, 2);
    lua_setglobal(L, "YGJustifyFlexEnd");
    lua_pushinteger(L, 3);
    lua_setglobal(L, "YGJustifySpaceBetween");
    lua_pushinteger(L, 4);
    lua_setglobal(L, "YGJustifySpaceAround");
    lua_pushinteger(L, 5);
    lua_setglobal(L, "YGJustifySpaceEvenly");
    
    //    YGPositionType
    lua_pushinteger(L, 0);
    lua_setglobal(L, "YGPositionTypeRelative");
    lua_pushinteger(L, 1);
    lua_setglobal(L, "YGPositionTypeAbsolute");
    
    //    YGWrap
    lua_pushinteger(L, 0);
    lua_setglobal(L, "YGWrapNoWrap");
    lua_pushinteger(L, 1);
    lua_setglobal(L, "YGWrapWrap");
    lua_pushinteger(L, 2);
    lua_setglobal(L, "YGWrapWrapReverse");
    
    //    YGOverflow
    lua_pushinteger(L, 0);
    lua_setglobal(L, "YGOverflowVisible");
    lua_pushinteger(L, 1);
    lua_setglobal(L, "YGOverflowHidden");
    lua_pushinteger(L, 2);
    lua_setglobal(L, "YGOverflowScroll");
    
    //    TextAlignment
    lua_pushinteger(L, 0);
    lua_setglobal(L, "TextAlignmentLeft");
    lua_pushinteger(L, 1);
    lua_setglobal(L, "TextAlignmentCenter");
    lua_pushinteger(L, 2);
    lua_setglobal(L, "TextAlignmentRight");
    
    //    ContentMode
    lua_pushinteger(L, 0);
    lua_setglobal(L, "ContentModeScaleToFill");//android fix_xy
    lua_pushinteger(L, 1);
    lua_setglobal(L, "ContentModeScaleAspectFit");//android center_inside
    lua_pushinteger(L, 2);
    lua_setglobal(L, "ContentModeScaleAspectFill");//android center
    lua_pushinteger(L, 4);
    lua_setglobal(L, "ContentModeCenter");//android center_crop
    lua_pushinteger(L, 9);
    lua_setglobal(L, "ContentModeTopLeft");//android matrix
    
    lua_pushcfunction(L, heightForTextTable);
    lua_setglobal(L, "heightForTextTable");

    lua_pushcfunction(L, widthForTextTable);
    lua_setglobal(L, "widthForTextTable");
    
    lua_pushcfunction(L, showToast);
    lua_setglobal(L, "showToast");

    lua_pushcfunction(L, goFlutter);
    lua_setglobal(L, "goFlutter");
}
