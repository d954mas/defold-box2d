#ifndef chain_shape_h
#define chain_shape_h

#include <box2d/box2d.h>
#include <dmsdk/sdk.h>

namespace box2dDefoldNE {

class ChainShape {
public:
    b2ChainShape* shape;
    ChainShape(b2ChainShape* shape);
    ~ChainShape();
};

ChainShape* b2ChainShape_push(lua_State *L, b2ChainShape* b2Shape);
ChainShape* ChainShape_get_userdata(lua_State* L, int index);
}
#endif