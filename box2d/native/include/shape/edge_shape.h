#ifndef edge_shape_h
#define edge_shape_h

#include <box2d/box2d.h>
#include <dmsdk/sdk.h>

namespace box2dDefoldNE {

class EdgeShape {
public:
    b2EdgeShape* shape;
    EdgeShape (b2EdgeShape* shape);
    ~EdgeShape();
};

EdgeShape* b2EdgeShape_push(lua_State *L, b2EdgeShape* b2Shape);
EdgeShape* EdgeShape_get_userdata(lua_State* L, int index);
}
#endif