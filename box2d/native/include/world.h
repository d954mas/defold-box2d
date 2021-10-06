#ifndef world_h
#define world_h

#include <queue>
#include <box2d/box2d.h>
#include <dmsdk/sdk.h>
#include <extra_utils.h>
#include "draw.h"
#include "base_userdata.h"
#include "contact_listener.h"
#include "destruction_listener.h"

namespace box2dDefoldNE {

class World : public BaseUserData, public b2ContactListener, public b2DestructionListener {
private:

public:
	b2World *world;
	Draw* draw;
	LuaContactListener* contactListener;
	LuaDestructionListener* destructionListener;
	World(b2Vec2 gravity);
	~World();

	virtual void Destroy(lua_State *L);

	// b2ContactListener
	void BeginContact(b2Contact *contact);
	void EndContact(b2Contact *contact);
	void PreSolve(b2Contact *contact, const b2Manifold *old_manifold);
	void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse);

	//b2DestructionListener
    /// Called when any joint is about to be destroyed due
    /// to the destruction of one of its attached bodies.
    void SayGoodbye(b2Joint* joint);

    /// Called when any fixture is about to be destroyed due
    /// to the destruction of its parent body.
    void SayGoodbye(b2Fixture* fixture);
};

void WorldInitMetaTable(lua_State *L);
World* World_get_userdata_safe(lua_State *L, int index);

World* World_find_by_pointer(b2World* world);

}
#endif