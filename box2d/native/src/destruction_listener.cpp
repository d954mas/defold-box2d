#include "destruction_listener.h"
#include "utils.h"
#include "static_hash.h"
#include "joint.h"
#include "fixture.h"

namespace box2dDefoldNE {
LuaDestructionListener::LuaDestructionListener(){
        error = false;
        error_message = NULL;
        fun_say_goodbye_fixture = LUA_REFNIL;
        fun_say_goodbye_joint = LUA_REFNIL;

        defold_script_instance_ref = LUA_REFNIL;
}

LuaDestructionListener::~LuaDestructionListener() {

}

void LuaDestructionListener::InitFromTable(lua_State *L, int index){
    if (lua_istable(L, index)) {
        Destroy(L);//free refs
        lua_pushvalue(L,index);
        /* table is in the stack at index 't' */
        lua_pushnil(L);  /* first key */
        while (lua_next(L, -2) != 0) {
            /* uses 'key' (at index -2) and 'value' (at index -1) */
           // printf("%s - %s\n",lua_tostring(L, -2),lua_tostring(L, -1));
            const char* key = lua_tostring(L, -2);
            switch (hash_string(key)) {
                case HASH_SayGoodbyeFixture:{
                    if(lua_isfunction(L,-1)){
                        lua_pushvalue(L,-1);
                        fun_say_goodbye_fixture = luaL_ref(L,LUA_REGISTRYINDEX);
                    }else{
                        utils::error(L,"SayGoodbyeFixture must be function");
                    }
                    break;
                }
                case HASH_SayGoodbyeJoint:{
                    if(lua_isfunction(L,-1)){
                        lua_pushvalue(L,-1);
                        fun_say_goodbye_joint = luaL_ref(L,LUA_REGISTRYINDEX);
                    }else{
                        utils::error(L,"SayGoodbyeJoint must be function");
                    }
                    break;
                }
                default:
                    luaL_error(L, "unknown key:%s", key);
                    break;
            }
           /* removes 'value'; keeps 'key' for next iteration */
           lua_pop(L, 1);
        }
        if(fun_say_goodbye_fixture == LUA_REFNIL && fun_say_goodbye_joint == LUA_REFNIL){
             dmLogWarning("No functions in destructionListener");
        }
        lua_pop(L,1); //remove table
        dmScript::GetInstance(L);
        defold_script_instance_ref = dmScript::Ref(L, LUA_REGISTRYINDEX);

    }else{
        utils::error(L,"destructionListener should be table");
    }
}

void LuaDestructionListener::Destroy(lua_State *L) {
    utils::unref(L, fun_say_goodbye_fixture);
    utils::unref(L, fun_say_goodbye_joint);
    utils::unref(L, defold_script_instance_ref);

    fun_say_goodbye_fixture = LUA_REFNIL;
    fun_say_goodbye_joint = LUA_REFNIL;
    defold_script_instance_ref = LUA_REFNIL;
}

extern lua_State * GLOBAL_L;

void LuaDestructionListener::SayGoodbye(b2Joint* b2joint){
    if(fun_say_goodbye_joint != LUA_REFNIL){
        lua_rawgeti(GLOBAL_L,LUA_REGISTRYINDEX,fun_say_goodbye_joint);
        Joint *joint = (Joint *)b2joint->GetUserData().pointer;
        joint->Push(GLOBAL_L);
        if (lua_pcall(GLOBAL_L, 1, 0, 0) != 0){
            error = true;
            error_message = lua_tostring(GLOBAL_L,-1);
            lua_pop(GLOBAL_L,1);
        }
    }
}

void LuaDestructionListener::SayGoodbye(b2Fixture* b2fixture){
    if(fun_say_goodbye_fixture != LUA_REFNIL){
        lua_rawgeti(GLOBAL_L,LUA_REGISTRYINDEX,fun_say_goodbye_fixture);
        Fixture *fixture = (Fixture *)b2fixture->GetUserData().pointer;
        fixture->Push(GLOBAL_L);
        if (lua_pcall(GLOBAL_L, 1, 0, 0) != 0){
           error = true;
           error_message = lua_tostring(GLOBAL_L,-1);
           lua_pop(GLOBAL_L,1);
        }
    }
}

}