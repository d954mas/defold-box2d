#include "contact_listener.h"
#include "utils.h"
#include "static_hash.h"
#include "contact.h"
#include "manifold.h"
namespace box2dDefoldNE {
LuaContactListener::LuaContactListener(){
        error = false;
        error_message = NULL;
        fun_begin_contact_ref = LUA_REFNIL;
        fun_end_contact_ref = LUA_REFNIL;
        fun_preSolve_contact_ref = LUA_REFNIL;
        fun_postSolve_contact_ref = LUA_REFNIL;
        defold_script_instance_ref = LUA_REFNIL;
}

LuaContactListener::~LuaContactListener() {

}

void LuaContactListener::InitFromTable(lua_State *L, int index){
    if (lua_istable(L, index)) {
        lua_pushvalue(L,index);
        /* table is in the stack at index 't' */
        lua_pushnil(L);  /* first key */
        while (lua_next(L, -2) != 0) {
            /* uses 'key' (at index -2) and 'value' (at index -1) */
           // printf("%s - %s\n",lua_tostring(L, -2),lua_tostring(L, -1));
            const char* key = lua_tostring(L, -2);
            switch (hash_string(key)) {
                case HASH_BeginContact:{
                    if(lua_isfunction(L,-1)){
                        lua_pushvalue(L,-1);
                        fun_begin_contact_ref = luaL_ref(L,LUA_REGISTRYINDEX);
                    }else{
                        utils::error(L,"BeginContact must be function");
                    }
                    break;
                }
                case HASH_EndContact:{
                    if(lua_isfunction(L,-1)){
                        lua_pushvalue(L,-1);
                        fun_end_contact_ref = luaL_ref(L,LUA_REGISTRYINDEX);
                    }else{
                        utils::error(L,"EndContact must be function");
                    }
                    break;
                }
                case HASH_PreSolve:{
                    if(lua_isfunction(L,-1)){
                        lua_pushvalue(L,-1);
                        fun_preSolve_contact_ref = luaL_ref(L,LUA_REGISTRYINDEX);
                    }else{
                        utils::error(L,"PreSolve must be function");
                    }
                    break;
                }
                case HASH_PostSolve:{
                    if(lua_isfunction(L,-1)){
                        lua_pushvalue(L,-1);
                        fun_postSolve_contact_ref = luaL_ref(L,LUA_REGISTRYINDEX);
                    }else{
                        utils::error(L,"PostSolve must be function");
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
        if(fun_postSolve_contact_ref == LUA_REFNIL && fun_end_contact_ref == LUA_REFNIL
            && fun_preSolve_contact_ref == LUA_REFNIL && fun_postSolve_contact_ref == LUA_REFNIL){
             dmLogWarning("No functions in contactListener");
        }
        lua_pop(L,1); //remove table
        
        dmScript::GetInstance(L);
        defold_script_instance_ref = dmScript::Ref(L, LUA_REGISTRYINDEX);

    }else{
        utils::error(L,"contactListener should be table");
    }
}

void LuaContactListener::Destroy(lua_State *L) {
    utils::unref(L, fun_begin_contact_ref);
    utils::unref(L, fun_end_contact_ref);
    utils::unref(L, fun_preSolve_contact_ref);
    utils::unref(L, fun_postSolve_contact_ref);
    utils::unref(L, defold_script_instance_ref);

    fun_begin_contact_ref = LUA_REFNIL;
    fun_end_contact_ref = LUA_REFNIL;
    fun_preSolve_contact_ref = LUA_REFNIL;
    fun_postSolve_contact_ref = LUA_REFNIL;
    defold_script_instance_ref = LUA_REFNIL;

    delete this;
}

void LuaContactListener::EndListen(lua_State *L){

}


void LuaContactListener::BeginContact(b2Contact *contact){
    if(!error && fun_begin_contact_ref != LUA_REFNIL){
        lua_rawgeti(L,LUA_REGISTRYINDEX,fun_begin_contact_ref);
        Contact_from_b2Contact(contact)->Push(L);
        if (lua_pcall(L, 1, 0, 0) != 0){
             error = true;
             error_message = lua_tostring(L,-1);
             lua_pop(L,1);
        }
    }
}

void LuaContactListener::EndContact(b2Contact *contact){
    if(!error && fun_end_contact_ref != LUA_REFNIL){
        lua_rawgeti(L,LUA_REGISTRYINDEX,fun_end_contact_ref);
        Contact_from_b2Contact(contact)->Push(L);
        if (lua_pcall(L, 1, 0, 0) != 0){
             error = true;
             error_message = lua_tostring(L,-1);
             lua_pop(L,1);
        }
    }
}

void LuaContactListener::PreSolve(b2Contact *contact, const b2Manifold *old_manifold){
    if(!error && fun_preSolve_contact_ref != LUA_REFNIL){
        lua_rawgeti(L,LUA_REGISTRYINDEX,fun_preSolve_contact_ref);
        Contact_from_b2Contact(contact)->Push(L);
        manifold_to_table(L, old_manifold);
        if (lua_pcall(L, 2, 0, 0) != 0){
             error = true;
             error_message = lua_tostring(L,-1);
             lua_pop(L,1);
        }
    }
}

void LuaContactListener::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse){
    if(!error && fun_postSolve_contact_ref != LUA_REFNIL){
        lua_rawgeti(L,LUA_REGISTRYINDEX,fun_postSolve_contact_ref);
        Contact_from_b2Contact(contact)->Push(L);
        contact_impulse_to_table(L, impulse);
        if (lua_pcall(L, 2, 0, 0) != 0){
             error = true;
             error_message = lua_tostring(L,-1);
             lua_pop(L,1);
        }
    }
}
}