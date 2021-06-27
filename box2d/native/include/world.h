#ifndef world_h
#define world_h

#include <queue>
#include <box2d/box2d.h>
#include <dmsdk/sdk.h>
#include <extra_utils.h>
#include "draw.h"



class World : public b2ContactListener {
private:

public:
	b2World *world;
	Draw* draw;
	int table_ref; //always return same table
	World(b2Vec2 gravity);
	~World();
	void Push(lua_State *L);
	void Destroy(lua_State *L);

	// b2ContactListener
	void BeginContact(b2Contact *contact);
	void EndContact(b2Contact *contact);
	void PreSolve(b2Contact *contact, const b2Manifold *old_manifold);
	void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse);
};

void WorldInitMetaTable(lua_State *L);
World* World_get_userdata(lua_State *L, int index);
World* World_get_userdata_safe(lua_State *L, int index);

World* World_find_by_pointer(b2World* world);

#endif