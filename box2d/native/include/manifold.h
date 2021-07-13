#ifndef manifold_h
#define manifold_h

#include <box2d/box2d.h>
#include <dmsdk/sdk.h>
#include <extra_utils.h>



void manifold_to_table(lua_State *L, b2Manifold* manifold);

#endif