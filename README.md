
# Box2D for Defold

Box2D lua bindings for Defold Game Engine.

Try to keep lua api same as c++ api when in possible.


If you like that extension. You can support me on patreon.
It will help me make more items for defold.

[![](https://c5.patreon.com/external/logo/become_a_patron_button.png)](https://www.patreon.com/d954mas)

<img src="https://github.com/d954mas/defold-box2d/blob/master/files/screenshot.png">
demo:https://d954mas.github.io/defold-box2d/



# Table of content
- [Box2D for Defold](#box2d-for-defold)
  * [Installation](#installation)
  * [Box2d](#box2d)
  * [Limitations](#limitations)
  * [API](#api)
    + [Extension](#extension)
    + [World](#world)
    + [Contact](#box2dcontact)
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
    + [Box2dManifold](#box2dmanifold)
    + [Box2dMWorldManifold](#box2dworldmanifold)
    + [Box2dProfile](#box2dprofile)
    + [Box2dMassData](#box2dmassdata)


## Installation

1)Add defold-box2d in your own project as a Defold library dependency. Open your game.project file and in the dependencies field under project add:
https://github.com/d954mas/defold-box2d/archive/refs/tags/0.9.zip

2)Remove defold engine box2d. If not remove there will be conflict between this box2d and engine box2d.
use manifest.appmanifest.  Open your game.project file and in the App Manifest field under Native Extension add manifest.

You can generate manifest yourself https://britzl.github.io/manifestation/ or use /box2d/manifest.appmanifest

## Box2d
If you need info about how box2d work read it documentation.
https://box2d.org/documentation/

Box2d version: 2.4.1 

## Limitations

1)No binding for b2Vec2. Use defold vector(vmath.vector3)

2)No binding b2Shape. Use table for shape when create fixture.

3)b2Assert. #define b2Assert(A) assert(A) . Engine will crashed if b2Assert happened.

4)No binding some b2World functions.

	void SetDestructionListener(b2DestructionListener* listener);
	void SetContactFilter(b2ContactFilter* filter);
	b2Contact* GetContactList();
	const b2ContactManager& GetContactManager() const;

5)No binding some b2Fixture functions.

	not suppor filter in fixture def.
	b2Shape* GetShape();
	void SetFilterData(const b2Filter& filter);
	const b2Filter& GetFilterData() const;
	bool RayCast(b2RayCastOutput* output, const b2RayCastInput& input, int32 childIndex) const;
	const b2AABB& GetAABB(int32 childIndex) const;
	
6)No binding some b2Body functions.

	b2JointEdge* GetJointList () Get the list of all joints attached to this body
	b2ContactEdge* GetContactList();
	
7)No binding some b2Joint functions.

	virtual void Draw(b2Draw* draw) const;
	
8)No binding some b2Contact functions.
    b2Contact* GetNext();

## API
Support emmylua. box2d_header.lua

### Extension
```lua 
box2d = {}
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

box2d.b2Manifold_Type = {
    e_circles = 0, e_faceA = 1,
    e_faceB = 2
}

---@param gravity vector3|nil the world gravity vector.
---@return Box2dWorld
function box2d.NewWorld(gravity) end

---@param data table
---@return Box2dDebugDraw
function box2d.NewDebugDraw(data) end

--- Utility to compute linear stiffness values from frequency and damping ratio
---@param frequencyHertz number
---@param dampingRatio number
---@param bodyA Box2dBody
---@param bodyB Box2dBody
---@return number stiffness
---@return number damping
function box2d.b2LinearStiffness(frequencyHertz, dampingRatio, bodyA, bodyB) end

--- Utility to compute rotational stiffness values frequency and damping ratio
---@param frequencyHertz number
---@param dampingRatio number
---@param bodyA Box2dBody
---@param bodyB Box2dBody
---@return number stiffness
---@return number damping
function box2d.b2AngularStiffness(frequencyHertz, dampingRatio, bodyA, bodyB) end


--- Use InitializeJoint methods to create b2JointDef and call b2JointDef::Initialize(...) if
--- joint have such method

--- Initialize the bodies, anchors, axis, and reference angle using the world
--- anchor and unit world axis.
---@param bodyA Box2dBody
---@param bodyB Box2dBody
---@param anchor vector3
---@param axis vector3
---@return Box2dPrismaticJointDef
function box2d.InitializePrismaticJointDef(bodyA, bodyB, anchor, axis) end

--- Initialize the bodies, anchors, and rest length using world space anchors.
--- The minimum and maximum lengths are set to the rest length.
---@param bodyA Box2dBody
---@param bodyB Box2dBody
---@param anchorA vector3
---@param anchorB vector3
---@return Box2dDistanceJointDef
function box2d.InitializeDistanceJointDef(bodyA, bodyB, anchorA, anchorB) end

--- Initialize the bodies, anchors, lengths, max lengths, and ratio using the world anchors.
---@param bodyA Box2dBody
---@param bodyB Box2dBody
---@param groundAnchorA vector3
---@param groundAnchorB vector3
---@param anchorA vector3
---@param anchorB vector3
---@param ratio number
---@return Box2dPulleyJointDef
function box2d.InitializePulleyJointDef(bodyA, bodyB, groundAnchorA, groundAnchorB, anchorA, anchorB, ratio) end

---@param bodyA Box2dBody
---@param bodyB Box2dBody
---@return Box2dMouseJointDef
function box2d.InitializeMouseJointDef(bodyA, bodyB) end

---@param bodyA Box2dBody
---@param bodyB Box2dBody
---@param joint1 Box2dJoint
---@param joint2 Box2dBody
---@return Box2dGearJoint
function box2d.InitializeGearJointDef(bodyA, bodyB, joint1, joint2) end

--- Initialize the bodies, anchors, axis, and reference angle using the world
--- anchor and world axis.
---@param bodyA Box2dBody
---@param bodyB Box2dBody
---@param anchor vector3
---@param axis vector3
---@return Box2dWheelJointDef
function box2d.InitializeWheelJointDef(bodyA, bodyB, anchor, axis) end

--- Initialize the bodies, anchors, reference angle, stiffness, and damping.
---@param bodyA Box2dBody
---@param bodyB Box2dBody
---@param anchor vector3
---@return Box2dWeldJointDef
function box2d.InitializeWeldJointDef(bodyA, bodyB, anchor) end

--- Initialize the bodies, anchors, axis, and reference angle using the world
--- anchor and world axis.
---@param bodyA Box2dBody
---@param bodyB Box2dBody
---@param anchor vector3
---@return Box2FrictionJointDef
function box2d.InitializeFrictionJointDef(bodyA, bodyB, anchor) end

--- Initialize the bodies and offsets using the current transforms.
---@param bodyA Box2dBody
---@param bodyB Box2dBody
---@return Box2dMotorJointDef
function box2d.InitializeMotorJointDef(bodyA, bodyB) end
```

### World
A physics world is a collection of bodies, fixtures, and constraints that interact together. Box2D supports the creation of multiple worlds, but this is usually not necessary or desirable.
Destroy world, world:Destroy() when you do not need it any more.

```lua
---@class Box2dWorld
local Box2dWorld = {}

--- Register a contact event listener.
--- listener = {
---    BeginContact = function (contact) end,
---    EndContact = function(contact) end,
---    PreSolve = function(contact, old_manifold) end,
---    PostSolve = function(contact,impulse) end
--- }
---@param listener table|nil
function Box2dWorld:SetContactListener(listener) end

--- Register a routine for debug drawing. The debug draw functions are called
--- inside with b2World:DebugDraw method. The debug draw object is owned
--- by you and must remain in scope.
---@param draw Box2dDebugDraw|nil
function Box2dWorld:SetDebugDraw(draw) end

---Create a rigid body given a definition.
---warning This function is locked during callbacks.
---@param bodyDef Box2dBodyDef
---@return Box2dBody
function Box2dWorld:CreateBody(bodyDef) end

--- Destroy a rigid body given a definition.
--- warning This automatically deletes all associated shapes and joints.
--- warning This function is locked during callbacks.
---@param body Box2dBody
function Box2dWorld:DestroyBody(body) end

--- Create a joint to constrain bodies together.
--- This may cause the connected bodies to cease colliding.
--- warning This function is locked during callbacks.
---@param def Box2dJointDef
---@return Box2dJoint
function Box2dWorld:CreateJoint(def) end

--- Destroy a joint. This may cause the connected bodies to begin colliding.
--- warning This function is locked during callbacks.
---@param joint Box2dJoint
function Box2dWorld:DestroyJoint(joint) end

--- Take a time step. This performs collision detection, integration,
--- and constraint solution.
---@param timeStep number the amount of time to simulate, this should not vary.
---@param velocityIterations number for the velocity constraint solver.
---@param positionIterations number for the position constraint solver.
function Box2dWorld:Step(timeStep, velocityIterations, positionIterations) end

--- Manually clear the force buffer on all bodies. By default, forces are cleared automatically
--- after each call to Step. The default behavior is modified by calling SetAutoClearForces.
--- The purpose of this function is to support sub-stepping. Sub-stepping is often used to maintain
--- a fixed sized time step under a variable frame-rate.
--- When you perform sub-stepping you will disable auto clearing of forces and instead call
--- ClearForces after all sub-steps are complete in one pass of your game loop.
--- @see SetAutoClearForces
function Box2dWorld:ClearForces() end

--- Call this to draw shapes and other debug draw data. This is intentionally non-const.
function Box2dWorld:DebugDraw() end

---Get the world body list. With the returned body, use b2Body:GetNext() to get the next body in the world list.
---A nil body indicates the end of the list.
---@return Box2dBody|nil the head of the world body list.
function Box2dWorld:GetBodyList() end

--- Ray-cast the world for all fixtures in the path of the ray. Your callback
--- controls whether you get the closest point, any point, or n-points.
--- The ray-cast ignores shapes that contain the starting point.
--- @param callback function(Box2dFixture fixture, vector3 point, vector3 normal, float fraction)
--- @param point1 vector3 ray starting point
--- @param point2 vector3 ray ending point
function Box2dWorld:RayCast(callback, point1, point2) end

---Get the world joint list. With the returned joint, use b2Joint:GetNext() to get the next joint in the world list.
---A nil joint indicates the end of the list.
---@return Box2dJoint|nil the head of the world joint list.
function Box2dWorld:GetJointList() end

--- Enable/disable sleep.
function Box2dWorld:SetAllowSleeping(flag) end
---@return boolean
function Box2dWorld:GetAllowSleeping() end

--- Enable/disable warm starting. For testing.
function Box2dWorld:SetWarmStarting(flag) end
---@return boolean
function Box2dWorld:GetWarmStarting() end

--- Enable/disable continuous physics. For testing.
function Box2dWorld:SetContinuousPhysics(flag) end
---@return boolean
function Box2dWorld:GetContinuousPhysics() end

--- Enable/disable single stepped continuous physics. For testing.
function Box2dWorld:SetSubStepping(flag) end
---@return boolean
function Box2dWorld:GetSubStepping() end


---@return number the number of broad-phase proxies.
function Box2dWorld:GetProxyCount() end

---@return number the number of bodies.
function Box2dWorld:GetBodyCount() end

---@return number the number of joints
function Box2dWorld:GetJointCount() end

---@return number the number of contacts (each may have 0 or more contact points).
function Box2dWorld:GetContactCount() end

---@return number the height of the dynamic tree.
function Box2dWorld:GetTreeHeight() end

---@return number the balance of the dynamic tree.
function Box2dWorld:GetTreeBalance() end

--- Get the quality metric of the dynamic tree. The smaller the better.
--- The minimum is 1.
---@return number
function Box2dWorld:GetTreeQuality() end

--- Change the global gravity vector.
function Box2dWorld:SetGravity() end

--- Get the global gravity vector.
---@return vector3
function Box2dWorld:GetGravity() end

--- Is the world locked (in the middle of a time step).
---@return boolean
function Box2dWorld:IsLocked() end

--- Set flag to control automatic clearing of forces after each time step.
function Box2dWorld:SetAutoClearForces(flag) end

---  Get the flag that controls automatic clearing of forces after each time step.
---@return boolean
function Box2dWorld:GetAutoClearForces() end

--- Shift the world origin. Useful for large worlds.
--- The body shift formula is: position -= newOrigin
---@param newOrigin vector3 the new origin with respect to the old origin
function Box2dWorld:ShiftOrigin(newOrigin) end

--- Get the current profile.
---@return Box2dProfile
function Box2dWorld:GetProfile() end

--- Dump the world into the log file.
--- warning this should be called outside of a time step.
function Box2dWorld:Dump() end

--- Destroy world
function Box2dWorld:Destroy() end
```

### Box2dContact
The class manages contact between two shapes. A contact exists for each overlapping
AABB in the broad-phase (except if filtered). Therefore a contact object may exist
that has no contact points.

```lua
---@class Box2dContact
local Box2dContact = {}

--- Get the local manifold.
---@return Box2dManifold
function Box2dContact:GetManifold() end

--- Get the world manifold.
---@return Box2dWorldManifold
function Box2dContact:GetWorldManifold() end

--- Is this contact touching?
---@return boolean
function Box2dContact:IsTouching() end

--- Enable/disable this contact. This can be used inside the pre-solve
--- contact listener. The contact is only disabled for the current
--- time step (or sub-step in continuous collisions).
---@param flag boolean
function Box2dContact:SetEnabled(flag) end

--- Has this contact been disabled?
---@return boolean
function Box2dContact:IsEnabled() end

--- Get fixture A in this contact.
---@return Box2dFixture
function Box2dContact:GetFixtureA() end

--- Get the child primitive index for fixture A.
---@return number
function Box2dContact:GetChildIndexA() end

--- Get fixture B in this contact.
---@return Box2dFixture
 function Box2dContact:GetFixtureB() end

--- Get the child primitive index for fixture B.
---@return number
function Box2dContact:GetChildIndexB() end

--- Override the default friction mixture. You can call this in b2ContactListener::PreSolve.
--- This value persists until set or reset.
---@param friction number
function Box2dContact:SetFriction(friction) end

--- Get the friction.
---@return number
function Box2dContact:GetFriction() end

--- Reset the friction mixture to the default value.
function Box2dContact:ResetFriction() end

--- Override the default restitution mixture. You can call this in b2ContactListener::PreSolve.
--- The value persists until you set or reset.
---@param restitution number
function Box2dContact:SetRestitution(restitution) end

--- Get the restitution.
---@return number
function Box2dContact:GetRestitution() end

--- Reset the restitution to the default value.
function Box2dContact:ResetRestitution() end

--- Override the default restitution velocity threshold mixture. You can call this in b2ContactListener::PreSolve.
--- The value persists until you set or reset.
---@param threshold number
function Box2dContact:SetRestitutionThreshold(threshold) end

--- Get the restitution threshold.
---@return number
function Box2dContact:GetRestitutionThreshold() end

--- Reset the restitution threshold to the default value.
function Box2dContact:ResetRestitutionThreshold() end

--- Set the desired tangent speed for a conveyor belt behavior. In meters per second.
---@param speed number
function Box2dContact:SetTangentSpeed(speed) end

--- Get the desired tangent speed. In meters per second.
---@return number
function Box2dContact:GetTangentSpeed() end
```


### DebugDraw
register this class with a b2World to provide debug drawing of physics
entities in your game.
Destroy when not need it anymore
```lua
--region Box2dDebugDraw
---@class Box2dDebugDraw
local Box2dDebugDraw = {}

--- Set the drawing flags.
---@param flags number
function Box2dDebugDraw:SetFlags(flags) end

--- Get the drawing flags.
---@return number
function Box2dDebugDraw:GetFlags() end

--- Append flags to the current flags.
---@param flags number
function Box2dDebugDraw:AppendFlags(flags) end

--- Clear flags from the current flags.
---@param flags number
function Box2dDebugDraw:ClearFlags(flags) end

---Destroy, free memory
function Box2dDebugDraw:Destroy() end
```

Creation
```lua
box2d.NewDebugDraw({
	DrawPolygon = function(vertices,color) __draw_polygon(physics_scale,vertices,color) end,
	DrawSolidPolygon = function(vertices,color) __draw_polygon(physics_scale,vertices,color) end,
	DrawCircle = function(center,radius,color) __draw_circle(physics_scale,center,radius,nil,color) end,
	DrawSolidCircle = function(center,radius,axis,color) __draw_circle(physics_scale,center,radius,axis,color) end,
	DrawSegment = function(p1,p2,color) __draw_segment(physics_scale,p1,p2,color) end,
})
```

### Shape
No binding for b2Shape. Use table with data when need a shape, for example when create fixture.
```lua
---@class Box2dShape
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

    --polygon box
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
---@class Box2dFixtureDef
local Box2dFixtureDef = {
    -- The shape, this must be set.
    ---@type Box2dShape
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
```lua
---@class Box2dFixture
local Box2dFixture = {}

---@return number box2d.b2Shape
function Box2dFixture:GetType() end

--- Set if this fixture is a sensor.
---@param sensor boolean
function Box2dFixture:SetSensor(sensor) end

---Is this fixture a sensor (non-solid)?
---@return boolean the true if the shape is a sensor.
function Box2dFixture:IsSensor() end

--- Call this if you want to establish collision that was previously disabled by b2ContactFilter::ShouldCollide.
function Box2dFixture:Refilter() end

--- Get the parent body of this fixture. This is nil if the fixture is not attached.
---@return Box2dBody the parent body
function Box2dFixture:GetBody() end

--- Get the next fixture in the parent body's fixture list.
---@return Box2dFixture|nil
function Box2dFixture:GetNext() end

--- Get the user data that was assigned in the fixture definition. Use this to
--- store your application specific data.
---@return table|nil
function Box2dFixture:GetUserData() end

--- Set the user data. Use this to
--- store your application specific data.
---@param userdata table|nil
function Box2dFixture:SetUserData(userdata) end

--- Test a point for containment in this fixture.
---@param point vector3 a point in world coordinates.
function Box2dFixture:TestPoint(point) end

--- Get the mass data for this fixture. The mass data is based on the density and
--- the shape. The rotational inertia is about the shape's origin. This operation
--- may be expensive.
---@return Box2dMassData
function Box2dFixture:GetMassData() end

--- Get the density of this fixture.
---@return number
function Box2dFixture:GetDensity() end

--- Set the density of this fixture. This will _not_ automatically adjust the mass
--- of the body. You must call b2Body::ResetMassData to update the body's mass.
---@param density number
function Box2dFixture:SetDensity(density) end

--- Get the coefficient of friction.
---@return number
function Box2dFixture:GetFriction() end

--- Set the coefficient of friction. This will _not_ change the friction of
--- existing contacts.
---@param friction number
function Box2dFixture:SetFriction(friction) end

--- Get the coefficient of restitution.
---@return number
function Box2dFixture:GetRestitution() end

--- Set the coefficient of restitution. This will _not_ change the restitution of
--- existing contacts.
---@param restitution number
function Box2dFixture:SetRestitution(restitution) end

--- Get the restitution velocity threshold.
---@return number
function Box2dFixture:GetRestitutionThreshold() end

--- Set the restitution threshold. This will _not_ change the restitution threshold of
--- existing contacts.
---@param threshold number
function Box2dFixture:SetRestitutionThreshold(threshold) end

--- Dump this fixture to the log file.
---@param bodyIndex number
function Box2dFixture:Dump(bodyIndex) end
```

### BodyDef
A body definition holds all the data needed to construct a rigid body.
You can safely re-use body definitions. Shapes are added to a body after construction.
```lua
---@class Box2dBodyDef
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
    -- @warning You should use this flag sparingly since it increases processing time.
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
```lua
--- A rigid body. These are created via world:CreateBody.
---@class Box2dBody
local Box2dBody = {}

--- Creates a fixture and attach it to this body. Use this function if you need
--- to set some fixture parameters, like friction. Otherwise you can create the
--- fixture directly from a shape.
--- If the density is non-zero, this function automatically updates the mass of the body.
--- Contacts are not created until the next time step.
--- warning This function is locked during callbacks.
---@param def Box2dFixtureDef
---@return Box2dFixture
function Box2dBody:CreateFixture(def) end

--- Creates a fixture from a shape and attach it to this body.
--- This is a convenience function. Use b2FixtureDef if you need to set parameters
--- like friction, restitution, user data, or filtering.
--- If the density is non-zero, this function automatically updates the mass of the body.
--- warning This function is locked during callbacks.
---@param shape Box2dShape
---@param density number the shape density (set to zero for static bodies)
---@return Box2dFixture
function Box2dBody:CreateFixture(shape, density) end

--- Destroy a fixture. This removes the fixture from the broad-phase and
--- destroys all contacts associated with this fixture. This will
--- automatically adjust the mass of the body if the body is dynamic and the
--- fixture has positive density.
--- All fixtures attached to a body are implicitly destroyed when the body is destroyed.
--- warning This function is locked during callbacks.
---@param fixture Box2dFixture
function Box2dBody:DestroyFixture(fixture) end

--- Set the position of the body's origin and rotation.
--- Manipulating a body's transform may cause non-physical behavior.
--- Note: contacts are updated on the next call to b2World::Step.
---@param position vector3 the world position of the body's local origin.
---@param angle number|nil the world rotation in radians. If nil use current angle
function Box2dBody:SetTransform(position, angle) end

--- Get the body transform for the body's origin.
---@return vector3 position
---@return number angle
function Box2dBody:GetTransform() end

--- Get the world body origin position.
---@return vector3
function Box2dBody:GetPosition() end

--- Get the angle in radians.
---@return number
function Box2dBody:GetAngle() end

--- Get the world position of the center of mass.
---@return vector3
function Box2dBody:GetWorldCenter() end

--- Get the local position of the center of mass.
---@return vector3
function Box2dBody:GetLocalCenter() end

--- Set the linear velocity of the center of mass.
---@param velocity vector3
function Box2dBody:SetLinearVelocity(velocity) end

--- Get the linear velocity of the center of mass.
---@return vector3
function Box2dBody:GetLinearVelocity() end

--- Set the angular velocity.
---@param omega number the new angular velocity in radians/second.
function Box2dBody:SetAngularVelocity(omega) end

--- Get the angular velocity.
---@return number the angular velocity in radians/second.
function Box2dBody:GetAngularVelocity() end

--- Apply a force at a world point. If the force is not
--- applied at the center of mass, it will generate a torque and
--- affect the angular velocity. This wakes up the body.
---@param force vector3 force the world force vector, usually in Newtons (N).
---@param point vector3 point the world position of the point of application.
---@param wake boolean wake also wake up the body
function Box2dBody:ApplyForce(force, point, wake) end

--- Apply a force to the center of mass. This wakes up the body.
---@param force vector3 force the world force vector, usually in Newtons (N).
---@param wake boolean wake also wake up the body
function Box2dBody:ApplyForceToCenter(force, wake) end

--- Apply a torque. This affects the angular velocity
--- without affecting the linear velocity of the center of mass.
---@param torque number torque about the z-axis (out of the screen), usually in N-m.
---@param wake boolean wake also wake up the body
function Box2dBody:ApplyTorque(torque, wake) end

--- Apply an impulse at a point. This immediately modifies the velocity.
--- It also modifies the angular velocity if the point of application
--- is not at the center of mass. This wakes up the body.
---@param impulse vector3 impulse the world impulse vector, usually in N-seconds or kg-m/s.
---@param point vector3 point the world position of the point of application.
---@param wake boolean wake also wake up the body
function Box2dBody:ApplyLinearImpulse(impulse, point, wake) end

--- Apply an impulse to the center of mass. This immediately modifies the velocity.
---@param impulse vector3 impulse the world impulse vector, usually in N-seconds or kg-m/s.
---@param wake boolean wake also wake up the body
function Box2dBody:ApplyLinearImpulseToCenter(impulse, wake) end

--- Apply an angular impulse.
---@param impulse vector3 impulse the angular impulse in units of kg*m*m/s
---@param wake boolean wake also wake up the body
function Box2dBody:ApplyAngularImpulse(impulse, wake) end

--- Get the total mass of the body.
---@return number the mass, usually in kilograms (kg).
function Box2dBody:GetMass() end

--- Get the rotational inertia of the body about the local origin.
---@return number the rotational inertia, usually in kg-m^2.
function Box2dBody:GetInertia() end

--- This resets the mass properties to the sum of the mass properties of the fixtures.
--- This normally does not need to be called unless you called SetMassData to override
--- the mass and you later want to reset the mass.
function Box2dBody:ResetMassData() end

--- Get the mass data of the body.
---@return Box2dMassData a struct containing the mass, inertia and center of the body.
function Box2dBody:GetMassData() end

--- Set the mass properties to override the mass properties of the fixtures.
--- Note that this changes the center of mass position.
--- Note that creating or destroying fixtures can also alter the mass.
--- This function has no effect if the body isn't dynamic.
---@param data Box2dMassData the mass properties.
function Box2dBody:SetMassData(data) end

--- Get the world coordinates of a point given the local coordinates.
---@param localPoint vector3 a point on the body measured relative the the body's origin.
---@return vector3 the same point expressed in world coordinates.
function Box2dBody:GetWorldPoint(localPoint) end

--- Get the world coordinates of a vector given the local coordinates.
---@param localVector vector3 localVector a vector fixed in the body.
---@return vector3 the same vector expressed in world coordinates.
function Box2dBody:GetWorldVector(localVector) end

--- Gets a local point relative to the body's origin given a world point.
---@param worldPoint vector3 worldPoint a point in world coordinates.
---@return vector3 the corresponding local point relative to the body's origin.
function Box2dBody:GetLocalPoint(worldPoint) end

--- Gets a local vector given a world vector.
---@param worldVector vector3 worldVector a vector in world coordinates.
---@return vector3 the corresponding local vector.
function Box2dBody:GetLocalVector(worldVector) end

--- Get the world linear velocity of a world point attached to this body.
---@param worldPoint vector3 worldPoint a point in world coordinates.
---@return vector3 the world velocity of a point.
function Box2dBody:GetLinearVelocityFromWorldPoint(worldPoint) end

--- Get the world velocity of a local point.
---@param localPoint vector3 localPoint a point in local coordinates.
---@return vector3 the world velocity of a point.
function Box2dBody:GetLinearVelocityFromLocalPoint(localPoint) end

--- Set the linear damping of the body.
---@param linearDamping number
function Box2dBody:SetLinearDamping(linearDamping) end

--- Get the linear damping of the body.
---@return number
function Box2dBody:GetLinearDamping() end

--- Set the angular damping of the body.
---@param angularDamping number
function Box2dBody:SetAngularDamping(angularDamping) end

--- Get the angular damping of the body.
---@return number
function Box2dBody:GetAngularDamping() end

--- Set the gravity scale of the body.
---@param scale number
function Box2dBody:SetGravityScale(scale) end

--- Get the gravity scale of the body.
---@return number
function Box2dBody:GetGravityScale() end

--- Set the type of this body. This may alter the mass and velocity.
---@param type number box2d.b2BodyType
function Box2dBody:SetType(type) end

--- Get the type of this body.
---@return number box2d.b2BodyType
function Box2dBody:GetType() end

--- Should this body be treated like a bullet for continuous collision detection?
---@param flag boolean
function Box2dBody:SetBullet(flag) end

--- Is this body treated like a bullet for continuous collision detection?
---@return boolean
function Box2dBody:IsBullet() end

--- You can disable sleeping on this body. If you disable sleeping, the
--- body will be woken.
---@param flag boolean
function Box2dBody:SetSleepingAllowed(flag) end

--- Is this body allowed to sleep
---@return boolean
function Box2dBody:IsSleepingAllowed() end

--- Set the sleep state of the body. A sleeping body has very
--- low CPU cost.
---@param flag boolean flag set to true to wake the body, false to put it to sleep.
function Box2dBody:SetAwake(flag) end

--- Get the sleeping state of this body.
---@return boolean  true if the body is awake.
function Box2dBody:IsAwake() end

--- Allow a body to be disabled. A disabled body is not simulated and cannot
--- be collided with or woken up.
--- If you pass a flag of true, all fixtures will be added to the broad-phase.
--- If you pass a flag of false, all fixtures will be removed from the
--- broad-phase and all contacts will be destroyed.
--- Fixtures and joints are otherwise unaffected. You may continue
--- to create/destroy fixtures and joints on disabled bodies.
--- Fixtures on a disabled body are implicitly disabled and will
--- not participate in collisions, ray-casts, or queries.
--- Joints connected to a disabled body are implicitly disabled.
--- An diabled body is still owned by a b2World object and remains
--- in the body list.
---@param flag boolean
function Box2dBody:SetEnabled(flag) end

--- Get the active state of the body.
---@return boolean
function Box2dBody:IsEnabled() end

--- Set this body to have fixed rotation. This causes the mass
--- to be reset.
---@param flag boolean
function Box2dBody:SetFixedRotation(flag) end

--- Does this body have fixed rotation?
---@return boolean
function Box2dBody:IsFixedRotation() end

--- Get the next body in the world's body list.
---@return Box2dBody
function Box2dBody:GetNext() end

--- Get the first fixture in list of all fixtures attached to this body or nil
---@return Box2dFixture|nil
function Box2dBody:GetFixtureList() end

--- Get the user data table. Use this to store your application specific data.
---@return table|nil
function Box2dBody:GetUserData() end

--- Set the user data. Use this to store your application specific data.
---@param data table|nil
function Box2dBody:SetUserData(data) end

--- Get the parent world of this body.
---@return Box2dWorld
function Box2dBody:GetWorld() end

--- Dump this body to a file
function Box2dBody:Dump() end
```


### Joint
This is a constraint used to hold two or more bodies together. Box2D supports several joint types: revolute, prismatic, distance, and more. Some joints may have limits and motors.

Box2dJointDef is based for other joint def.
Joint have needed and optional fields.

If you need to call Initialize method of joint for example b2RevoluteJointDef::Initialize(
b2Body * bodyA, b2Body * bodyB, const b2Vec2 & anchor) use box2d.InitializeRevoluteJointDef(bodyA, bodyB, anchor)
```lua
---@class Box2dJointDef
local Box2dJointDef = {
    --region JointNeeded
    --- The joint type
    type = box2d.b2JointType.e_revoluteJoint,

    ---@type Box2dBody
    bodyA = nil,

    ---@type Box2dBody
    bodyB = nil,
    --endregion

    --region JointOptional
    -- Use this to attach application specific data to your joints.
    ---@type table|nil
    userData = nil,

    -- Set this flag to true if the attached bodies should collide.
    collideConnected = false,
    --endregion

}
```
The base joint class. Joints are used to constraint two bodies together in
various fashions. Some joints also feature limits and motors.
```lua
--- The base joint class. Joints are used to constraint two bodies together in
--- various fashions. Some joints also feature limits and motors.
---@class Box2dJoint
local Box2dJoint = {}

--- Get the type of the concrete joint.
---@return number box2d.b2JointType
function Box2dJoint:GetType() end

--- Get the first body attached to this joint.
---@return Box2dBody bodyA
function Box2dJoint:GetBodyA() end

--- Get the second body attached to this joint.
---@return Box2dBody bodyB
function Box2dJoint:GetBodyA() end

--- Get the anchor point on bodyA in world coordinates.
---@return vector3
function Box2dJoint:GetAnchorA() end

--- Get the anchor point on bodyB in world coordinates.
---@return vector3
function Box2dJoint:GetAnchorB() end

--- Get the reaction force on bodyB at the joint anchor in Newtons.
---@param inv_dt number
---@return vector3
function Box2dJoint:GetReactionForce(inv_dt) end

--- Get the reaction torque on bodyB in N*m.
---@param inv_dt number
---@return vector3
function Box2dJoint:GetReactionTorque(inv_dt) end

--- Get the next joint the world joint list.
---@return Box2dJoint|nil
function Box2dJoint:GetNext() end

--- Get the user data.
--- Use this to store your application specific data.
---@return table|nil
function Box2dJoint:GetUserData() end

--- Set the user data.
--- Use this to store your application specific data.
---@param userdata table|nil
function Box2dJoint:SetUserData(userdata) end

--- Short-cut function to determine if either body is enabled.
---@return boolean
function Box2dJoint:IsEnabled() end

--- Get collide connected.
--- Note: modifying the collide connect flag won't work correctly because
--- the flag is only checked when fixture AABBs begin to overlap.
---@return boolean
function Box2dJoint:GetCollideConnected() end

--- Dump this joint to the log file.
function Box2dJoint:Dump() end

--- Shift the origin for any points stored in world coordinates.
---@param newOrigin vector3
function Box2dJoint:ShiftOrigin(newOrigin) end
```

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
---@class Box2dRevoluteJointDef:Box2dJointDef
local Box2dRevoluteJointDef = {
    -- Initialize the bodies, anchors, and reference angle using a world
    -- anchor point.
    -- void Initialize(b2Body* bodyA, b2Body* bodyB, const b2Vec2& anchor);
    
    --region JointNeeded
    anchor = vmath.vector3(0), ---for Initialize
    --endregion

    --region JointOptional
    --- The local anchor point relative to bodyA's origin.
    localAnchorA = vmath.vector3(0, 0, 0),

    --- The local anchor point relative to bodyB's origin.
    localAnchorB = vmath.vector3(0, 0, 0),

    --- The bodyB angle minus bodyA angle in the reference state (radians).
    referenceAngle = 0,

    --- A flag to enable joint limits.
    enableLimit = false,

    --- The lower angle for the joint limit (radians).
    lowerAngle = 0,

    --- The upper angle for the joint limit (radians).
    upperAngle = 0,

    --- A flag to enable the joint motor.
    enableMotor = false,

    --- The desired motor speed. Usually in radians per second.
    motorSpeed = 0,

    --- The maximum motor torque used to achieve the desired motor speed.
    --- Usually in N-m.
    maxMotorTorque = 0,
    --endregion
}
```
A revolute joint constrains two bodies to share a common point while they
are free to rotate about the point. The relative rotation about the shared
point is the joint angle. You can limit the relative rotation with
a joint limit that specifies a lower and upper angle. You can use a motor
to drive the relative rotation about the shared point. A maximum motor torque is provided so that infinite forces are not generated.
```lua
---@class Box2dRevoluteJoint:Box2dJoint
local Box2dRevoluteJoint = {}

--- The local anchor point relative to bodyA's origin.
---@return vector3
function Box2dRevoluteJoint:GetLocalAnchorA() end

--- The local anchor point relative to bodyB's origin.
---@return vector3
function Box2dRevoluteJoint:GetLocalAnchorB() end

--- Get the reference angle.
---@return float
function Box2dRevoluteJoint:GetReferenceAngle() end

--- Get the current joint angle in radians.
---@return float
function Box2dRevoluteJoint:GetJointAngle()end

--- Get the current joint angle speed in radians per second.
---@return float
function Box2dRevoluteJoint:GetJointSpeed() end

--- Is the joint limit enabled?
---@return boolean
function Box2dRevoluteJoint:IsLimitEnabled() end

--- Enable/disable the joint limit.
---@param flag boolean
function Box2dRevoluteJoint:EnableLimit(flag) end

--- Get the lower joint limit in radians.
---@return float
function Box2dRevoluteJoint:GetLowerLimit() end

--- Get the upper joint limit in radians.
---@return float
function Box2dRevoluteJoint:GetUpperLimit() end

--- Set the joint limits in radians.
---@param lower number
---@param upper number
function Box2dRevoluteJoint:SetLimits(lower, upper) end

--- Is the joint motor enabled?
---@return boolean
function Box2dRevoluteJoint:IsMotorEnabled() end

--- Enable/disable the joint motor.
---@param flag boolean
function Box2dRevoluteJoint:EnableMotor(flag) end

--- Set the motor speed in radians per second.
---@param speed number
function Box2dRevoluteJoint:SetMotorSpeed(speed) end

--- Get the motor speed in radians per second.
---@return float
function Box2dRevoluteJoint:GetMotorSpeed() end

--- Set the maximum motor torque, usually in N-m.
---@param torque number
function Box2dRevoluteJoint:SetMaxMotorTorque(torque) end

---@return float
function Box2dRevoluteJoint:GetMaxMotorTorque() end

--- Get the current motor torque given the inverse time step.
--- Unit is N*m.
---@param inv_dt number
---@return float
function Box2dRevoluteJoint:GetMotorTorque(inv_dt) end
```

### PrismaticJoint
Prismatic joint definition. This requires defining a line of
motion using an axis and an anchor point. The definition uses local
anchor points and a local axis so that the initial configuration
can violate the constraint slightly. The joint translation is zero
when the local anchor points coincide in world space. Using local
anchors and a local axis helps when saving and loading a game.
```lua
---@class Box2dPrismaticJointDef:Box2dJointDef
local Box2dPrismaticJointDef = {
    --- Initialize the bodies, anchors, axis, and reference angle using the world
    --- anchor and unit world axis.
    --- void Initialize(b2Body* bodyA, b2Body* bodyB, const b2Vec2& anchor, const b2Vec2& axis);
    --region JointNeeded
    anchor = vmath.vector3(0), ---for Initialize
    axis = vmath.vector3(0), ---for Initialize
    --endregion

    --region JointOptional
    --- The local anchor point relative to bodyA's origin.
    localAnchorA = vmath.vector3(0, 0, 0),
    
    --- The local anchor point relative to bodyB's origin.
    localAnchorB = vmath.vector3(0, 0, 0),
    
    --- The constrained angle between the bodies: bodyB_angle - bodyA_angle.
    referenceAngle = 0,
    
    --- Enable/disable the joint limit.
    enableLimit = false,
    
    --- Enable/disable the joint motor.
    enableMotor = false,
    
    --- The desired motor speed in radians per second.
    motorSpeed = 0,
    
    --- The local translation unit axis in bodyA.
    localAxisA = vmath.vector3(1,0,0),
    
    --- The lower translation limit, usually in meters.
    lowerTranslation = 0,
    
    --- The upper translation limit, usually in meters.
    upperTranslation = 0,
    
    --- The maximum motor torque, usually in N-m.
    maxMotorForce = 0,
    --endregion
}
```

A prismatic joint. This joint provides one degree of freedom: translation
along an axis fixed in bodyA. Relative rotation is prevented. You can
use a joint limit to restrict the range of motion and a joint motor to
drive the motion or to model joint friction.
```lua
---@class Box2dPrismaticJoint:Box2dJoint
local Box2dPrismaticJoint = {}
--- The local anchor point relative to bodyA's origin.
---@return vector3
function Box2dPrismaticJoint:GetLocalAnchorA() end

--- The local anchor point relative to bodyB's origin.
---@return vector3
function Box2dPrismaticJoint:GetLocalAnchorB() end

--- The local joint axis relative to bodyA.
---@return vector3
function Box2dPrismaticJoint:GetLocalAxisA() end

--- Get the reference angle.
---@return number
function Box2dPrismaticJoint:GetReferenceAngle() end

--- Get the current joint translation, usually in meters.
---@return number
function Box2dPrismaticJoint:GetJointTranslation() end

--- Get the current joint translation speed, usually in meters per second.
---@return number
function Box2dPrismaticJoint:GetJointSpeed() end

--- Is the joint limit enabled?
---@return boolean
function Box2dPrismaticJoint:IsLimitEnabled() end

--- Enable/disable the joint limit.
---@param flag boolean
function Box2dPrismaticJoint:EnableLimit(flag) end

--- Get the lower joint limit, usually in meters.
---@return number
function Box2dPrismaticJoint:GetLowerLimit() end

--- Get the upper joint limit, usually in meters.
---@return number
function Box2dPrismaticJoint:GetUpperLimit() end

--- Set the joint limits, usually in meters.
---@param lower number
---@param upper number
function Box2dPrismaticJoint:SetLimits(lower, upper) end

--- Is the joint motor enabled?
---@return boolean
function Box2dPrismaticJoint:IsMotorEnabled() end

--- Enable/disable the joint motor.
---@param flag boolean
function Box2dPrismaticJoint:EnableMotor(flag) end

--- Set the motor speed, usually in meters per second.
---@param speed number
function Box2dPrismaticJoint:SetMotorSpeed(speed) end

--- Get the motor speed, usually in meters per second.
---@return number
function Box2dPrismaticJoint:GetMotorSpeed() end

--- Set the maximum motor force, usually in N.
---@param force number
function Box2dPrismaticJoint:SetMaxMotorForce(force) end
---@return number
function Box2dPrismaticJoint:GetMaxMotorForce() end

--- Get the current motor force given the inverse time step, usually in N.
---@param inv_dt number
---@return number
function Box2dPrismaticJoint:GetMotorForce(inv_dt) end
```

### DistanceJoint
Distance joint definition. This requires defining an anchor point on both
bodies and the non-zero distance of the distance joint. The definition uses
local anchor points so that the initial configuration can violate the
constraint slightly. This helps when saving and loading a game.
```lua
---@class Box2dDistanceJointDef:Box2dJointDef
local Box2dDistanceJointDef = {
    --- Initialize the bodies, anchors, and rest length using world space anchors.
    --- The minimum and maximum lengths are set to the rest length.
    ---void Initialize(b2Body* bodyA, b2Body* bodyB,
    ---const b2Vec2& anchorA, const b2Vec2& anchorB);
    
    --region JointNeeded
    anchorA = vmath.vector3(0),
    anchorB = vmath.vector3(0),
    --endregion

    --region JointOptional
    --- The local anchor point relative to bodyA's origin.
    localAnchorA = vmath.vector3(0, 0, 0),

    --- The local anchor point relative to bodyB's origin.
    localAnchorB = vmath.vector3(0, 0, 0),

    --- The rest length of this joint. Clamped to a stable minimum value.
    length = 1,
    
    --- Minimum length. Clamped to a stable minimum value.
    minLength = 0,
    
    --- Maximum length. Must be greater than or equal to the minimum length.
    maxLength = math.huge,
    
    --- The linear stiffness in N/m.
    stiffness = 0.0,
    
    --- The linear damping in N*s/m.
    damping = 0.0,
    --endregion
}
```

A distance joint constrains two points on two bodies to remain at a fixed
distance from each other. You can view this as a massless, rigid rod.
```lua
---@class Box2dDistanceJoint:Box2dJoint
local Box2dDistanceJoint = {}
--- The local anchor point relative to bodyA's origin.
---@return vector3
function Box2dDistanceJoint:GetLocalAnchorA() end

--- The local anchor point relative to bodyB's origin.
---@return vector3
function Box2dDistanceJoint:GetLocalAnchorB() end

--- Get the rest length
---@return number
function Box2dDistanceJoint:GetLength() end

--- Set the rest length
---@param length number
---@return number clamped rest length
function Box2dDistanceJoint:SetLength(length) end

--- Get the minimum length
---@return number
function Box2dDistanceJoint:GetMinLength() end

--- Set the minimum length
---@param minLength number
---@return number the clamped minimum length
function Box2dDistanceJoint:SetMinLength(minLength) end

--- Get the maximum length
---@return number
function Box2dDistanceJoint:GetMaxLength() end

--- Set the maximum length
---@param maxLength number
---@return number the clamped maximum length
function Box2dDistanceJoint:SetMaxLength(maxLength) end

--- Get the current length
---@return number
function Box2dDistanceJoint:GetCurrentLength() end

--- Set/get the linear stiffness in N/m
---@param stiffness number
function Box2dDistanceJoint:SetStiffness(stiffness) end
---@return number
function Box2dDistanceJoint:GetStiffness() end

--- Set/get linear damping in N*s/m
---@param damping number
function Box2dDistanceJoint:SetDamping(damping) end
---@return number
function Box2dDistanceJoint:GetDamping() end
```

### PulleyJoint
Pulley joint definition. This requires two ground anchors,
two dynamic body anchor points, and a pulley ratio.
```lua
---@class Box2dPulleyJointDef:Box2dJointDef
local Box2dPulleyJointDef = {
    --- Initialize the bodies, anchors, lengths, max lengths, and ratio using the world anchors.
    ---void Initialize(b2Body* bodyA, b2Body* bodyB,
    ---     const b2Vec2& groundAnchorA, const b2Vec2& groundAnchorB,
    ---     const b2Vec2& anchorA, const b2Vec2& anchorB,
    ---     float ratio);

    --region JointNeeded
    anchorA = vmath.vector3(0), --for Initialize

    anchorB = vmath.vector3(0), --for Initialize
    
    --- The first ground anchor in world coordinates. This point never moves.
    groundAnchorA = vmath.vector3(0), --for Initialize

    --- The second ground anchor in world coordinates. This point never moves.
    groundAnchorB = vmath.vector3(0), --for Initialize
    
    --- The pulley ratio, used to simulate a block-and-tackle.
    ratio = 0, ---for Initialize
    --endregion

    --region JointOptional
    --- The local anchor point relative to bodyA's origin.
    localAnchorA = vmath.vector3(0, 0, 0),
    
    --- The local anchor point relative to bodyB\'s origin.
    localAnchorB = vmath.vector3(0, 0, 0),
    
    --- The a reference length for the segment attached to bodyA.
    lengthA = 0,
    
    --- The a reference length for the segment attached to bodyB.
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

```lua
---@class Box2dPulleyJoint:Box2dJoint
local Box2dPulleyJoint = {}

--- Get the first ground anchor.
---@return vector3
function Box2dPulleyJoint:GetGroundAnchorA() end

--- Get the second ground anchor.
---@return vector3
function Box2dPulleyJoint:GetGroundAnchorB() end

--- Get the current length of the segment attached to bodyA.
---@return number
function Box2dPulleyJoint:GetLengthA() end

--- Get the current length of the segment attached to bodyB.
---@return number
function Box2dPulleyJoint:GetLengthB() end

--- Get the pulley ratio.
---@return number
function Box2dPulleyJoint:GetRatio() end

--- Get the current length of the segment attached to bodyA.
---@return number
function Box2dPulleyJoint:GetCurrentLengthA() end

--- Get the current length of the segment attached to bodyB.
---@return number
function Box2dPulleyJoint:GetCurrentLengthB() end
```

### MouseJoint
Mouse joint definition. This requires a world target point,
tuning parameters, and the time step.
```lua
---@class Box2dMouseJointDef:Box2dJointDef
local Box2dMouseJointDef = {
    --region JointNeeded
    --endregion

    --region JointOptional
    --- The linear stiffness in N/m
    stiffness = 0,
    
    --- The linear damping in N*s/m
    damping = 0,
    
    --- The initial world target point. This is assumed
    --- to coincide with the body anchor initially.
    target = vmath.vector3(0),
    
    --- The maximum constraint force that can be exerted
    --- to move the candidate body. Usually you will express
    --- as some multiple of the weight (multiplier * mass * gravity).
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
```lua
---@class Box2dMouseJoint:Box2dJoint
local Box2dMouseJoint = {}

--- Use this to update the target point.
---@param target vector3
function Box2dMouseJoint:SetTarget(target) end

---@return vector3
function Box2dMouseJoint:GetTarget() end

--- Set/get the maximum force in Newtons.
---@param force number
function Box2dMouseJoint:SetMaxForce(force) end

---@return number
function Box2dMouseJoint:GetMaxForce() end

--- Set/get the linear stiffness in N/m
---@param stiffness number
function Box2dMouseJoint:SetStiffness(stiffness) end

---@return number
function Box2dMouseJoint:GetStiffness() end

--- Set/get linear damping in N*s/m
---@param damping number
function Box2dMouseJoint:SetDamping(damping) end

---@return number
function Box2dMouseJoint:GetDamping() end
```

### GearJoint
Gear joint definition. This definition requires two existing
revolute or prismatic joints (any combination will work).
@warning bodyB on the input joints must both be dynamic
```lua
---@class Box2dGearJointDef:Box2dJointDef
local Box2dGearJointDef = {
    --region JointNeeded
    --- The first revolute/prismatic joint attached to the gear joint.
    ---@type Box2dJoint
    joint1 = nil,

    --- The second revolute/prismatic joint attached to the gear joint.
    ---@type Box2dJoint
    joint2 = nil,
    --endregion

    --region JointOptional
    --- The gear ratio.
    --- @see Box2dGearJoint for explanation.
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
warning You have to manually destroy the gear joint if joint1 or joint2
is destroyed.
```lua
---@class Box2dGearJoint:Box2dJoint
local Box2dGearJoint = {}
--- Get the first joint.
---@return Box2dJoint
function Box2dGearJoint:GetJoint1() end

--- Get the second joint.
---@return Box2dJoint
function Box2dGearJoint:GetJoint2() end

--- Set/Get the gear ratio.
---@param ratio number
function Box2dGearJoint:SetRatio(ratio) end
---@return number
function Box2dGearJoint:GetRatio() end
```

### WheelJoint
Wheel joint definition. This requires defining a line of
motion using an axis and an anchor point. The definition uses local
anchor points and a local axis so that the initial configuration
can violate the constraint slightly. The joint translation is zero
when the local anchor points coincide in world space. Using local
anchors and a local axis helps when saving and loading a game.
```lua
---@class Box2dWheelJointDef:Box2dJointDef
local Box2dWheelJointDef = {
    --- Initialize the bodies, anchors, axis, and reference angle using the world
    --- anchor and world axis.
    --- void Initialize(b2Body* bodyA, b2Body* bodyB, const b2Vec2& anchor, const b2Vec2& axis);
    --region JointNeeded
    anchor = vmath.vector3(0), --for Initialize
    axis = vmath.vector3(0), --for Initialize
    --endregion

    --region JointOptional
    --- The local anchor point relative to bodyA's origin.
    localAnchorA = vmath.vector3(0, 0, 0),
    
    --- The local anchor point relative to bodyB\'s origin.
    localAnchorB = vmath.vector3(0, 0, 0),

    --- Enable/disable the joint limit.
    enableLimit = false,

--- Enable/disable the joint motor.
    enableMotor = false,

    --- The desired motor speed in radians per second.
    motorSpeed = 0,

    --- The maximum motor torque, usually in N-m.
    maxMotorTorque = 0,

    --- The local translation axis in bodyA.
    localAxisA = vmath.vector3(0),

--- The lower translation limit, usually in meters.
    lowerTranslation = 0,

--- The upper translation limit, usually in meters.
    upperTranslation = 0,

--- Suspension stiffness. Typically in units N/m.
    stiffness = 0,

--- Suspension damping. Typically in units of N*s/m.
    damping = 0,
    --endregion
}
```
A wheel joint. This joint provides two degrees of freedom: translation
along an axis fixed in bodyA and rotation in the plane. In other words, it is a point to
line constraint with a rotational motor and a linear spring/damper. The spring/damper is
initialized upon creation. This joint is designed for vehicle suspensions.
```lua
---@class Box2dWheelJoint:Box2dJoint
local Box2dWheelJoint = {}

--- The local anchor point relative to bodyA's origin.
---@return vector3
function Box2dWheelJoint:GetLocalAnchorA() end

--- The local anchor point relative to bodyB's origin.
---@return vector3
function Box2dWheelJoint:GetLocalAnchorB() end

--- The local joint axis relative to bodyA.
---@return vector3
function Box2dWheelJoint:GetLocalAxisA() end

--- Get the current joint translation, usually in meters.
---@return number
function Box2dWheelJoint:GetJointTranslation() end

--- Get the current joint linear speed, usually in meters per second.
---@return number
function Box2dWheelJoint:GetJointLinearSpeed() end

--- Get the current joint angle in radians.
---@return number
function Box2dWheelJoint:GetJointAngle() end

--- Get the current joint angular speed in radians per second.
---@return number
function Box2dWheelJoint:GetJointAngularSpeed() end

--- Is the joint limit enabled?
---@return boolean
function Box2dWheelJoint:IsLimitEnabled() end

--- Enable/disable the joint translation limit.
---@param flag boolean
function Box2dWheelJoint:EnableLimit(flag) end

--- Get the lower joint translation limit, usually in meters.
---@return number
function Box2dWheelJoint:GetLowerLimit() end

--- Get the upper joint translation limit, usually in meters.
---@return number
function Box2dWheelJoint:GetUpperLimit() end

--- Set the joint translation limits, usually in meters.
---@param lower number
---@param upper number
function Box2dWheelJoint:SetLimits(lower, upper) end

--- Is the joint motor enabled?
---@return boolean
function Box2dWheelJoint:IsMotorEnabled() end

--- Enable/disable the joint motor.
---@param flag boolean
function Box2dWheelJoint:EnableMotor(flag) end

--- Set the motor speed, usually in radians per second.
---@param speed number
function Box2dWheelJoint:SetMotorSpeed(speed) end

--- Get the motor speed, usually in radians per second.
---@return number
function Box2dWheelJoint:GetMotorSpeed() end

--- Set/Get the maximum motor force, usually in N-m.
---@param torque number
function Box2dWheelJoint:SetMaxMotorTorque(torque) end
---@return number
function Box2dWheelJoint:GetMaxMotorTorque() end

--- Get the current motor torque given the inverse time step, usually in N-m.
---@param inv_dt number
---@return number
function Box2dWheelJoint:GetMotorTorque(inv_dt) end

--- Access spring stiffness
---@param stiffness number
function Box2dWheelJoint:SetStiffness(stiffness) end
---@return number
function Box2dWheelJoint:GetStiffness() end

--- Access damping
---@param damping number
function Box2dWheelJoint:SetDamping(damping) end
---@return number
function Box2dWheelJoint:GetDamping() end
```

### WeldJoint
Weld joint definition. You need to specify local anchor points
where they are attached and the relative body angle. The position
of the anchor points is important for computing the reaction torque.
```lua
---@class Box2WeldJointDef:Box2dJointDef
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
    --- The local anchor point relative to bodyA's origin.
    localAnchorA = vmath.vector3(0, 0, 0),
    
    --- The local anchor point relative to bodyB\'s origin.
    localAnchorB = vmath.vector3(0, 0, 0),
    
    --- The bodyB angle minus bodyA angle in the reference state (radians).
    referenceAngle = 0,
    
    --- The rotational stiffness in N*m
    --- Disable softness with a value of 0
    stiffness = 0,
    
    --- The rotational damping in N*m*s
    damping = 0,
    --endregion
}
```

A weld joint essentially glues two bodies together. A weld joint may
distort somewhat because the island constraint solver is approximate.
```lua
---@class Box2dWeldJoint:Box2dJoint
local Box2dWeldJoint = {}

--- The local anchor point relative to bodyA's origin.
---@return vector3
function Box2dWeldJoint:GetLocalAnchorA() end

--- The local anchor point relative to bodyB's origin.
---@return vector3
function Box2dWeldJoint:GetLocalAnchorB() end

--- Get the reference angle.
---@return number
function Box2dWeldJoint:GetReferenceAngle() end

--- Set/get stiffness in N*m
---@param hz number
function Box2dWeldJoint:SetStiffness(hz) end
---@return number
function Box2dWeldJoint:GetStiffness() end

--- Set/get damping in N*m*s
---@param damping number
function Box2dWeldJoint:SetDamping(damping) end
---@return number
function Box2dWeldJoint:GetDamping() end
```

### FrictionJoint
Friction joint definition.
```lua
---@class Box2FrictionJointDef:Box2dJointDef
local Box2FrictionJointDef = {
    -- Initialize the bodies, anchors, axis, and reference angle using the world
    -- anchor and world axis.
    --void Initialize(b2Body* bodyA, b2Body* bodyB, const b2Vec2& anchor);
    --region JointNeeded
    anchor = vmath.vector3(0), --for Initialize
    --endregion

    --region JointOptional
    --- The local anchor point relative to bodyA's origin.
    localAnchorA = vmath.vector3(0, 0, 0),
    
    --- The local anchor point relative to bodyB's origin.
    localAnchorB = vmath.vector3(0, 0, 0), 
    
    --- The maximum friction force in N.
    maxForce = 0,

    --- The maximum friction torque in N-m.
    maxTorque = 0,
    --endregion
}
```
Friction joint. This is used for top-down friction.
It provides 2D translational friction and angular friction.
```lua
---@class Box2FrictionJoint:Box2dJoint
local Box2FrictionJoint = {}

--- The local anchor point relative to bodyA's origin.
---@return vector3
function Box2FrictionJoint:GetLocalAnchorA() end

--- The local anchor point relative to bodyB's origin.
---@return vector3
function Box2FrictionJoint:GetLocalAnchorB() end

--- Set the maximum friction force in N.
---@param force number
function Box2FrictionJoint:SetMaxForce(force) end

--- Get the maximum friction force in N.
---@return number
function Box2FrictionJoint:GetMaxForce() end

--- Set the maximum friction torque in N*m.
---@param torque number
function Box2FrictionJoint:SetMaxTorque(torque) end

--- Get the maximum friction torque in N*m.
---@return number
function Box2FrictionJoint:GetMaxTorque() end
```

### MotorJoint
Motor joint definition.
```lua
---@class Box2MotorJointDef:Box2dJointDef
local Box2MotorJointDef = {
    -- Initialize the bodies and offsets using the current transforms.
    --void Initialize(b2Body* bodyA, b2Body* bodyB);
    --region JointNeeded
    --endregion

    --region JointOptional
    --- The maximum motor force in N.
    maxForce = vmath.vector3(0, 0, 0),
    
    --- The maximum motor torque in N-m.
    maxTorque = vmath.vector3(0, 0, 0),
    
    --- Position of bodyB minus the position of bodyA, in bodyA's frame, in meters.
    linearOffset = 0,
    
    --- The bodyB angle minus bodyA angle in radians.
    angularOffset = 0,
    
    --- Position correction factor in the range [0,1].
    correctionFactor = 0,
    --endregion
}
```

A motor joint is used to control the relative motion
between two bodies. A typical usage is to control the movement
of a dynamic body with respect to the ground.
```lua
---@class Box2dMotorJoint:Box2dJoint
local Box2dMotorJoint = {}
--- Set/get the target linear offset, in frame A, in meters.
---@param linearOffset vector3
function Box2dMotorJoint:SetLinearOffset(linearOffset) end
---@return vector3
function Box2dMotorJoint:GetLinearOffset() end

--- Set/get the target angular offset, in radians.
---@param angularOffset number
function Box2dMotorJoint:SetAngularOffset(angularOffset) end
---@return number
function Box2dMotorJoint:GetAngularOffset() end

--- Set the maximum friction force in N.
---@param force number
function Box2dMotorJoint:SetMaxForce(force) end

--- Get the maximum friction force in N.
---@return number
function Box2dMotorJoint:GetMaxForce() end

--- Set the maximum friction torque in N*m.
---@param torque number
function Box2dMotorJoint:SetMaxTorque(torque) end

--- Get the maximum friction torque in N*m.
---@return number
function Box2dMotorJoint:GetMaxTorque() end

--- Set the position correction factor in the range [0,1].
---@param factor number
function Box2dMotorJoint:SetCorrectionFactor(factor) end

--- Get the position correction factor in the range [0,1].
---@return number
function Box2dMotorJoint:GetCorrectionFactor() end
```

###Box2dManifold
```lua
--- A manifold for two touching convex shapes.
--- Box2D supports multiple types of contact:
--- - clip point versus plane with radius
--- - point versus point with radius (circles)
--- The local point usage depends on the manifold type:
--- -e_circles: the local center of circleA
--- -e_faceA: the center of faceA
--- -e_faceB: the center of faceB
--- Similarly the local normal usage:
--- -e_circles: not used
--- -e_faceA: the normal on polygonA
--- -e_faceB: the normal on polygonB
--- We store contacts in this way so that position correction can
--- account for movement, which is critical for continuous physics.
--- All contact scenarios must be expressed in one of these types.
--- This structure is stored across time steps, so we keep it small.
---@class Box2dManifold
---@field type number box2d.b2Manifold_Type
---@field localPoint vector3 usage depends on manifold type
---@field localNormal vector3 not use for Type::e_points
---@field pointCount number the number of manifold points
---@field points Box2dManifoldPoint[] the points of contact

--- A manifold point is a contact point belonging to a contact
--- manifold. It holds details related to the geometry and dynamics
--- of the contact points.
--- The local point usage depends on the manifold type:
--- -e_circles: the local center of circleB
--- -e_faceA: the local center of cirlceB or the clip point of polygonB
--- -e_faceB: the clip point of polygonA
--- This structure is stored across time steps, so we keep it small.
--- Note: the impulses are used for internal caching and may not
--- provide reliable contact forces, especially for high speed collisions.
---@class Box2dManifoldPoint
---@field localPoint vector3 usage depends on manifold type
---@field normalImpulse number the non-penetration impulse
---@field tangentImpulse number	the friction impulse
---@field id Box2dContactID uniquely identifies a contact point between two shapes

--- Contact ids to facilitate warm starting.
---@class Box2dContactID
---@field cf Box2dContactFeature
---@field key number  Used to quickly compare contact ids.

--- The features that intersect to form the contact point
--- This must be 4 bytes or less.
--enum Type
--	{
--		e_vertex = 0,
--		e_face = 1
--	};
---@class Box2dContactFeature
---@field indexA number Feature index on shapeA
---@field indexB number	Feature index on shapeB
---@field typeA number	The feature type on shapeA
---@field typeB number	The feature type on shapeB
```

### Box2dWorldManifold
```lua
--- This is used to compute the current state of a contact manifold.
---@class Box2dWorldManifold
---@field normal vector3 world vector pointing from A to B
---@field points vector3[] world contact point (point of intersection)
---@field separations number[] a negative value indicates overlap, in meters
```
### Box2dProfile
return by world:GetProfile() method
```lua
---@class Box2dProfile
---@field step number
---@field collide number
---@field solve number
---@field solveInit number
---@field solveVelocity number
---@field solvePosition number
---@field broadphase number
---@field solveTOI number
```

### Box2dMassData
```lua
---@class Box2dMassData
---@field mass number
---@field center vector3
---@field I number
```
