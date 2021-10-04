#include "base_userdata.h"
#include "utils.h"
namespace box2dDefoldNE {

BaseUserData::BaseUserData(const char* userdata_type, void* box2dObj){
    user_data_ref = LUA_REFNIL;
    table_ref = LUA_REFNIL;
    metatable_name = NULL;

    this->box2dObj = box2dObj;
    this->userdata_type = userdata_type;
}

BaseUserData::~BaseUserData() {
    if(user_data_ref != LUA_REFNIL || table_ref != LUA_REFNIL){
        dmLogError("userdata:%s was not free",userdata_type);
    }

    if(box2dObj != NULL){
        dmLogError("userdata:%s  box2dObject was not free",userdata_type);
    }
}

BaseUserData* BaseUserData_get_userdata(lua_State *L, int index, const char *userdata_type) {
    int top = lua_gettop(L);
    BaseUserData *obj = NULL;

    if (lua_istable(L, index)) {
        //1.Check userdata type
        if(userdata_type != NULL){
            lua_getfield(L, index, USERDATA_TYPE);
            if (strcmp(lua_tostring(L, -1), userdata_type) != 0) {
                luaL_error(L, "Need %s. Get %d.", userdata_type, lua_tostring(L, -1));
            }
            lua_pop(L,-1);
        }

        //2.Check userdata
        lua_getfield(L, index, USERDATA_NAME);
        if (lua_islightuserdata(L, -1)) {
            obj = (BaseUserData *)lua_touserdata(L, -1);
            //check cpp box2d object not null
            if(false){
                luaL_error(L, "cpp box2d object in NULL");
            }
        }else{
              luaL_error(L, "userdata in not lightuserdata");
        }
        lua_pop(L, 1);
    }else{
        luaL_error(L, "can't get userdata. variable not table");
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
        utils::unref(L, user_data_ref);
        user_data_ref = LUA_REFNIL;
        utils::unref(L, table_ref);
        table_ref = LUA_REFNIL;
    }
}

}

