#include "body_def.h"
#include "utils.h"
#include <extra_utils.h>
#include <static_hash.h>
namespace box2dDefoldNE {

b2Filter b2Filter_from_table(lua_State *L, int index){
    b2Filter filter;
    lua_pushvalue(L,index);
    filter.categoryBits = utils::table_get_integer_safe(L,"categoryBits", "no categoryBits");
    filter.maskBits = utils::table_get_integer_safe(L,"maskBits", "no maskBits");
    filter.groupIndex = utils::table_get_integer_safe(L,"groupIndex", "no groupIndex");
    lua_pop(L, 1);
    return filter;
}
void b2Filter_to_table(lua_State *L, b2Filter filter){
    lua_newtable(L);
    lua_pushnumber(L, filter.categoryBits);
    lua_setfield(L, -2, "categoryBits");
    lua_pushnumber(L, filter.maskBits);
    lua_setfield(L, -2, "maskBits");
    lua_pushnumber(L, filter.groupIndex);
    lua_setfield(L, -2, "groupIndex");

}

}