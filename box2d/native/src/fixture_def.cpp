#include "fixture_def.h"
#include "utils.h"
#include "shape.h"
#include "filter.h"
#include <extra_utils.h>
#include <static_hash.h>

namespace box2dDefoldNE {

b2FixtureDef b2FixtureDef_from_table(lua_State *L, int index){
    b2FixtureDef def;
    if (lua_istable(L, index)) {
        lua_pushvalue(L,index);
        /* table is in the stack at index 't' */
         lua_pushnil(L);  /* first key */
         while (lua_next(L, -2) != 0) {
           /* uses 'key' (at index -2) and 'value' (at index -1) */
            //printf("%s - %s\n",lua_tostring(L, -2),lua_tostring(L, -1));
            const char* key = lua_tostring(L, -2);
            switch (hash_string(key)) {
                case HASH_shape:
                    def.shape = b2Shape_from_lua(L,-1);
                    break;
                case HASH_friction:
                    def.friction = lua_tonumber(L, -1);
                    break;
                case HASH_restitution:
                    def.restitution = lua_tonumber(L, -1);
                    break;
                case HASH_restitutionThreshold:
                    def.restitutionThreshold =  lua_tonumber(L, -1);
                    break;
                case HASH_density:
                    def.density =  lua_tonumber(L, -1);
                    break;
                case HASH_isSensor:
                    def.isSensor =  lua_toboolean(L, -1);
                    break;
                case HASH_userData:
                    if (lua_istable(L ,-1)) {
                        lua_pushvalue(L, -1);
                        def.userData.pointer = luaL_ref(L,LUA_REGISTRYINDEX);
                    }else{
                        utils::error(L,"userdata can be only table or nil");
                    }
                    break;
                case HASH_filter:
                    if (lua_istable(L ,-1)) {
                        def.filter = b2Filter_from_table(L,-1);
                    }else{
                        utils::error(L,"filter can be only table or nil");
                    }
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
        utils::error(L,"fixtureDef should be table");
    }
    if(def.shape == NULL){
        utils::error(L,"fixture def must have shape");
    }
    return def;
}

}

