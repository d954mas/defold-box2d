#ifndef manifold_h
#define manifold_h

#include <box2d/box2d.h>
#include <dmsdk/sdk.h>
#include <extra_utils.h>

namespace box2dDefoldNE {

void manifold_to_table(lua_State *L, const b2Manifold* manifold);
void world_manifold_to_table(lua_State *L, b2WorldManifold* manifold, int32 pointCount);

void contact_impulse_to_table(lua_State *L, const b2ContactImpulse *impulse);

}

#endif