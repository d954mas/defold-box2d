#include "allocators.h"
#include "utils.h"
#include "extra_utils.h"
#include <new>

namespace box2dDefoldNE {

b2BlockAllocator shapeAllocator;

//delete b2Shape after use
b2Shape* b2Shape_clone(b2Shape* shape){
    return shape->Clone(&shapeAllocator);
}

b2CircleShape* b2CircleShape_new(){
    void* mem = shapeAllocator.Allocate(sizeof(b2CircleShape));
    return new (mem) b2CircleShape;
}
b2PolygonShape* b2PolygonShape_new(){
    void* mem = shapeAllocator.Allocate(sizeof(b2PolygonShape));
    return new (mem) b2PolygonShape;
}
b2EdgeShape* b2EdgeShape_new(){
    void* mem = shapeAllocator.Allocate(sizeof(b2EdgeShape));
    return new (mem) b2EdgeShape;
}
b2ChainShape* b2ChainShape_new(){
    void* mem = shapeAllocator.Allocate(sizeof(b2ChainShape));
    return new (mem) b2ChainShape;
}

void b2Shape_free(b2Shape* shape){
    switch(shape->GetType()){
        case b2Shape::e_circle:{
            shapeAllocator.Free(shape, sizeof(b2CircleShape));
            break;
        }
        case b2Shape::e_polygon:{
            shapeAllocator.Free(shape, sizeof(b2PolygonShape));
            break;
        }
        case b2Shape::e_edge:{
            shapeAllocator.Free(shape, sizeof(b2EdgeShape));
            break;
        }
        case b2Shape::e_chain:{
            shapeAllocator.Free(shape, sizeof(b2ChainShape));
            break;
        }
    }
}


}