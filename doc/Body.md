# Body
A chunk of matter that is so strong that the distance between any two bits of matter on the chunk is constant. They are hard like a diamond. In the following discussion we use body interchangeably with rigid body.

A rigid body. These are created via world:CreateBody.

## Constructor

#### Box2dWorld:CreateBody(bodyDef)
Create a rigid body given a definition.
_Warning:_ This function is locked during callbacks.

_ARGUMENTS_
* __bodyDef__ <kbd>Box2dBodyDef</kbd> -

_RETURNS_
* <kbd>Box2dBody</kbd>

## Methods

* Box2dBody:[CreateFixture](Box2dBody:CreateFixture(def)) (def)
* Box2dBody:[CreateFixture](Box2dBody:CreateFixture(shape,density)) (shape, density)
* Box2dBody:[DestroyFixture](Box2dBody:DestroyFixture(fixture)) (fixture)
* Box2dBody:[SetTransform](Box2dBody:SetTransform(position,angle)) (position, angle)
* Box2dBody:[GetTransform](Box2dBody:GetTransform()) ()
* Box2dBody:[GetPosition](Box2dBody:GetPosition()) ()
* Box2dBody:[GetAngle](Box2dBody:GetAngle()) ()
* Box2dBody:[GetWorldCenter](Box2dBody:GetWorldCenter()) ()
* Box2dBody:[GetLocalCenter](Box2dBody:GetLocalCenter()) ()
* Box2dBody:[SetLinearVelocity](Box2dBody:SetLinearVelocity(velocity)) (velocity)
* Box2dBody:[GetLinearVelocity](Box2dBody:GetLinearVelocity()) ()
* Box2dBody:[SetAngularVelocity](Box2dBody:SetAngularVelocity(omega)) (omega)
* Box2dBody:[GetAngularVelocity](Box2dBody:GetAngularVelocity()) ()
* Box2dBody:[ApplyForce](Box2dBody:ApplyForce(force,point,wake)) (force, point, wake)
* Box2dBody:[ApplyForceToCenter](Box2dBody:ApplyForceToCenter(force,wake)) (force, wake)
* Box2dBody:[ApplyTorque](Box2dBody:ApplyTorque(torque,wake)) (torque, wake)
* Box2dBody:[ApplyLinearImpulse](Box2dBody:ApplyLinearImpulse(impulse,point,wake)) (impulse, point, wake)
* Box2dBody:[ApplyLinearImpulseToCenter](Box2dBody:ApplyLinearImpulseToCenter(impulse,wake)) (impulse, wake)
* Box2dBody:[ApplyAngularImpulse](Box2dBody:ApplyAngularImpulse(impulse,wake)) (impulse, wake)
* Box2dBody:[GetMass](Box2dBody:GetMass()) ()
* Box2dBody:[GetInertia](Box2dBody:GetInertia()) ()
* Box2dBody:[ResetMassData](Box2dBody:ResetMassData()) ()
* Box2dBody:[GetMassData](Box2dBody:GetMassData()) ()
* Box2dBody:[SetMassData](Box2dBody:SetMassData(data)) (data)
* Box2dBody:[GetWorldPoint](Box2dBody:GetWorldPoint(localPoint)) (localPoint)
* Box2dBody:[GetWorldVector](Box2dBody:GetWorldVector(localVector)) (localVector)
* Box2dBody:[GetLocalPoint](Box2dBody:GetLocalPoint(worldPoint)) (worldPoint)
* Box2dBody:[GetLocalVector](Box2dBody:GetLocalVector(worldVector)) (worldVector)
* Box2dBody:[GetLinearVelocityFromWorldPoint](Box2dBody:GetLinearVelocityFromWorldPoint(worldPoint)) (worldPoint)
* Box2dBody:[GetLinearVelocityFromLocalPoint](Box2dBody:GetLinearVelocityFromLocalPoint(localPoint)) (localPoint)
* Box2dBody:[SetLinearDamping](Box2dBody:SetLinearDamping(linearDamping)) (linearDamping)
* Box2dBody:[GetLinearDamping](Box2dBody:GetLinearDamping()) ()
* Box2dBody:[SetAngularDamping](Box2dBody:SetAngularDamping(angularDamping)) (angularDamping)
* Box2dBody:[GetAngularDamping](Box2dBody:GetAngularDamping()) ()
* Box2dBody:[SetGravityScale](Box2dBody:SetGravityScale(scale)) (scale)
* Box2dBody:[GetGravityScale](Box2dBody:GetGravityScale()) ()
* Box2dBody:[SetType](Box2dBody:SetType(type)) (type)
* Box2dBody:[GetType](Box2dBody:GetType()) ()
* Box2dBody:[SetBullet](Box2dBody:SetBullet(flag)) (flag)
* Box2dBody:[IsBullet](Box2dBody:IsBullet()) ()
* Box2dBody:[SetSleepingAllowed](Box2dBody:SetSleepingAllowed(flag)) (flag)
* Box2dBody:[IsSleepingAllowed](Box2dBody:IsSleepingAllowed()) ()
* Box2dBody:[SetAwake](Box2dBody:SetAwake(flag)) (flag)
* Box2dBody:[IsAwake](Box2dBody:IsAwake()) ()
* Box2dBody:[SetEnabled](Box2dBody:SetEnabled(flag)) (flag)
* Box2dBody:[IsEnabled](Box2dBody:IsEnabled()) ()
* Box2dBody:[SetFixedRotation](Box2dBody:SetFixedRotation(flag)) (flag)
* Box2dBody:[IsFixedRotation](Box2dBody:IsFixedRotation()) ()
* Box2dBody:[GetNext](Box2dBody:GetNext()) ()
* Box2dBody:[GetFixtureList](Box2dBody:GetFixtureList()) ()
* Box2dBody:[GetUserData](Box2dBody:GetUserData()) ()
* Box2dBody:[SetUserData](Box2dBody:SetUserData(data)) (data)
* Box2dBody:[GetWorld](Box2dBody:GetWorld()) ()
* Box2dBody:[Dump](Box2dBody:Dump()) ()

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
