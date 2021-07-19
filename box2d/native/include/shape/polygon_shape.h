#ifndef polygon_shape_h
#define polygon_shape_h

#include <box2d/box2d.h>
#include <dmsdk/sdk.h>

namespace box2dDefoldNE {

class PolygonShape {
public:
    b2PolygonShape shape;
    PolygonShape(b2PolygonShape shape);
    ~PolygonShape();
};

PolygonShape* b2PolygonShape_push(lua_State *L, b2PolygonShape b2Shape);

}
#endif