#ifndef fixture_def_h
#define fixture_def_h

#include <box2d/box2d.h>
#include <dmsdk/sdk.h>


namespace box2dDefoldNE {

b2FixtureDef b2FixtureDef_from_table(lua_State *L, int index);

}
#endif