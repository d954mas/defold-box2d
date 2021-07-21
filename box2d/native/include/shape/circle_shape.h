#ifndef circle_shape_h
#define circle_shape_h

#include <box2d/box2d.h>
#include <dmsdk/sdk.h>

namespace box2dDefoldNE {

class CircleShape {
public:
    b2CircleShape* shape;
    CircleShape(b2CircleShape* shape);
    ~CircleShape();
};

CircleShape* b2CircleShape_push(lua_State *L, b2CircleShape* b2Shape);
CircleShape* CircleShape_get_userdata(lua_State* L, int index);
}
#endif