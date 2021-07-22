#ifndef shape_h
#define shape_h

#include <box2d/box2d.h>
#include <dmsdk/sdk.h>
#include "shape/polygon_shape.h"
#include "shape/circle_shape.h"
#include "shape/edge_shape.h"
#include "shape/chain_shape.h"

namespace box2dDefoldNE {

b2Shape* b2Shape_from_lua(lua_State *L, int index);

void b2Shape_push(lua_State *L, b2Shape* shape);



}


#endif