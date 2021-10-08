#include <box2d/box2d.h>
#include <dmsdk/sdk.h>
#include <extra_utils.h>
#include <utils.h>
#include <manifold.h>

namespace box2dDefoldNE {
static void b2ManifoldPointToTable(lua_State *L, const b2ManifoldPoint* point){
    lua_newtable(L);

    lua_pushnumber(L, point->normalImpulse);
    lua_setfield(L, -2, "normalImpulse");
    lua_pushnumber(L, point->tangentImpulse);
    lua_setfield(L, -2, "tangentImpulse");
    utils::push_vector(L, point->localPoint.x, point->localPoint.y, 0);
    lua_setfield(L, -2, "localPoint");

    b2ContactID id = point->id;
    lua_newtable(L);
        lua_pushnumber(L, id.key);
        lua_setfield(L, -2, "key");

        lua_newtable(L);
            lua_pushnumber(L,id.cf.indexA);
            lua_setfield(L, -2, "indexA");
            lua_pushnumber(L,id.cf.indexB);
            lua_setfield(L, -2, "indexB");
            lua_pushnumber(L,id.cf.typeA);
            lua_setfield(L, -2, "typeA");
            lua_pushnumber(L,id.cf.typeB);
            lua_setfield(L, -2, "typeB");
        lua_setfield(L, -2, "cf");

    lua_setfield(L, -2, "id");

}

void manifold_to_table(lua_State *L, const b2Manifold* manifold){
    lua_newtable(L);
    utils::push_vector(L, manifold->localNormal.x, manifold->localNormal.y, 0);
    lua_setfield(L, -2, "localNormal");

    utils::push_vector(L, manifold->localPoint.x, manifold->localPoint.y, 0);
    lua_setfield(L, -2, "localPoint");

    lua_pushnumber(L,manifold->type);
    lua_setfield(L, -2, "type");

    lua_pushnumber(L,manifold->pointCount);
    lua_setfield(L, -2, "pointCount");

    lua_newtable(L);
        for (int32 i = 0; i < manifold->pointCount; ++i){
            b2ManifoldPointToTable(L,&manifold->points[i]);
            lua_rawseti(L, -2, i+1);
        }
    lua_setfield(L, -2, "points");
}

void world_manifold_to_table(lua_State *L, b2WorldManifold* manifold, int32 pointCount){
    lua_newtable(L);
    utils::push_vector(L, manifold->normal.x, manifold->normal.y, 0);
    lua_setfield(L, -2, "normal");
    lua_newtable(L);
    for (int32 i = 0; i < pointCount; ++i){
        b2Vec2 point = manifold->points[i];
        utils::push_vector(L,point.x, point.y, 0);
        lua_rawseti(L, -2, i+1);
    }
    lua_setfield(L, -2, "points");

    lua_newtable(L);
    for (int32 i = 0; i < pointCount; ++i){
        lua_pushnumber(L,manifold->separations[i]);
        lua_rawseti(L, -2, i+1);
    }
    lua_setfield(L, -2, "separations");
}


void contact_impulse_to_table(lua_State *L, const b2ContactImpulse *impulse){

	float normalImpulses[b2_maxManifoldPoints];
	float tangentImpulses[b2_maxManifoldPoints];

    lua_newtable(L);

    lua_pushnumber(L,impulse->count);
    lua_setfield(L, -2, "count");

    lua_newtable(L);
        for (int32 i = 0; i < impulse->count; ++i){
            lua_pushnumber(L, impulse->normalImpulses[i]);
            lua_rawseti(L, -2, i+1);
        }
    lua_setfield(L, -2, "normalImpulses");

    lua_newtable(L);
        for (int32 i = 0; i < impulse->count; ++i){
            lua_pushnumber(L, impulse->tangentImpulses[i]);
            lua_rawseti(L, -2, i+1);
        }
    lua_setfield(L, -2, "tangentImpulses");
}
}
