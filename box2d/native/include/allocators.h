#ifndef box2d_allocators_h
#define box2d_allocators_h

#include <box2d/box2d.h>
#include <dmsdk/sdk.h>

namespace box2dDefoldNE {

b2CircleShape* b2CircleShape_new();
b2PolygonShape* b2PolygonShape_new();
b2EdgeShape* b2EdgeShape_new();
b2ChainShape* b2ChainShape_new();
b2Shape* b2Shape_clone(b2Shape* shape);
void b2Shape_free(b2Shape* shape);

}
#endif