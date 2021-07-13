#ifndef body_def_h
#define body_def_h

#include <box2d/box2d.h>
#include <dmsdk/sdk.h>

namespace box2dDefoldNE {

b2BodyDef b2BodyDef_from_table(lua_State *L, int index);

}
#endif