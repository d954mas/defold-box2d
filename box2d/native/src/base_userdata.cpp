#include "base_userdata.h"
#include "utils.h"

#define USERDATA_NAME "__userdata_box2d"
#define USERDATA_TYPE "__userdata_type_box2d"

namespace box2dDefoldNE {

BaseUserData::BaseUserData(const char* userdata_type){
    table_ref = LUA_REFNIL;
    metatable_name = NULL;
    box2dObj = NULL;

    this->userdata_type = userdata_type;
}

BaseUserData::~BaseUserData() {
    if(table_ref != LUA_REFNIL){
        dmLogError("userdata:%s was not free",userdata_type);
    }

    if(box2dObj != NULL){
        dmLogError("userdata:%s  box2dObject was not free",userdata_type);
    }
}

BaseUserData* BaseUserData_get_userdata(lua_State *L, int index, char *userdata_type) {
    int top = lua_gettop(L);
    BaseUserData *obj = NULL;

    if (lua_istable(L, index)) {
        //1.Check userdata type
        if(userdata_type != NULL){
            lua_getfield(L, index, USERDATA_TYPE);
            if(!lua_isstring(L,-1)){
                 luaL_error(L, "unknown userdata type. Need %s. Get %s", userdata_type, lua_tostring(L, -1));
            }else{
                const char* str = lua_tostring(L, -1);
                if (strcmp(lua_tostring(L, -1), userdata_type) != 0) {
                    luaL_error(L, "Need %s. Get %s.", userdata_type, lua_tostring(L, -1));
                }
            }
            lua_pop(L,1);
        }

        //2.Check userdata
        lua_getfield(L, index, USERDATA_NAME);
        if (lua_islightuserdata(L, -1)) {
            obj = (BaseUserData *)lua_touserdata(L, -1);
            //check cpp box2d object not null
            if(obj->box2dObj == NULL){
                luaL_error(L, "%s box2d object is NULL", userdata_type);
            }
        }else if(lua_isnil(L,-1)){
             luaL_error(L, "%s was destroyed",userdata_type);
        }else{
              luaL_error(L, "userdata:%s is not lightuserdata or nil",userdata_type);
        }
        lua_pop(L, 1);
    }else{
        luaL_error(L, "can't get %s. Need table get:%s",userdata_type, lua_typename(L, lua_type(L, index)));
    }

    assert(top == lua_gettop(L));
	return obj;
}

void BaseUserData::Push(lua_State *L) {
     DM_LUA_STACK_CHECK(L, 1);

    if(table_ref == LUA_REFNIL){
        lua_createtable(L, 0, 1);
        // table.__userdata_box2d = userdata
        lua_pushlightuserdata(L, this);
        lua_setfield(L, -2, USERDATA_NAME);

        lua_pushstring(L, this->userdata_type);
        lua_setfield(L, -2, USERDATA_TYPE);

        if(metatable_name != NULL){
            luaL_getmetatable(L, metatable_name);
            lua_setmetatable(L, -2);
        }
        //safe ref
        lua_pushvalue(L, -1);
        table_ref = luaL_ref(L,LUA_REGISTRYINDEX);
     }else{
        lua_rawgeti(L,LUA_REGISTRYINDEX,table_ref);
     }
}

void BaseUserData::Destroy(lua_State *L) {
    if(box2dObj != NULL){
        box2dObj = NULL;
    }

    if(table_ref != LUA_REFNIL){
        lua_rawgeti(L,LUA_REGISTRYINDEX,table_ref);

        lua_pushnil(L);
        lua_setfield(L, -2, USERDATA_NAME);

        //do not delete type. Use type for error message when call deleted object
      //  lua_pushnil(L);
      //  lua_setfield(L, -2, USERDATA_TYPE);

        lua_pop(L,1);

        utils::unref(L, table_ref);
        table_ref = LUA_REFNIL;
    }

}

}

