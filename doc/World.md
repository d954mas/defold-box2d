# World
A physics world is a collection of bodies, fixtures, and constraints that interact together. Box2D supports the creation of multiple worlds, but this is usually not necessary or desirable.
Destroy the world with world:Destroy() when you do not need it any more.

## Constructor

### box2d.NewWorld(gravity)

_ARGUMENTS_
* __gravity__ <kbd>vector3|nil</kbd> - The world gravity vector.

_RETURNS_
* [`Box2dWorld`](World.md)

## Methods

* Box2dWorld:[SetContactListener](#box2dworldsetcontactlistenerlistener) (listener)
* Box2dWorld:[SetDebugDraw](#box2dworldsetdebugdrawdraw) (draw)
* Box2dWorld:[CreateBody](#box2dworldcreatebodybodydef) (bodyDef)
* Box2dWorld:[DestroyBody](#box2dworlddestroybodybody) (body)
* Box2dWorld:[CreateJoint](#box2dworldcreatejointdef) (def)
* Box2dWorld:[DestroyJoint](#box2dworlddestroyjointjoint) (joint)
* Box2dWorld:[Step](#steptimestepvelocityiterationspositioniterations)) (timeStep, velocityIterations, positionIterations)
* Box2dWorld:[ClearForces](#box2dworldclearforces) ()
* Box2dWorld:[DebugDraw](#box2dworlddebugdraw) ()
* Box2dWorld:[GetBodyList](#box2dworldgetbodylist) ()
* Box2dWorld:[RayCast](#box2dworldraycastcallback-point1-point2) (callback, point1, point2)
* Box2dWorld:[QueryAABB](#box2dworldqueryaabbcallback-aabb) (callback, aabb)
* Box2dWorld:[GetJointList](#box2dworldgetjointlist) ()
* Box2dWorld:[SetAllowSleeping](#box2dworldsetallowsleepingflag) (flag)
* Box2dWorld:[GetAllowSleeping](#box2dworldgetallowsleeping) ()
* Box2dWorld:[SetWarmStarting](#box2dworldsetwarmstartingflag) (flag)
* Box2dWorld:[GetWarmStarting](#box2dworldgetwarmstarting) ()
* Box2dWorld:[SetContinuousPhysics](#setcontinuousphysicsflag) (flag)
* Box2dWorld:[GetContinuousPhysics](#box2dworldgetcontinuousphysics) ()
* Box2dWorld:[SetSubStepping](#box2dworldsetsubsteppingflag) (flag)
* Box2dWorld:[GetSubStepping](#box2dworldgetsubstepping) ()
* Box2dWorld:[GetProxyCount](#box2dworldgetproxycount) ()
* Box2dWorld:[GetBodyCount](#box2dworldgetbodycount) ()
* Box2dWorld:[GetJointCount](#box2dworldgetjointcount) ()
* Box2dWorld:[GetContactCount](#box2dworldgetcontactcount) ()
* Box2dWorld:[GetTreeHeight](#box2dworldgettreeheight) ()
* Box2dWorld:[GetTreeBalance](#box2dworldgettreebalance) ()
* Box2dWorld:[GetTreeQuality](#box2dworldgettreequality) ()
* Box2dWorld:[SetGravity](#box2dworldsetgravity) ()
* Box2dWorld:[GetGravity](#box2dworldgetgravity) ()
* Box2dWorld:[IsLocked](#box2dworldislocked) ()
* Box2dWorld:[SetAutoClearForces](#box2dworldsetautoclearforcesflag) (flag)
* Box2dWorld:[GetAutoClearForces](#box2dworldgetautoclearforces) ()
* Box2dWorld:[ShiftOrigin](#box2dworldshiftoriginneworigin) (newOrigin)
* Box2dWorld:[GetProfile](#box2dworldgetprofile) ()
* Box2dWorld:[Dump](#box2dworlddump) ()
* Box2dWorld:[Destroy](#box2dworlddestroy) ()

#### Box2dWorld:SetContactListener(listener)
Register a contact event listener.

_ARGUMENTS_
* __listener__ <kbd>table|nil</kbd>

```lua
listener = {
   BeginContact = function (contact) end,
   EndContact = function(contact) end,
   PreSolve = function(contact, old_manifold) end,
   PostSolve = function(contact,impulse) end
}
```

#### Box2dWorld:SetDebugDraw(draw)
Register a routine for debug drawing. The debug draw functions are called
inside with b2World:DebugDraw method. The debug draw object is owned
by you and must remain in scope.

_ARGUMENTS_
* __draw__ [`Box2dDebugDraw`](DebugDraw.md)|<kbd>nil</kbd> -

#### Box2dWorld:CreateBody(bodyDef)
Create a rigid body given a definition.
_Warning:_ This function is locked during callbacks.

_ARGUMENTS_
* __bodyDef__ [`Box2dBodyDef`](BodyDef.md) -

_RETURNS_
* [`Box2dBody`](Body.md)

#### Box2dWorld:DestroyBody(body)
Destroy a rigid body given a definition.
_Warning:_ This automatically deletes all associated shapes and joints.
_Warning:_ This function is locked during callbacks.

_ARGUMENTS_
* __body__ [`Box2dBody`](Body.md) -

#### Box2dWorld:CreateJoint(def)
Create a joint to constrain bodies together.
This may cause the connected bodies to cease colliding.
_Warning:_ This function is locked during callbacks.

_ARGUMENTS_
* __def__ [`Box2dJointDef`](Joint.md) -

_RETURNS_
* [`Box2dJoint`](Joint.md)

#### Box2dWorld:DestroyJoint(joint)
Destroy a joint. This may cause the connected bodies to begin colliding.
_Warning:_ This function is locked during callbacks.

_ARGUMENTS_
* __joint__ [`Box2dJoint`](Joint.md) -

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
* [`Box2dBody`](Body.md)|<kbd>nil</kbd> - The head of the world body list.

#### Box2dWorld:RayCast(callback, point1, point2)
Ray-cast the world for all fixtures in the path of the ray. Your callback
controls whether you get the closest point, any point, or n-points.
The ray-cast ignores shapes that contain the starting point.

_ARGUMENTS_
* __callback__ <kbd>function</kbd> - function(Box2dFixture fixture, vector3 point, vector3 normal, float fraction)
* __point1__ <kbd>vector3</kbd> - Ray starting point.
* __point2__ <kbd>vector3</kbd> - Ray ending point.

#### Box2dWorld:QueryAABB(callback, aabb)
Query the world for all fixtures that potentially overlap the
provided AABB.

_ARGUMENTS_
* __callback__ <kbd>function</kbd> - function(fixture)
* __aabb__ <kbd>table</kbd> - The query box. { lowerBound = vmath.vector3(0), upperBound = vmath.vector3(0) }

#### Box2dWorld:GetJointList()
Get the world joint list. With the returned joint, use b2Joint:GetNext() to get the next joint in the world list.
A nil joint indicates the end of the list.

_RETURNS_
* [`Box2dJoint`](Joint.md)|<kbd>nil</kbd> - The head of the world joint list.

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
* [`Box2dProfile`](Box2dProfile.md)

#### Box2dWorld:Dump()
Dump the world into the log file.
_Warning:_ this should be called outside of a time step.

#### Box2dWorld:Destroy()
Destroy the world.
