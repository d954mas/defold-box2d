
# Box2D for Defold

Box2D lua bindings for the Defold Game Engine.

I tried to keep the lua api the same as the c++ api when possible.

If you like the extension you can support me on patreon.
It will help me make more items for defold.

[![](https://c5.patreon.com/external/logo/become_a_patron_button.png)](https://www.patreon.com/d954mas)

Try the demo: https://d954mas.github.io/defold-box2d/

<img src="https://github.com/d954mas/defold-box2d/blob/master/files/screenshot.png">

# Table of Contents
- [Box2D for Defold](#box2d-for-defold)
  * [Installation](#installation)
  * [Box2d](#box2d)
  * [Limitations](#limitations)
  * [API](#api)
    + [Extension](#extension)
    + [World](#world)
    + [DebugDraw](#debugdraw)
    + [Shape](#shape)
    + [FixtureDef](#fixturedef)
    + [Fixture](#fixture)
    + [BodyDef](#bodydef)
    + [Body](#body)
    + [Joint](#joint)
    + [RevoluteJoint](#revolutejoint)
    + [PrismaticJoint](#prismaticjoint)
    + [DistanceJoint](#distancejoint)
    + [PulleyJoint](#pulleyjoint)
    + [MouseJoint](#mousejoint)
    + [GearJoint](#gearjoint)
    + [WheelJoint](#wheeljoint)
    + [WeldJoint](#weldjoint)
    + [FrictionJoint](#frictionjoint)
    + [MotorJoint](#motorjoint)
    + [Box2dProfile](#box2dprofile)
    + [Box2dMassData](#box2dmassdata)

## Installation

__1)__ Add defold-box2d in your own project as a Defold library dependency. Open your game.project file and in the dependencies field under project add:
https://github.com/d954mas/defold-box2d/archive/refs/tags/0.8.zip

__2)__ Remove Defold engine box2d. If it's not removed there will be a conflict between this box2d and engine box2d.
Open your game.project file and in the App Manifest field under Native Extension add manifest.

1. Use /box2d/manifest.appmanifest, OR
2. You can generate a manifest yourself https://britzl.github.io/manifestation/

## Box2d
If you need info about how Box2D works, read its documentation.
https://box2d.org/documentation/

Box2d version: 2.4.1

## Limitations

__1)__ No binding for b2Vec2. Use defold vector(vmath.vector3)

__2)__ No binding for b2Shape. Use tables for shapes when creating fixtures.

__3)__ b2Assert. #define b2Assert(A) assert(A) . Engine will crashed if b2Assert happened.

__4)__ No binding for some b2World functions.

	void SetDestructionListener(b2DestructionListener* listener);
	void SetContactFilter(b2ContactFilter* filter);
	void SetContactListener(b2ContactListener* listener);
	void QueryAABB(b2QueryCallback* callback, const b2AABB& aabb) const;
	void RayCast(b2RayCastCallback* callback, const b2Vec2& point1, const b2Vec2& point2) const;
	b2Contact* GetContactList();
	const b2ContactManager& GetContactManager() const;

__5)__ No binding for some b2Fixture functions.

	not support filter in fixture def.
	b2Shape* GetShape();
	void SetFilterData(const b2Filter& filter);
	const b2Filter& GetFilterData() const;
	bool RayCast(b2RayCastOutput* output, const b2RayCastInput& input, int32 childIndex) const;
	const b2AABB& GetAABB(int32 childIndex) const;

__6)__ No binding for some b2Body functions.

	b2JointEdge* GetJointList () Get the list of all joints attached to this body
	b2ContactEdge* GetContactList();

__7)__ No binding for some b2Joint functions.

	virtual void Draw(b2Draw* draw) const;

## API
Support emmylua. box2d_header.lua

### Extension
#### Constants:
```lua
box2d.b2Shape = {
    e_circle = 0,
    e_edge = 1,
    e_polygon = 2,
    e_chain = 3,
}

box2d.b2BodyType = {
    b2_staticBody = 0,
    b2_kinematicBody = 1,
    b2_dynamicBody = 2,
}

box2d.b2JointType = {
    e_unknownJoint = 0, e_revoluteJoint = 1,
    e_prismaticJoint = 2, e_distanceJoint = 3,
    e_pulleyJoint = 4, e_mouseJoint = 5,
    e_gearJoint = 6, e_wheelJoint = 7,
    e_weldJoint = 8, e_frictionJoint = 9,
    e_ropeJoint = 10, e_motorJoint = 11,
}

box2d.b2Draw = {
    e_shapeBit = 1, e_jointBit = 2,
    e_aabbBit = 4, e_pairBit = 8,
    e_centerOfMassBit = 16
}
```

#### box2d.NewWorld(gravity)

_ARGUMENTS_
* __gravity__ <kbd>vector3|nil</kbd> - The world gravity vector.

_RETURNS_
* <kbd>Box2dWorld</kbd>

#### box2d.NewDebugDraw(data)

_ARGUMENTS_
* __data__ <kbd>table</kbd> -

_RETURNS_
* <kbd>Box2dDebugDraw</kbd>

#### box2d.b2LinearStiffness(frequencyHertz, dampingRatio, bodyA, bodyB)
Utility to compute linear stiffness values from frequency and damping ratio

_ARGUMENTS_
* __frequencyHertz__ <kbd>number</kbd> -
* __dampingRatio__ <kbd>number</kbd> -
* __bodyA__ <kbd>Box2dBody</kbd> -
* __bodyB__ <kbd>Box2dBody</kbd> -

_RETURNS_
* <kbd>number</kbd> - Stiffness
* <kbd>number</kbd> - Damping

#### box2d.b2AngularStiffness(frequencyHertz, dampingRatio, bodyA, bodyB)
Utility to compute rotational stiffness values from frequency and damping ratio

_ARGUMENTS_
* __frequencyHertz__ <kbd>number</kbd> -
* __dampingRatio__ <kbd>number</kbd> -
* __bodyA__ <kbd>Box2dBody</kbd> -
* __bodyB__ <kbd>Box2dBody</kbd> -

_RETURNS_
* <kbd>number</kbd> - Stiffness
* <kbd>number</kbd> - Damping

### World
A physics world is a collection of bodies, fixtures, and constraints that interact together. Box2D supports the creation of multiple worlds, but this is usually not necessary or desirable.
Destroy the world with world:Destroy() when you do not need it any more.

#### Box2dWorld:SetDebugDraw(draw)
Register a routine for debug drawing. The debug draw functions are called
inside with b2World:DebugDraw method. The debug draw object is owned
by you and must remain in scope.

_ARGUMENTS_
* __draw__ <kbd>Box2dDebugDraw|nil</kbd> -

#### Box2dWorld:CreateBody(bodyDef)
Create a rigid body given a definition.
_Warning:_ This function is locked during callbacks.

_ARGUMENTS_
* __bodyDef__ <kbd>Box2dBodyDef</kbd> -

_RETURNS_
* <kbd>Box2dBody</kbd>

#### Box2dWorld:DestroyBody(body)
Destroy a rigid body given a definition.
_Warning:_ This automatically deletes all associated shapes and joints.
_Warning:_ This function is locked during callbacks.

_ARGUMENTS_
* __body__ <kbd>Box2dBody</kbd> -

#### Box2dWorld:CreateJoint(def)
Create a joint to constrain bodies together.
This may cause the connected bodies to cease colliding.
_Warning:_ This function is locked during callbacks.

_ARGUMENTS_
* __def__ <kbd>Box2dJointDef</kbd> -

_RETURNS_
* <kbd>Box2dJoint</kbd>

#### Box2dWorld:DestroyJoint(joint)
Destroy a joint. This may cause the connected bodies to begin colliding.
_Warning:_ This function is locked during callbacks.

_ARGUMENTS_
* __joint__ <kbd>Box2dJoint</kbd> -

#### Box2dWorld:Step(timeStep, velocityIterations, positionIterations)
Take a time step. This performs collision detection, integration,
and constraint solution.

_ARGUMENTS_
* __timeStep__ <kbd>number</kbd> - The amount of time to simulate, this should not vary.
* __velocityIterations__ <kbd>number</kbd> - For the velocity constraint solver. Suggested value: 8.
* __positionIterations__ <kbd>number</kbd> - For the position constraint solver. Suggested value: 3.

#### Box2dWorld:ClearForces()
Manually clear the force buffer on all bodies. By default, forces are cleared automatically
after each call to Step. The default behavior is modified by calling SetAutoClearForces.
The purpose of this function is to support sub-stepping. Sub-stepping is often used to maintain
a fixed sized time step under a variable frame-rate.
When you perform sub-stepping you will disable auto clearing of forces and instead call
ClearForces after all sub-steps are complete in one pass of your game loop.
@see SetAutoClearForces

#### Box2dWorld:DebugDraw()
Call this to draw shapes and other debug draw data. This is intentionally non-const.

#### Box2dWorld:GetBodyList()
Get the world body list. With the returned body, use b2Body:GetNext() to get the next body in the world list.
A nil body indicates the end of the list.

_RETURNS_
* <kbd>Box2dBody|nil</kbd> - The head of the world body list.

#### Box2dWorld:GetJointList()
Get the world joint list. With the returned joint, use b2Joint:GetNext() to get the next joint in the world list.
A nil joint indicates the end of the list.

_RETURNS_
* <kbd>Box2dJoint|nil</kbd> - The head of the world joint list.

#### Box2dWorld:SetAllowSleeping(flag)
Enable/disable sleep.

#### Box2dWorld:GetAllowSleeping()

_RETURNS_
* <kbd>boolean</kbd>

#### Box2dWorld:SetWarmStarting(flag)
Enable/disable warm starting. For testing.

#### Box2dWorld:GetWarmStarting()

_RETURNS_
* <kbd>boolean</kbd>

#### Box2dWorld:SetContinuousPhysics(flag)
Enable/disable continuous physics. For testing.

#### Box2dWorld:GetContinuousPhysics()

_RETURNS_
* <kbd>boolean</kbd>

#### Box2dWorld:SetSubStepping(flag)
Enable/disable single stepped continuous physics. For testing.

#### Box2dWorld:GetSubStepping()

_RETURNS_
* <kbd>boolean</kbd>


#### Box2dWorld:GetProxyCount()

_RETURNS_
* <kbd>number</kbd> - The number of broad-phase proxies.

#### Box2dWorld:GetBodyCount()

_RETURNS_
* <kbd>number</kbd> - The number of bodies.

#### Box2dWorld:GetJointCount()

_RETURNS_
* <kbd>number</kbd> - The number of joints

#### Box2dWorld:GetContactCount()

_RETURNS_
* <kbd>number</kbd> - The number of contacts (each may have 0 or more contact ###

#### Box2dWorld:GetTreeHeight()

_RETURNS_
* <kbd>number</kbd> - The height of the dynamic tree.

#### Box2dWorld:GetTreeBalance()

_RETURNS_
* <kbd>number</kbd> - The balance of the dynamic tree.

#### Box2dWorld:GetTreeQuality()
Get the quality metric of the dynamic tree. The smaller the better.
The minimum is 1.

_RETURNS_
* <kbd>number</kbd>

#### Box2dWorld:SetGravity()
Change the global gravity vector.

#### Box2dWorld:GetGravity()
Get the global gravity vector.

_RETURNS_
* <kbd>vector3</kbd>

#### Box2dWorld:IsLocked()
Is the world locked (in the middle of a time step).

_RETURNS_
* <kbd>boolean</kbd>

#### Box2dWorld:SetAutoClearForces(flag)
Set flag to control automatic clearing of forces after each time step.

#### Box2dWorld:GetAutoClearForces()
 Get the flag that controls automatic clearing of forces after each time step.

_RETURNS_
* <kbd>boolean</kbd>

#### Box2dWorld:ShiftOrigin(newOrigin)
Shift the world origin. Useful for large worlds.
The body shift formula is: position -= newOrigin
* __newOrigin__ <kbd>vector3</kbd> - The new origin with respect to the old origin

#### Box2dWorld:GetProfile()
Get the current profile.

_RETURNS_
* <kbd>Box2dProfile</kbd>

#### Box2dWorld:Dump()
Dump the world into the log file.
_Warning:_ this should be called outside of a time step.

#### Box2dWorld:Destroy()
Destroy world

### DebugDraw
register this class with a b2World to provide debug drawing of physics
entities in your game.
Destroy it when not it's needed anymore.

#### Creation:
```lua
-- NOTE: See the /box2d/utils module for premade functions using the "draw_line" message.

box2d.NewDebugDraw({
	DrawPolygon = function(vertices,color) __draw_polygon(physics_scale,vertices,color) end,
	DrawSolidPolygon = function(vertices,color) __draw_polygon(physics_scale,vertices,color) end,
	DrawCircle = function(center,radius,color) __draw_circle(physics_scale,center,radius,nil,color) end,
	DrawSolidCircle = function(center,radius,axis,color) __draw_circle(physics_scale,center,radius,axis,color) end,
	DrawSegment = function(p1,p2,color) __draw_segment(physics_scale,p1,p2,color) end,
})
```

#### Box2dDebugDraw:SetFlags(flags)
Set the drawing flags.

_ARGUMENTS_
* __flags__ <kbd>number</kbd> -

#### Box2dDebugDraw:GetFlags()
Get the drawing flags.

_RETURNS_
* <kbd>number</kbd>

#### Box2dDebugDraw:AppendFlags(flags)
Append flags to the current flags.

_ARGUMENTS_
* __flags__ <kbd>number</kbd> -

#### Box2dDebugDraw:ClearFlags(flags)
Clear flags from the current flags.

_ARGUMENTS_
* __flags__ <kbd>number</kbd> -

#### Box2dDebugDraw:Destroy()
Destroy, free memory.

### Shape
There is no direct binding for `b2Shape`. Use a table with data instead when you need a shape, for example when you create a fixture.

```lua
local Box2dShape = {
    --box2d.b2Shape e_circle, e_edge, e_polygon, e_chain
    shape = 0,

    --circle
    circle_radius = 1,
    circle_position = vmath.vector3(0), --or nil

    --edge
    edge_two_sided = false,
    edge_v0 = vmath.vector3(0),
    edge_v1 = vmath.vector3(0),
    edge_v2 = vmath.vector3(0),
    edge_v3 = vmath.vector3(0),

    --box (polygon)
    box = true,
    box_hx = 1, box_hy = 1,
    box_center = vmath.vector3(0), --or nil
    box_angle = 0, -- or nil. need box_center when use angle

    --polygon vertices
    polygon_vertices = { vmath.vector3(0, 0, 0), vmath.vector3(1, 0, 0), vmath.vector3(0, 1, 0) },

    --chain
    chain_loop = false, --true use CreateLoop false use CreateChain
    chain_vertices = { vmath.vector3(1.7, 0, 0), vmath.vector3(1, 0, 0), vmath.vector3(0, 0, 0), vmath.vector3(-1.7, 0.4, 0) },
    chain_prev_vertex = vmath.vector3(0, 0, 0),
    chain_next_vertex = vmath.vector3(0, 0, 0)
}
```

### FixtureDef
A fixture definition is used to create a fixture.
You can reuse fixture definitions safely.

```lua
local Box2dFixtureDef = {
    -- The shape, this must be set.
    @type Box2dShape
    shape = { shape = box2d.b2Shape.e_circle, circle_radius = 1, circle_position = vmath.vector3(0) },

    -- Use this to store application specific fixture data.
    userData = nil;

    -- The friction coefficient, usually in the range [0,1].
    friction = 0.2;

    -- The restitution (elasticity) usually in the range [0,1].
    restitution = 0;

    -- Restitution velocity threshold, usually in m/s. Collisions above this
    -- speed have restitution applied (will bounce).
    restitutionThreshold = 1;

    --The density, usually in kg/m^2.
    density = 0;

    -- A sensor shape collects contact information but never generates a collision
    -- response.
    isSensor = false;

    -- Contact filtering data. b2Filter
    -- filter = nil;
}
```

### Fixture
A fixture binds a shape to a body and adds material properties such as density, friction, and restitution. A fixture puts a shape into the collision system (broad-phase) so that it can collide with other shapes.

#### Box2dFixture:GetType()

_RETURNS_
* <kbd>number(box2d.b2Shape)</kbd> -

#### Box2dFixture:SetSensor(sensor)
Set if this fixture is a sensor.

_ARGUMENTS_
* __sensor__ <kbd>boolean</kbd> -

#### Box2dFixture:IsSensor()
Is this fixture a sensor (non-solid)?

_RETURNS_
* <kbd>boolean</kbd> - The true if the shape is a sensor.

#### Box2dFixture:Refilter()
Call this if you want to establish collision that was previously disabled by b2ContactFilter::ShouldCollide.

#### Box2dFixture:GetBody()
Get the parent body of this fixture. This is nil if the fixture is not attached.

_RETURNS_
* <kbd>Box2dBody</kbd> - The parent body

#### Box2dFixture:GetNext()
Get the next fixture in the parent body's fixture list.

_RETURNS_
* <kbd>Box2dFixture|nil</kbd>

#### Box2dFixture:GetUserData()
Get the user data that was assigned in the fixture definition. Use this to
store your application specific data.

_RETURNS_
* <kbd>table|nil</kbd>

#### Box2dFixture:SetUserData(userdata)
Set the user data. Use this to
store your application specific data.

_ARGUMENTS_
* __userdata__ <kbd>table|nil</kbd> -

#### Box2dFixture:TestPoint(point)
Test a point for containment in this fixture.

_ARGUMENTS_
* __point__ <kbd>vector3</kbd> - A point in world coordinates.

#### Box2dFixture:GetMassData()
Get the mass data for this fixture. The mass data is based on the density and
the shape. The rotational inertia is about the shape's origin. This operation
may be expensive.

_RETURNS_
* <kbd>Box2dMassData</kbd>

#### Box2dFixture:GetDensity()
Get the density of this fixture.

_RETURNS_
* <kbd>number</kbd>

#### Box2dFixture:SetDensity(density)
Set the density of this fixture. This will _not_ automatically adjust the mass
of the body. You must call Box2dBody:ResetMassData() to update the body's mass.

_ARGUMENTS_
* __density__ <kbd>number</kbd> -

#### Box2dFixture:GetFriction()
Get the coefficient of friction.

_RETURNS_
* <kbd>number</kbd>

#### Box2dFixture:SetFriction(friction)
Set the coefficient of friction. This will _not_ change the friction of
existing contacts.

_ARGUMENTS_
* __friction__ <kbd>number</kbd> -

#### Box2dFixture:GetRestitution()
Get the coefficient of restitution.

_RETURNS_
* <kbd>number</kbd>

#### Box2dFixture:SetRestitution(restitution)
Set the coefficient of restitution. This will _not_ change the restitution of
existing contacts.

_ARGUMENTS_
* __restitution__ <kbd>number</kbd> -

#### Box2dFixture:GetRestitutionThreshold()
Get the restitution velocity threshold.

_RETURNS_
* <kbd>number</kbd>

#### Box2dFixture:SetRestitutionThreshold(threshold)
Set the restitution threshold. This will _not_ change the restitution threshold of
existing contacts.

_ARGUMENTS_
* __threshold__ <kbd>number</kbd> -

#### Box2dFixture:Dump(bodyIndex)
Dump this fixture to the log file.

_ARGUMENTS_
* __bodyIndex__ <kbd>number</kbd> -

### BodyDef
A body definition holds all the data needed to construct a rigid body.
You can safely re-use body definitions. Shapes are added to a body after construction.

```lua
local Box2dBodyDef = {
    -- The body type: static, kinematic, or dynamic.
    -- box2d.b2BodyType
    -- Note: if a dynamic body would have zero mass, the mass is set to one.
    type = box2d.b2BodyType.b2_staticBody,

    -- The world position of the body. Avoid creating bodies at the origin
    -- since this can lead to many overlapping shapes.
    position = vmath.vector3(0),

    -- The world angle of the body in radians.
    angle = 0,

    -- The linear velocity of the body's origin in world co-ordinates.
    linearVelocity = vmath.vector3(0),

    -- The angular velocity of the body.
    angularVelocity = 0,

    -- Linear damping is use to reduce the linear velocity. The damping parameter
    -- can be larger than 1.0f but the damping effect becomes sensitive to the
    -- time step when the damping parameter is large.
    -- Units are 1/time
    linearDamping = 0,

    -- Angular damping is use to reduce the angular velocity. The damping parameter
    -- can be larger than 1.0f but the damping effect becomes sensitive to the
    -- time step when the damping parameter is large.
    -- Units are 1/time
    angularDamping = 0,

    -- Set this flag to false if this body should never fall asleep. Note that
    -- this increases CPU usage.
    allowSleep = true,

    -- Is this body initially awake or sleeping?
    awake = true,

    -- Should this body be prevented from rotating? Useful for characters.
    fixedRotation = false,

    -- Is this a fast moving body that should be prevented from tunneling through
    -- other moving bodies? Note that all bodies are prevented from tunneling through
    -- kinematic and static bodies. This setting is only considered on dynamic bodies.
    -- @_Warning:_ You should use this flag sparingly since it increases processing time.
    bullet = false,

    -- Does this body start out enabled?
    enabled = true,

    -- Use this to store application specific body data.
    userData = nil,

    -- Scale the gravity applied to this body.
    gravityScale = 1
}
```

### Body
A chunk of matter that is so strong that the distance between any two bits of matter on the chunk is constant. They are hard like a diamond. In the following discussion we use body interchangeably with rigid body.

A rigid body. These are created via world:CreateBody.

#### Box2dBody:CreateFixture(def)
Creates a fixture and attach it to this body. Use this function if you need
to set some fixture parameters, like friction. Otherwise you can create the
fixture directly from a shape.
If the density is non-zero, this function automatically updates the mass of the body.
Contacts are not created until the next time step.
_Warning:_ This function is locked during callbacks.

_ARGUMENTS_
* __def__ <kbd>Box2dFixtureDef</kbd> -

_RETURNS_
* <kbd>Box2dFixture</kbd>

#### Box2dBody:CreateFixture(shape, density)
Creates a fixture from a shape and attach it to this body.
This is a convenience function. Use b2FixtureDef if you need to set parameters
like friction, restitution, user data, or filtering.
If the density is non-zero, this function automatically updates the mass of the body.
_Warning:_ This function is locked during callbacks.

_ARGUMENTS_
* __shape__ <kbd>Box2dShape</kbd> -
* __density__ <kbd>number</kbd> - The shape density (set to zero for static bodies)

_RETURNS_
* <kbd>Box2dFixture</kbd>

#### Box2dBody:DestroyFixture(fixture)
Destroy a fixture. This removes the fixture from the broad-phase and
destroys all contacts associated with this fixture. This will
automatically adjust the mass of the body if the body is dynamic and the
fixture has positive density.
All fixtures attached to a body are implicitly destroyed when the body is destroyed.
_Warning:_ This function is locked during callbacks.

_ARGUMENTS_
* __fixture__ <kbd>Box2dFixture</kbd> -

#### Box2dBody:SetTransform(position, angle)
Set the position of the body's origin and rotation.
Manipulating a body's transform may cause non-physical behavior.
Note: contacts are updated on the next call to b2World::Step.

_ARGUMENTS_
* __position__ <kbd>vector3</kbd> - The world position of the body's local origin.
* __angle__ <kbd>number|nil</kbd> - The world rotation in radians. If nil use current angle

#### Box2dBody:GetTransform()
Get the body transform for the body's origin.

_RETURNS_
* <kbd>vector3</kbd> - Position
* <kbd>number</kbd> - Angle

#### Box2dBody:GetPosition()
Get the world body origin position.

_RETURNS_
* <kbd>vector3</kbd>

#### Box2dBody:GetAngle()
Get the angle in radians.

_RETURNS_
* <kbd>number</kbd>

#### Box2dBody:GetWorldCenter()
Get the world position of the center of mass.

_RETURNS_
* <kbd>vector3</kbd>

#### Box2dBody:GetLocalCenter()
Get the local position of the center of mass.

_RETURNS_
* <kbd>vector3</kbd>

#### Box2dBody:SetLinearVelocity(velocity)
Set the linear velocity of the center of mass.

_ARGUMENTS_
* __velocity__ <kbd>vector3</kbd> -

#### Box2dBody:GetLinearVelocity()
Get the linear velocity of the center of mass.

_RETURNS_
* <kbd>vector3</kbd>

#### Box2dBody:SetAngularVelocity(omega)
Set the angular velocity.

_ARGUMENTS_
* __omega__ <kbd>number</kbd> - The new angular velocity in radians/second.

#### Box2dBody:GetAngularVelocity()
Get the angular velocity.

_RETURNS_
* <kbd>number</kbd> - The angular velocity in radians/second.

#### Box2dBody:ApplyForce(force, point, wake)
Apply a force at a world point. If the force is not
applied at the center of mass, it will generate a torque and
affect the angular velocity. This wakes up the body.

_ARGUMENTS_
* __force__ <kbd>vector3</kbd> - Force the world force vector, usually in Newtons (N).
* __point__ <kbd>vector3</kbd> - Point the world position of the point of application.
* __wake__ <kbd>boolean</kbd> - Wake also wake up the body

#### Box2dBody:ApplyForceToCenter(force, wake)
Apply a force to the center of mass. This wakes up the body.

_ARGUMENTS_
* __force__ <kbd>vector3</kbd> - Force the world force vector, usually in Newtons (N).
* __wake__ <kbd>boolean</kbd> - Wake also wake up the body

#### Box2dBody:ApplyTorque(torque, wake)
Apply a torque. This affects the angular velocity
without affecting the linear velocity of the center of mass.

_ARGUMENTS_
* __torque__ <kbd>number</kbd> - Torque about the z-axis (out of the screen), usually in N-m.
* __wake__ <kbd>boolean</kbd> - Wake also wake up the body

#### Box2dBody:ApplyLinearImpulse(impulse, point, wake)
Apply an impulse at a point. This immediately modifies the velocity.
It also modifies the angular velocity if the point of application
is not at the center of mass. This wakes up the body.

_ARGUMENTS_
* __impulse__ <kbd>vector3</kbd> - Impulse the world impulse vector, usually in N-seconds or kg-m/s.
* __point__ <kbd>vector3</kbd> - Point the world position of the point of application.
* __wake__ <kbd>boolean</kbd> - Wake also wake up the body

#### Box2dBody:ApplyLinearImpulseToCenter(impulse, wake)
Apply an impulse to the center of mass. This immediately modifies the velocity.

_ARGUMENTS_
* __impulse__ <kbd>vector3</kbd> - Impulse the world impulse vector, usually in N-seconds or kg-m/s.
* __wake__ <kbd>boolean</kbd> - Wake also wake up the body

#### Box2dBody:ApplyAngularImpulse(impulse, wake)
Apply an angular impulse.

_ARGUMENTS_
* __impulse__ <kbd>vector3</kbd> - Impulse the angular impulse in units of kg*m*m/s
* __wake__ <kbd>boolean</kbd> - Wake also wake up the body

#### Box2dBody:GetMass()
Get the total mass of the body.

_RETURNS_
* <kbd>number</kbd> - The mass, usually in kilograms (kg).

#### Box2dBody:GetInertia()
Get the rotational inertia of the body about the local origin.

_RETURNS_
* <kbd>number</kbd> - The rotational inertia, usually in kg-m^2.

#### Box2dBody:ResetMassData()
This resets the mass properties to the sum of the mass properties of the fixtures.
This normally does not need to be called unless you called SetMassData to override
the mass and you later want to reset the mass.

#### Box2dBody:GetMassData()
Get the mass data of the body.

_RETURNS_
* <kbd>Box2dMassData</kbd> - A struct containing the mass, inertia and center of ### bod

#### Box2dBody:SetMassData(data)
Set the mass properties to override the mass properties of the fixtures.
Note that this changes the center of mass position.
Note that creating or destroying fixtures can also alter the mass.
This function has no effect if the body isn't dynamic.

_ARGUMENTS_
* __data__ <kbd>Box2dMassData</kbd> - The mass properties.

#### Box2dBody:GetWorldPoint(localPoint)
Get the world coordinates of a point given the local coordinates.

_ARGUMENTS_
* __localPoint__ <kbd>vector3</kbd> - A point on the body measured relative the the body's origin.

_RETURNS_
* <kbd>vector3</kbd> - The same point expressed in world coordinates.

#### Box2dBody:GetWorldVector(localVector)
Get the world coordinates of a vector given the local coordinates.

_ARGUMENTS_
* __localVector__ <kbd>vector3</kbd> - LocalVector a vector fixed in the body.

_RETURNS_
* <kbd>vector3</kbd> - The same vector expressed in world coordinates.

#### Box2dBody:GetLocalPoint(worldPoint)
Gets a local point relative to the body's origin given a world point.

_ARGUMENTS_
* __worldPoint__ <kbd>vector3</kbd> - WorldPoint a point in world coordinates.

_RETURNS_
* <kbd>vector3</kbd> - The corresponding local point relative to the body's origin.

#### Box2dBody:GetLocalVector(worldVector)
Gets a local vector given a world vector.

_ARGUMENTS_
* __worldVector__ <kbd>vector3</kbd> - WorldVector a vector in world coordinates.

_RETURNS_
* <kbd>vector3</kbd> - The corresponding local vector.

#### Box2dBody:GetLinearVelocityFromWorldPoint(worldPoint)
Get the world linear velocity of a world point attached to this body.

_ARGUMENTS_
* __worldPoint__ <kbd>vector3</kbd> - WorldPoint a point in world coordinates.

_RETURNS_
* <kbd>vector3</kbd> - The world velocity of a point.

#### Box2dBody:GetLinearVelocityFromLocalPoint(localPoint)
Get the world velocity of a local point.

_ARGUMENTS_
* __localPoint__ <kbd>vector3</kbd> - LocalPoint a point in local coordinates.

_RETURNS_
* <kbd>vector3</kbd> - The world velocity of a point.

#### Box2dBody:SetLinearDamping(linearDamping)
Set the linear damping of the body.

_ARGUMENTS_
* __linearDamping__ <kbd>number</kbd> -

#### Box2dBody:GetLinearDamping()
Get the linear damping of the body.

_RETURNS_
* <kbd>number</kbd>

#### Box2dBody:SetAngularDamping(angularDamping)
Set the angular damping of the body.

_ARGUMENTS_
* __angularDamping__ <kbd>number</kbd> -

#### Box2dBody:GetAngularDamping()
Get the angular damping of the body.

_RETURNS_
* <kbd>number</kbd>

#### Box2dBody:SetGravityScale(scale)
Set the gravity scale of the body.

_ARGUMENTS_
* __scale__ <kbd>number</kbd> -

#### Box2dBody:GetGravityScale()
Get the gravity scale of the body.

_RETURNS_
* <kbd>number</kbd>

#### Box2dBody:SetType(type)
Set the type of this body. This may alter the mass and velocity.

_ARGUMENTS_
* __type__ <kbd>number</kbd> - Box2d.b2BodyType

#### Box2dBody:GetType()
Get the type of this body.

_RETURNS_
* <kbd>number</kbd> - Box2d.b2BodyType

#### Box2dBody:SetBullet(flag)
Should this body be treated like a bullet for continuous collision detection?

_ARGUMENTS_
* __flag__ <kbd>boolean</kbd> -

#### Box2dBody:IsBullet()
Is this body treated like a bullet for continuous collision detection?

_RETURNS_
* <kbd>boolean</kbd>

#### Box2dBody:SetSleepingAllowed(flag)
You can disable sleeping on this body. If you disable sleeping, the
body will be woken.

_ARGUMENTS_
* __flag__ <kbd>boolean</kbd> -

#### Box2dBody:IsSleepingAllowed()
Is this body allowed to sleep

_RETURNS_
* <kbd>boolean</kbd>

#### Box2dBody:SetAwake(flag)
Set the sleep state of the body. A sleeping body has very
low CPU cost.

_ARGUMENTS_
* __flag__ <kbd>boolean</kbd> - Flag set to true to wake the body, false to put it to sleep.

#### Box2dBody:IsAwake()
Get the sleeping state of this body.

_RETURNS_
* <kbd>boolean</kbd> -  true if the body is awake.

#### Box2dBody:SetEnabled(flag)
Allow a body to be disabled. A disabled body is not simulated and cannot
be collided with or woken up.
If you pass a flag of true, all fixtures will be added to the broad-phase.
If you pass a flag of false, all fixtures will be removed from the
broad-phase and all contacts will be destroyed.
Fixtures and joints are otherwise unaffected. You may continue
to create/destroy fixtures and joints on disabled bodies.
Fixtures on a disabled body are implicitly disabled and will
not participate in collisions, ray-casts, or queries.
Joints connected to a disabled body are implicitly disabled.
An diabled body is still owned by a b2World object and remains
in the body list.

_ARGUMENTS_
* __flag__ <kbd>boolean</kbd> -

#### Box2dBody:IsEnabled()
Get the active state of the body.

_RETURNS_
* <kbd>boolean</kbd>

#### Box2dBody:SetFixedRotation(flag)
Set this body to have fixed rotation. This causes the mass
to be reset.

_ARGUMENTS_
* __flag__ <kbd>boolean</kbd> -

#### Box2dBody:IsFixedRotation()
Does this body have fixed rotation?

_RETURNS_
* <kbd>boolean</kbd>

#### Box2dBody:GetNext()
Get the next body in the world's body list.

_RETURNS_
* <kbd>Box2dBody</kbd>

#### Box2dBody:GetFixtureList()
Get the first fixture in list of all fixtures attached to this body or nil

_RETURNS_
* <kbd>Box2dFixture|nil</kbd>

#### Box2dBody:GetUserData()
Get the user data table. Use this to store your application specific data.

_RETURNS_
* <kbd>table|nil</kbd>

#### Box2dBody:SetUserData(data)
Set the user data. Use this to store your application specific data.

_ARGUMENTS_
* __data__ <kbd>table|nil</kbd> -

#### Box2dBody:GetWorld()
Get the parent world of this body.

_RETURNS_
* <kbd>Box2dWorld</kbd>

#### Box2dBody:Dump()
Dump this body to a file

### Joint
This is a constraint used to hold two or more bodies together. Box2D supports several joint types: revolute, prismatic, distance, and more. Some joints may have limits and motors.

Box2dJointDef is based for other joint def.
Joint have needed and optional fields.
If jointDef have Initialize method for example b2PrismaticJointDef, it will be called when create joint def.

```lua
local Box2dJointDef = {
    --region JointNeeded
    The joint type
    type = box2d.b2JointType.e_revoluteJoint,

    @type Box2dBody
    bodyA = nil,

    @type Box2dBody
    bodyB = nil,
    --endregion

    --region JointOptional
    -- Use this to attach application specific data to your joints.
    @type table|nil
    userData = nil,

    -- Set this flag to true if the attached bodies should collide.
    collideConnected = false,
    --endregion

}
```
The base joint class. Joints are used to constraint two bodies together in
various fashions. Some joints also feature limits and motors.

The base joint class. Joints are used to constraint two bodies together in
various fashions. Some joints also feature limits and motors.

#### Box2dJoint:GetType()
Get the type of the concrete joint.

_RETURNS_
* <kbd>number</kbd> - Box2d.b2JointType

#### Box2dJoint:GetBodyA()
Get the first body attached to this joint.

_RETURNS_
* <kbd>Box2dBody</kbd> - BodyA

#### Box2dJoint:GetBodyA()
Get the second body attached to this joint.

_RETURNS_
* <kbd>Box2dBody</kbd> - BodyB

#### Box2dJoint:GetAnchorA()
Get the anchor point on bodyA in world coordinates.

_RETURNS_
* <kbd>vector3</kbd>

#### Box2dJoint:GetAnchorB()
Get the anchor point on bodyB in world coordinates.

_RETURNS_
* <kbd>vector3</kbd>

#### Box2dJoint:GetReactionForce(inv_dt)
Get the reaction force on bodyB at the joint anchor in Newtons.

_ARGUMENTS_
* __inv_dt__ <kbd>number</kbd> -

_RETURNS_
* <kbd>vector3</kbd>

#### Box2dJoint:GetReactionTorque(inv_dt)
Get the reaction torque on bodyB in N*m.

_ARGUMENTS_
* __inv_dt__ <kbd>number</kbd> -

_RETURNS_
* <kbd>vector3</kbd>

#### Box2dJoint:GetNext()
Get the next joint the world joint list.

_RETURNS_
* <kbd>Box2dJoint|nil</kbd>

#### Box2dJoint:GetUserData()
Get the user data.
Use this to store your application specific data.

_RETURNS_
* <kbd>table|nil</kbd>

#### Box2dJoint:SetUserData(userdata)
Set the user data.
Use this to store your application specific data.

_ARGUMENTS_
* __userdata__ <kbd>table|nil</kbd> -

#### Box2dJoint:IsEnabled()
Short-cut function to determine if either body is enabled.

_RETURNS_
* <kbd>boolean</kbd>

#### Box2dJoint:GetCollideConnected()
Get collide connected.
Note: modifying the collide connect flag won't work correctly because
the flag is only checked when fixture AABBs begin to overlap.

_RETURNS_
* <kbd>boolean</kbd>

#### Box2dJoint:Dump()
Dump this joint to the log file.

#### Box2dJoint:ShiftOrigin(newOrigin)
Shift the origin for any points stored in world coordinates.

_ARGUMENTS_
* __newOrigin__ <kbd>vector3</kbd> -

### RevoluteJoint

Revolute joint definition. This requires defining an anchor point where the
bodies are joined. The definition uses local anchor points so that the
initial configuration can violate the constraint slightly. You also need to
specify the initial relative angle for joint limits. This helps when saving
and loading a game.

The local anchor points are measured from the body's origin
rather than the center of mass because:
1. you might not know where the center of mass will be.
2. if you add/remove shapes from a body and recompute the mass,the joints will be broken.

```lua
local Box2dRevoluteJointDef = {
    -- Initialize the bodies, anchors, and reference angle using a world
    -- anchor point.
    -- void Initialize(b2Body* bodyA, b2Body* bodyB, const b2Vec2& anchor);

    --region JointNeeded
    anchor = vmath.vector3(0), for Initialize
    --endregion

    --region JointOptional
    The local anchor point relative to bodyA's origin.
    localAnchorA = vmath.vector3(0, 0, 0),

    The local anchor point relative to bodyB's origin.
    localAnchorB = vmath.vector3(0, 0, 0),

    The bodyB angle minus bodyA angle in the reference state (radians).
    referenceAngle = 0,

    A flag to enable joint limits.
    enableLimit = false,

    The lower angle for the joint limit (radians).
    lowerAngle = 0,

    The upper angle for the joint limit (radians).
    upperAngle = 0,

    A flag to enable the joint motor.
    enableMotor = false,

    The desired motor speed. Usually in radians per second.
    motorSpeed = 0,

    The maximum motor torque used to achieve the desired motor speed.
    Usually in N-m.
    maxMotorTorque = 0,
    --endregion
}
```
A revolute joint constrains two bodies to share a common point while they
are free to rotate about the point. The relative rotation about the shared
point is the joint angle. You can limit the relative rotation with
a joint limit that specifies a lower and upper angle. You can use a motor
to drive the relative rotation about the shared point. A maximum motor torque is provided so that infinite forces are not generated.

#### Box2dRevoluteJoint:GetLocalAnchorA()
The local anchor point relative to bodyA's origin.

_RETURNS_
* <kbd>vector3</kbd>

#### Box2dRevoluteJoint:GetLocalAnchorB()
The local anchor point relative to bodyB's origin.

_RETURNS_
* <kbd>vector3</kbd>

#### Box2dRevoluteJoint:GetReferenceAngle()
Get the reference angle.

_RETURNS_
* <kbd>float</kbd>

### Box2dRevoluteJoint:GetJointAngle(
Get the current joint angle in radians.

_RETURNS_
* <kbd>float</kbd>

#### Box2dRevoluteJoint:GetJointSpeed()
Get the current joint angle speed in radians per second.

_RETURNS_
* <kbd>float</kbd>

#### Box2dRevoluteJoint:IsLimitEnabled()
Is the joint limit enabled?

_RETURNS_
* <kbd>boolean</kbd>

#### Box2dRevoluteJoint:EnableLimit(flag)
Enable/disable the joint limit.

_ARGUMENTS_
* __flag__ <kbd>boolean</kbd> -

#### Box2dRevoluteJoint:GetLowerLimit()
Get the lower joint limit in radians.

_RETURNS_
* <kbd>float</kbd>

#### Box2dRevoluteJoint:GetUpperLimit()
Get the upper joint limit in radians.

_RETURNS_
* <kbd>float</kbd>

#### Box2dRevoluteJoint:SetLimits(lower, upper)
Set the joint limits in radians.

_ARGUMENTS_
* __lower__ <kbd>number</kbd> -
* __upper__ <kbd>number</kbd> -

#### Box2dRevoluteJoint:IsMotorEnabled()
Is the joint motor enabled?

_RETURNS_
* <kbd>boolean</kbd>

#### Box2dRevoluteJoint:EnableMotor(flag)
Enable/disable the joint motor.

_ARGUMENTS_
* __flag__ <kbd>boolean</kbd> -

#### Box2dRevoluteJoint:SetMotorSpeed(speed)
Set the motor speed in radians per second.

_ARGUMENTS_
* __speed__ <kbd>number</kbd> -

#### Box2dRevoluteJoint:GetMotorSpeed()
Get the motor speed in radians per second.

_RETURNS_
* <kbd>float</kbd>

#### Box2dRevoluteJoint:SetMaxMotorTorque(torque)
Set the maximum motor torque, usually in N-m.

_ARGUMENTS_
* __torque__ <kbd>number</kbd> -

#### Box2dRevoluteJoint:GetMaxMotorTorque()

_RETURNS_
* <kbd>float</kbd>

#### Box2dRevoluteJoint:GetMotorTorque(inv_dt)
Get the current motor torque given the inverse time step.
Unit is N*m.

_ARGUMENTS_
* __inv_dt__ <kbd>number</kbd> -

_RETURNS_
* <kbd>float</kbd>

### PrismaticJoint
Prismatic joint definition. This requires defining a line of
motion using an axis and an anchor point. The definition uses local
anchor points and a local axis so that the initial configuration
can violate the constraint slightly. The joint translation is zero
when the local anchor points coincide in world space. Using local
anchors and a local axis helps when saving and loading a game.

```lua
local Box2dPrismaticJointDef = {
    Initialize the bodies, anchors, axis, and reference angle using the world
    anchor and unit world axis.
    void Initialize(b2Body* bodyA, b2Body* bodyB, const b2Vec2& anchor, const b2Vec2& axis);
    --region JointNeeded
    anchor = vmath.vector3(0), for Initialize
    axis = vmath.vector3(0), for Initialize
    --endregion

    --region JointOptional
    The local anchor point relative to bodyA's origin.
    localAnchorA = vmath.vector3(0, 0, 0),

    The local anchor point relative to bodyB's origin.
    localAnchorB = vmath.vector3(0, 0, 0),

    The constrained angle between the bodies: bodyB_angle - bodyA_angle.
    referenceAngle = 0,

    Enable/disable the joint limit.
    enableLimit = false,

    Enable/disable the joint motor.
    enableMotor = false,

    The desired motor speed in radians per second.
    motorSpeed = 0,

    The local translation unit axis in bodyA.
    localAxisA = vmath.vector3(1,0,0),

    The lower translation limit, usually in meters.
    lowerTranslation = 0,

    The upper translation limit, usually in meters.
    upperTranslation = 0,

    The maximum motor torque, usually in N-m.
    maxMotorForce = 0,
    --endregion
}
```

A prismatic joint. This joint provides one degree of freedom: translation
along an axis fixed in bodyA. Relative rotation is prevented. You can
use a joint limit to restrict the range of motion and a joint motor to
drive the motion or to model joint friction.

#### Box2dPrismaticJoint:GetLocalAnchorA()
The local anchor point relative to bodyA's origin.

_RETURNS_
* <kbd>vector3</kbd>

#### Box2dPrismaticJoint:GetLocalAnchorB()
The local anchor point relative to bodyB's origin.

_RETURNS_
* <kbd>vector3</kbd>

#### Box2dPrismaticJoint:GetLocalAxisA()
The local joint axis relative to bodyA.

_RETURNS_
* <kbd>vector3</kbd>

#### Box2dPrismaticJoint:GetReferenceAngle()
Get the reference angle.

_RETURNS_
* <kbd>number</kbd>

#### Box2dPrismaticJoint:GetJointTranslation()
Get the current joint translation, usually in meters.

_RETURNS_
* <kbd>number</kbd>

#### Box2dPrismaticJoint:GetJointSpeed()
Get the current joint translation speed, usually in meters per second.

_RETURNS_
* <kbd>number</kbd>

#### Box2dPrismaticJoint:IsLimitEnabled()
Is the joint limit enabled?

_RETURNS_
* <kbd>boolean</kbd>

#### Box2dPrismaticJoint:EnableLimit(flag)
Enable/disable the joint limit.

_ARGUMENTS_
* __flag__ <kbd>boolean</kbd> -

#### Box2dPrismaticJoint:GetLowerLimit()
Get the lower joint limit, usually in meters.

_RETURNS_
* <kbd>number</kbd>

#### Box2dPrismaticJoint:GetUpperLimit()
Get the upper joint limit, usually in meters.

_RETURNS_
* <kbd>number</kbd>

#### Box2dPrismaticJoint:SetLimits(lower, upper)
Set the joint limits, usually in meters.

_ARGUMENTS_
* __lower__ <kbd>number</kbd> -
* __upper__ <kbd>number</kbd> -

#### Box2dPrismaticJoint:IsMotorEnabled()
Is the joint motor enabled?

_RETURNS_
* <kbd>boolean</kbd>

#### Box2dPrismaticJoint:EnableMotor(flag)
Enable/disable the joint motor.

_ARGUMENTS_
* __flag__ <kbd>boolean</kbd> -

#### Box2dPrismaticJoint:SetMotorSpeed(speed)
Set the motor speed, usually in meters per second.

_ARGUMENTS_
* __speed__ <kbd>number</kbd> -

#### Box2dPrismaticJoint:GetMotorSpeed()
Get the motor speed, usually in meters per second.

_RETURNS_
* <kbd>number</kbd>

#### Box2dPrismaticJoint:SetMaxMotorForce(force)
Set the maximum motor force, usually in N.

_ARGUMENTS_
* __force__ <kbd>number</kbd> -

#### Box2dPrismaticJoint:GetMaxMotorForce()

_RETURNS_
* <kbd>number</kbd>

#### Box2dPrismaticJoint:GetMotorForce(inv_dt)
Get the current motor force given the inverse time step, usually in N.

_ARGUMENTS_
* __inv_dt__ <kbd>number</kbd> -

_RETURNS_
* <kbd>number</kbd>

### DistanceJoint
Distance joint definition. This requires defining an anchor point on both
bodies and the non-zero distance of the distance joint. The definition uses
local anchor points so that the initial configuration can violate the
constraint slightly. This helps when saving and loading a game.

```lua
local Box2dDistanceJointDef = {
    Initialize the bodies, anchors, and rest length using world space anchors.
    The minimum and maximum lengths are set to the rest length.
    void Initialize(b2Body* bodyA, b2Body* bodyB,
    const b2Vec2& anchorA, const b2Vec2& anchorB);

    --region JointNeeded
    anchorA = vmath.vector3(0),
    anchorB = vmath.vector3(0),
    --endregion

    --region JointOptional
    The local anchor point relative to bodyA's origin.
    localAnchorA = vmath.vector3(0, 0, 0),

    The local anchor point relative to bodyB's origin.
    localAnchorB = vmath.vector3(0, 0, 0),

    The rest length of this joint. Clamped to a stable minimum value.
    length = 1,

    Minimum length. Clamped to a stable minimum value.
    minLength = 0,

    Maximum length. Must be greater than or equal to the minimum length.
    maxLength = math.huge,

    The linear stiffness in N/m.
    stiffness = 0.0,

    The linear damping in N*s/m.
    damping = 0.0,
    --endregion
}
```

A distance joint constrains two points on two bodies to remain at a fixed
distance from each other. You can view this as a massless, rigid rod.

#### Box2dDistanceJoint:GetLocalAnchorA()
The local anchor point relative to bodyA's origin.

_RETURNS_
* <kbd>vector3</kbd>

#### Box2dDistanceJoint:GetLocalAnchorB()
The local anchor point relative to bodyB's origin.

_RETURNS_
* <kbd>vector3</kbd>

#### Box2dDistanceJoint:GetLength()
Get the rest length

_RETURNS_
* <kbd>number</kbd>

#### Box2dDistanceJoint:SetLength(length)
Set the rest length

_ARGUMENTS_
* __length__ <kbd>number</kbd> -

_RETURNS_
* <kbd>number</kbd> - Clamped rest length

#### Box2dDistanceJoint:GetMinLength()
Get the minimum length

_RETURNS_
* <kbd>number</kbd>

#### Box2dDistanceJoint:SetMinLength(minLength)
Set the minimum length

_ARGUMENTS_
* __minLength__ <kbd>number</kbd> -

_RETURNS_
* <kbd>number</kbd> - The clamped minimum length

#### Box2dDistanceJoint:GetMaxLength()
Get the maximum length

_RETURNS_
* <kbd>number</kbd>

#### Box2dDistanceJoint:SetMaxLength(maxLength)
Set the maximum length

_ARGUMENTS_
* __maxLength__ <kbd>number</kbd> -

_RETURNS_
* <kbd>number</kbd> - The clamped maximum length

#### Box2dDistanceJoint:GetCurrentLength()
Get the current length

_RETURNS_
* <kbd>number</kbd>

#### Box2dDistanceJoint:SetStiffness(stiffness)
Set/get the linear stiffness in N/m

_ARGUMENTS_
* __stiffness__ <kbd>number</kbd> -

#### Box2dDistanceJoint:GetStiffness()

_RETURNS_
* <kbd>number</kbd>

#### Box2dDistanceJoint:SetDamping(damping)
Set/get linear damping in N*s/m

_ARGUMENTS_
* __damping__ <kbd>number</kbd> -

#### Box2dDistanceJoint:GetDamping()

_RETURNS_
* <kbd>number</kbd>

### PulleyJoint
Pulley joint definition. This requires two ground anchors,
two dynamic body anchor points, and a pulley ratio.

```lua
local Box2dPulleyJointDef = {
    Initialize the bodies, anchors, lengths, max lengths, and ratio using the world anchors.
    void Initialize(b2Body* bodyA, b2Body* bodyB,
        const b2Vec2& groundAnchorA, const b2Vec2& groundAnchorB,
        const b2Vec2& anchorA, const b2Vec2& anchorB,
        float ratio);

    --region JointNeeded
    anchorA = vmath.vector3(0), --for Initialize

    anchorB = vmath.vector3(0), --for Initialize

    The first ground anchor in world coordinates. This point never moves.
    groundAnchorA = vmath.vector3(0), --for Initialize

    The second ground anchor in world coordinates. This point never moves.
    groundAnchorB = vmath.vector3(0), --for Initialize

    The pulley ratio, used to simulate a block-and-tackle.
    ratio = 0, for Initialize
    --endregion

    --region JointOptional
    The local anchor point relative to bodyA's origin.
    localAnchorA = vmath.vector3(0, 0, 0),

    The local anchor point relative to bodyB\'s origin.
    localAnchorB = vmath.vector3(0, 0, 0),

    The a reference length for the segment attached to bodyA.
    lengthA = 0,

    The a reference length for the segment attached to bodyB.
    lengthB = 0
    --endregion
}
```

The pulley joint is connected to two bodies and two fixed ground points.
he pulley supports a ratio such that:
length1 + ratio * length2 <= constant
Yes, the force transmitted is scaled by the ratio.
Warning: the pulley joint can get a bit squirrelly by itself. They often
work better when combined with prismatic joints. You should also cover the
the anchor points with static shapes to prevent one side from going to
zero length.



#### Box2dPulleyJoint:GetGroundAnchorA()
Get the first ground anchor.

_RETURNS_
* <kbd>vector3</kbd>

#### Box2dPulleyJoint:GetGroundAnchorB()
Get the second ground anchor.

_RETURNS_
* <kbd>vector3</kbd>

#### Box2dPulleyJoint:GetLengthA()
Get the current length of the segment attached to bodyA.

_RETURNS_
* <kbd>number</kbd>

#### Box2dPulleyJoint:GetLengthB()
Get the current length of the segment attached to bodyB.

_RETURNS_
* <kbd>number</kbd>

#### Box2dPulleyJoint:GetRatio()
Get the pulley ratio.

_RETURNS_
* <kbd>number</kbd>

#### Box2dPulleyJoint:GetCurrentLengthA()
Get the current length of the segment attached to bodyA.

_RETURNS_
* <kbd>number</kbd>

#### Box2dPulleyJoint:GetCurrentLengthB()
Get the current length of the segment attached to bodyB.

_RETURNS_
* <kbd>number</kbd>

### MouseJoint
Mouse joint definition. This requires a world target point,
tuning parameters, and the time step.

```lua
local Box2dMouseJointDef = {
    --region JointNeeded
    --endregion

    --region JointOptional
    The linear stiffness in N/m
    stiffness = 0,

    The linear damping in N*s/m
    damping = 0,

    The initial world target point. This is assumed
    to coincide with the body anchor initially.
    target = vmath.vector3(0),

    The maximum constraint force that can be exerted
    to move the candidate body. Usually you will express
    as some multiple of the weight (multiplier * mass * gravity).
    maxForce = 0
    --endregion
}
```
A mouse joint is used to make a point on a body track a
specified world point. This a soft constraint with a maximum
force. This allows the constraint to stretch and without
applying huge forces.
NOTE: this joint is not documented in the manual because it was
developed to be used in the testbed. If you want to learn how to
use the mouse joint, look at the testbed.


#### Box2dMouseJoint:SetTarget(target)
Use this to update the target point.

_ARGUMENTS_
* __target__ <kbd>vector3</kbd> -

#### Box2dMouseJoint:GetTarget()

_RETURNS_
* <kbd>vector3</kbd>

#### Box2dMouseJoint:SetMaxForce(force)
Set/get the maximum force in Newtons.

_ARGUMENTS_
* __force__ <kbd>number</kbd> -

#### Box2dMouseJoint:GetMaxForce()

_RETURNS_
* <kbd>number</kbd>

#### Box2dMouseJoint:SetStiffness(stiffness)
Set/get the linear stiffness in N/m

_ARGUMENTS_
* __stiffness__ <kbd>number</kbd> -

#### Box2dMouseJoint:GetStiffness()

_RETURNS_
* <kbd>number</kbd>

#### Box2dMouseJoint:SetDamping(damping)
Set/get linear damping in N*s/m

_ARGUMENTS_
* __damping__ <kbd>number</kbd> -

#### Box2dMouseJoint:GetDamping()

_RETURNS_
* <kbd>number</kbd>

### GearJoint
Gear joint definition. This definition requires two existing
revolute or prismatic joints (any combination will work).
@_Warning:_ bodyB on the input joints must both be dynamic

```lua
local Box2dGearJointDef = {
    --region JointNeeded
    The first revolute/prismatic joint attached to the gear joint.
    @type Box2dJoint
    joint1 = nil,

    The second revolute/prismatic joint attached to the gear joint.
    @type Box2dJoint
    joint2 = nil,
    --endregion

    --region JointOptional
    The gear ratio.
    @see Box2dGearJoint for explanation.
    ratio = 0
    --endregion
}
```
A gear joint is used to connect two joints together. Either joint
can be a revolute or prismatic joint. You specify a gear ratio
to bind the motions together:
coordinate1 + ratio * coordinate2 = constant
The ratio can be negative or positive. If one joint is a revolute joint
and the other joint is a prismatic joint, then the ratio will have units
of length or units of 1/length.
_Warning:_ You have to manually destroy the gear joint if joint1 or joint2
is destroyed.

#### Box2dGearJoint:GetJoint1()
Get the first joint.

_RETURNS_
* <kbd>Box2dJoint</kbd>

#### Box2dGearJoint:GetJoint2()
Get the second joint.

_RETURNS_
* <kbd>Box2dJoint</kbd>

#### Box2dGearJoint:SetRatio(ratio)
Set/Get the gear ratio.

_ARGUMENTS_
* __ratio__ <kbd>number</kbd> -

#### Box2dGearJoint:GetRatio()

_RETURNS_
* <kbd>number</kbd>

### WheelJoint
Wheel joint definition. This requires defining a line of
motion using an axis and an anchor point. The definition uses local
anchor points and a local axis so that the initial configuration
can violate the constraint slightly. The joint translation is zero
when the local anchor points coincide in world space. Using local
anchors and a local axis helps when saving and loading a game.

```lua
local Box2dWheelJointDef = {
    Initialize the bodies, anchors, axis, and reference angle using the world
    anchor and world axis.
    void Initialize(b2Body* bodyA, b2Body* bodyB, const b2Vec2& anchor, const b2Vec2& axis);
    --region JointNeeded
    anchor = vmath.vector3(0), --for Initialize
    axis = vmath.vector3(0), --for Initialize
    --endregion

    --region JointOptional
    The local anchor point relative to bodyA's origin.
    localAnchorA = vmath.vector3(0, 0, 0),

    The local anchor point relative to bodyB\'s origin.
    localAnchorB = vmath.vector3(0, 0, 0),

    Enable/disable the joint limit.
    enableLimit = false,

Enable/disable the joint motor.
    enableMotor = false,

    The desired motor speed in radians per second.
    motorSpeed = 0,

    The maximum motor torque, usually in N-m.
    maxMotorTorque = 0,

    The local translation axis in bodyA.
    localAxisA = vmath.vector3(0),

The lower translation limit, usually in meters.
    lowerTranslation = 0,

The upper translation limit, usually in meters.
    upperTranslation = 0,

Suspension stiffness. Typically in units N/m.
    stiffness = 0,

Suspension damping. Typically in units of N*s/m.
    damping = 0,
    --endregion
}
```
A wheel joint. This joint provides two degrees of freedom: translation
along an axis fixed in bodyA and rotation in the plane. In other words, it is a point to
line constraint with a rotational motor and a linear spring/damper. The spring/damper is
initialized upon creation. This joint is designed for vehicle suspensions.



#### Box2dWheelJoint:GetLocalAnchorA()
The local anchor point relative to bodyA's origin.

_RETURNS_
* <kbd>vector3</kbd>

#### Box2dWheelJoint:GetLocalAnchorB()
The local anchor point relative to bodyB's origin.

_RETURNS_
* <kbd>vector3</kbd>

#### Box2dWheelJoint:GetLocalAxisA()
The local joint axis relative to bodyA.

_RETURNS_
* <kbd>vector3</kbd>

#### Box2dWheelJoint:GetJointTranslation()
Get the current joint translation, usually in meters.

_RETURNS_
* <kbd>number</kbd>

#### Box2dWheelJoint:GetJointLinearSpeed()
Get the current joint linear speed, usually in meters per second.

_RETURNS_
* <kbd>number</kbd>

#### Box2dWheelJoint:GetJointAngle()
Get the current joint angle in radians.

_RETURNS_
* <kbd>number</kbd>

#### Box2dWheelJoint:GetJointAngularSpeed()
Get the current joint angular speed in radians per second.

_RETURNS_
* <kbd>number</kbd>

#### Box2dWheelJoint:IsLimitEnabled()
Is the joint limit enabled?

_RETURNS_
* <kbd>boolean</kbd>

#### Box2dWheelJoint:EnableLimit(flag)
Enable/disable the joint translation limit.

_ARGUMENTS_
* __flag__ <kbd>boolean</kbd> -

#### Box2dWheelJoint:GetLowerLimit()
Get the lower joint translation limit, usually in meters.

_RETURNS_
* <kbd>number</kbd>

#### Box2dWheelJoint:GetUpperLimit()
Get the upper joint translation limit, usually in meters.

_RETURNS_
* <kbd>number</kbd>

#### Box2dWheelJoint:SetLimits(lower, upper)
Set the joint translation limits, usually in meters.

_ARGUMENTS_
* __lower__ <kbd>number</kbd> -
* __upper__ <kbd>number</kbd> -

#### Box2dWheelJoint:IsMotorEnabled()
Is the joint motor enabled?

_RETURNS_
* <kbd>boolean</kbd>

#### Box2dWheelJoint:EnableMotor(flag)
Enable/disable the joint motor.

_ARGUMENTS_
* __flag__ <kbd>boolean</kbd> -

#### Box2dWheelJoint:SetMotorSpeed(speed)
Set the motor speed, usually in radians per second.

_ARGUMENTS_
* __speed__ <kbd>number</kbd> -

#### Box2dWheelJoint:GetMotorSpeed()
Get the motor speed, usually in radians per second.

_RETURNS_
* <kbd>number</kbd>

#### Box2dWheelJoint:SetMaxMotorTorque(torque)
Set/Get the maximum motor force, usually in N-m.

_ARGUMENTS_
* __torque__ <kbd>number</kbd> -

#### Box2dWheelJoint:GetMaxMotorTorque()

_RETURNS_
* <kbd>number</kbd>

#### Box2dWheelJoint:GetMotorTorque(inv_dt)
Get the current motor torque given the inverse time step, usually in N-m.

_ARGUMENTS_
* __inv_dt__ <kbd>number</kbd> -

_RETURNS_
* <kbd>number</kbd>

#### Box2dWheelJoint:SetStiffness(stiffness)
Access spring stiffness

_ARGUMENTS_
* __stiffness__ <kbd>number</kbd> -

#### Box2dWheelJoint:GetStiffness()

_RETURNS_
* <kbd>number</kbd>

#### Box2dWheelJoint:SetDamping(damping)
Access damping

_ARGUMENTS_
* __damping__ <kbd>number</kbd> -

#### Box2dWheelJoint:GetDamping()

_RETURNS_
* <kbd>number</kbd>

### WeldJoint
Weld joint definition. You need to specify local anchor points
where they are attached and the relative body angle. The position
of the anchor points is important for computing the reaction torque.

```lua
local Box2WeldJointDef = {
    -- Initialize the bodies, anchors, reference angle, stiffness, and damping.
    -- @param bodyA the first body connected by this joint
    -- @param bodyB the second body connected by this joint
    -- @param anchor the point of connection in world coordinates
    --void Initialize(b2Body* bodyA, b2Body* bodyB, const b2Vec2& anchor);

    --region JointNeeded
    anchor = vmath.vector3(0), --for Initialize
    --endregion

    --region JointOptional
    The local anchor point relative to bodyA's origin.
    localAnchorA = vmath.vector3(0, 0, 0),

    The local anchor point relative to bodyB\'s origin.
    localAnchorB = vmath.vector3(0, 0, 0),

    The bodyB angle minus bodyA angle in the reference state (radians).
    referenceAngle = 0,

    The rotational stiffness in N*m
    Disable softness with a value of 0
    stiffness = 0,

    The rotational damping in N*m*s
    damping = 0,
    --endregion
}
```

A weld joint essentially glues two bodies together. A weld joint may
distort somewhat because the island constraint solver is approximate.



#### Box2dWeldJoint:GetLocalAnchorA()
The local anchor point relative to bodyA's origin.

_RETURNS_
* <kbd>vector3</kbd>

#### Box2dWeldJoint:GetLocalAnchorB()
The local anchor point relative to bodyB's origin.

_RETURNS_
* <kbd>vector3</kbd>

#### Box2dWeldJoint:GetReferenceAngle()
Get the reference angle.

_RETURNS_
* <kbd>number</kbd>

#### Box2dWeldJoint:SetStiffness(hz)
Set/get stiffness in N*m

_ARGUMENTS_
* __hz__ <kbd>number</kbd> -

#### Box2dWeldJoint:GetStiffness()

_RETURNS_
* <kbd>number</kbd>

#### Box2dWeldJoint:SetDamping(damping)
Set/get damping in N*m*s

_ARGUMENTS_
* __damping__ <kbd>number</kbd> -

#### Box2dWeldJoint:GetDamping()

_RETURNS_
* <kbd>number</kbd>

### FrictionJoint
Friction joint definition.

```lua
local Box2FrictionJointDef = {
    -- Initialize the bodies, anchors, axis, and reference angle using the world
    -- anchor and world axis.
    --void Initialize(b2Body* bodyA, b2Body* bodyB, const b2Vec2& anchor);
    --region JointNeeded
    anchor = vmath.vector3(0), --for Initialize
    --endregion

    --region JointOptional
    The local anchor point relative to bodyA's origin.
    localAnchorA = vmath.vector3(0, 0, 0),

    The local anchor point relative to bodyB's origin.
    localAnchorB = vmath.vector3(0, 0, 0),

    The maximum friction force in N.
    maxForce = 0,

    The maximum friction torque in N-m.
    maxTorque = 0,
    --endregion
}
```
Friction joint. This is used for top-down friction.
It provides 2D translational friction and angular friction.



#### Box2FrictionJoint:GetLocalAnchorA()
The local anchor point relative to bodyA's origin.

_RETURNS_
* <kbd>vector3</kbd>

#### Box2FrictionJoint:GetLocalAnchorB()
The local anchor point relative to bodyB's origin.

_RETURNS_
* <kbd>vector3</kbd>

#### Box2FrictionJoint:SetMaxForce(force)
Set the maximum friction force in N.

_ARGUMENTS_
* __force__ <kbd>number</kbd> -

#### Box2FrictionJoint:GetMaxForce()
Get the maximum friction force in N.

_RETURNS_
* <kbd>number</kbd>

#### Box2FrictionJoint:SetMaxTorque(torque)
Set the maximum friction torque in N*m.

_ARGUMENTS_
* __torque__ <kbd>number</kbd> -

#### Box2FrictionJoint:GetMaxTorque()
Get the maximum friction torque in N*m.

_RETURNS_
* <kbd>number</kbd>

### MotorJoint
Motor joint definition.

```lua
local Box2MotorJointDef = {
    -- Initialize the bodies and offsets using the current transforms.
    --void Initialize(b2Body* bodyA, b2Body* bodyB);
    --region JointNeeded
    --endregion

    --region JointOptional
    The maximum motor force in N.
    maxForce = vmath.vector3(0, 0, 0),

    The maximum motor torque in N-m.
    maxTorque = vmath.vector3(0, 0, 0),

    Position of bodyB minus the position of bodyA, in bodyA's frame, in meters.
    linearOffset = 0,

    The bodyB angle minus bodyA angle in radians.
    angularOffset = 0,

    Position correction factor in the range [0,1].
    correctionFactor = 0,
    --endregion
}
```

A motor joint is used to control the relative motion
between two bodies. A typical usage is to control the movement
of a dynamic body with respect to the ground.


#### Box2dMotorJoint:SetLinearOffset(linearOffset)
Set/get the target linear offset, in frame A, in meters.
* __linearOffset__ <kbd>vector3</kbd> -

#### Box2dMotorJoint:GetLinearOffset()

_RETURNS_
* <kbd>vector3</kbd>

#### Box2dMotorJoint:SetAngularOffset(angularOffset)
Set/get the target angular offset, in radians.

_ARGUMENTS_
* __angularOffset__ <kbd>number</kbd> -

#### Box2dMotorJoint:GetAngularOffset()

_RETURNS_
* <kbd>number</kbd>

#### Box2dMotorJoint:SetMaxForce(force)
Set the maximum friction force in N.

_ARGUMENTS_
* __force__ <kbd>number</kbd> -

#### Box2dMotorJoint:GetMaxForce()
Get the maximum friction force in N.

_RETURNS_
* <kbd>number</kbd>

#### Box2dMotorJoint:SetMaxTorque(torque)
Set the maximum friction torque in N*m.

_ARGUMENTS_
* __torque__ <kbd>number</kbd> -

#### Box2dMotorJoint:GetMaxTorque()
Get the maximum friction torque in N*m.

_RETURNS_
* <kbd>number</kbd>

#### Box2dMotorJoint:SetCorrectionFactor(factor)
Set the position correction factor in the range [0,1].

_ARGUMENTS_
* __factor__ <kbd>number</kbd> -

#### Box2dMotorJoint:GetCorrectionFactor()
Get the position correction factor in the range [0,1].

_RETURNS_
* <kbd>number</kbd>

### Box2dProfile <kbd>table</kbd>
Profiling data. Times are in milliseconds.
Returned by world:GetProfile().

_FIELDS_
* __step__ <kbd>number</kbd> -
* __collide__ <kbd>number</kbd> -
* __solve__ <kbd>number</kbd> -
* __solveInit__ <kbd>number</kbd> -
* __solveVelocity__ <kbd>number</kbd> -
* __solvePosition__ <kbd>number</kbd> -
* __broadphase__ <kbd>number</kbd> -
* __solveTOI__ <kbd>number</kbd> -

### Box2dMassData <kbd>table</kbd>
This holds the mass data computed for a shape.

_FIELDS_
* __mass__ <kbd>number</kbd> - The mass of the shape, usually in kilograms.
* __center__ <kbd>vector3</kbd> - The position of the shape's centroid relative to the shape's origin.
* __I__ <kbd>number</kbd> -  The rotational inertia of the shape about the local origin.
