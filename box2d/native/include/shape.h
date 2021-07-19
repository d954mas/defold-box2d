#ifndef shape_h
#define shape_h

#include <box2d/box2d.h>
#include <dmsdk/sdk.h>

namespace box2dDefoldNE {

b2Shape* b2Shape_from_table(lua_State *L, int index);



class PolygonShape {
private:
    b2PolygonShape shape;
public:
    PolygonShape(b2PolygonShape shape);
    ~PolygonShape();
};

PolygonShape* b2PolygonShape_push(lua_State *L, b2PolygonShape b2Shape);

}
#endif