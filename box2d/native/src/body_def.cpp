#include "body_def.h"
#include "utils.h"
#include <extra_utils.h>
#include <static_hash.h>
namespace box2dDefoldNE {
b2BodyDef b2BodyDef_from_table(lua_State *L, int index){
    b2BodyDef def;
    if (lua_istable(L, index)) {
        lua_pushvalue(L,index);
        /* table is in the stack at index 't' */
         lua_pushnil(L);  /* first key */
         while (lua_next(L, -2) != 0) {
           /* uses 'key' (at index -2) and 'value' (at index -1) */
            //printf("%s - %s\n",lua_tostring(L, -2),lua_tostring(L, -1));
            const char* key = lua_tostring(L, -2);
            switch (hash_string(key)) {
                case HASH_type:
                     def.type =  static_cast<b2BodyType>(lua_tonumber(L, -1));
                     break;
                case HASH_position:
                    def.position = extra_utils::get_b2vec_safe(L,-1,"position not vector3");
                    break;
                case HASH_angle:
                    def.angle = lua_tonumber(L, -1);
                    break;
                case HASH_linearVelocity:
                   def.linearVelocity = extra_utils::get_b2vec_safe(L,-1,"linearVelocity not vector3");
                   break;
                case HASH_angularVelocity:
                    def.angularVelocity =  lua_tonumber(L, -1);
                    break;
                case HASH_linearDamping:
                    def.linearDamping =  lua_tonumber(L, -1);
                    break;
                case HASH_angularDamping:
                    def.angularDamping =  lua_tonumber(L, -1);
                    break;
                case HASH_allowSleep:
                    def.allowSleep =  lua_toboolean(L, -1);
                    break;
                case HASH_awake:
                    def.awake =  lua_toboolean(L, -1);
                    break;
                case HASH_fixedRotation:
                    def.fixedRotation =  lua_toboolean(L, -1);
                    break;
                case HASH_bullet:
                    def.bullet =  lua_toboolean(L, -1);
                    break;
                case HASH_enabled:
                    def.enabled =  lua_toboolean(L, -1);
                    break;
                case HASH_userData:
                    if (lua_istable(L ,-1)) {
                        lua_pushvalue(L, -1);
                        def.userData.pointer = luaL_ref(L,LUA_REGISTRYINDEX);
                    }else{
                        utils::error(L,"userdata can be only table or nil");
                    }
                    break;
                case HASH_gravityScale:
                    def.gravityScale =  lua_tonumber(L, -1);
                    break;
                default:
                    luaL_error(L, "unknown key:%s", key);
                    break;
            }
           /* removes 'value'; keeps 'key' for next iteration */
           lua_pop(L, 1);
        }
        lua_pop(L,1); //remove table
    }else{
        utils::error(L,"bodyDef should be table");
    }
    return def;
}
}


