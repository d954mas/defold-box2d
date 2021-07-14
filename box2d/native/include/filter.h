#ifndef filter_h
#define filter_h

#include <box2d/box2d.h>
#include <dmsdk/sdk.h>

namespace box2dDefoldNE {

b2Filter b2Filter_from_table(lua_State *L, int index);
void b2Filter_to_table(lua_State *L, b2Filter filter);

}
#endif