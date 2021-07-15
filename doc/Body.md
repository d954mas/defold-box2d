# Body
A chunk of matter that is so strong that the distance between any two bits of matter on the chunk is constant. They are hard like a diamond. In the following discussion we use body interchangeably with rigid body.

A rigid body. These are created via world:CreateBody.

## Constructor

### Box2dWorld:CreateBody(bodyDef)
Create a rigid body given a definition.
_Warning:_ This function is locked during callbacks.

**PARAMETERS**
* `bodyDef` [(Box2dBodyDef)](BodyDef.md) -

**RETURN**
* [(Box2dBody)](Body.md)

## Methods

* Box2dBody:[CreateFixture](#box2dbodycreatefixturedef) (def)
* Box2dBody:[CreateFixture](#box2dbodycreatefixtureshape-density) (shape, density)
* Box2dBody:[DestroyFixture](#box2dbodydestroyfixturefixture) (fixture)
* Box2dBody:[SetTransform](#box2dbodysettransformposition-angle) (position, angle)
* Box2dBody:[GetTransform](#box2dbodygettransform) ()
* Box2dBody:[GetPosition](#box2dbodygetposition) ()
* Box2dBody:[GetAngle](#box2dbodygetangle) ()
* Box2dBody:[GetWorldCenter](#box2dbodygetworldcenter) ()
* Box2dBody:[GetLocalCenter](#box2dbodygetlocalcenter) ()
* Box2dBody:[SetLinearVelocity](#box2dbodysetlinearvelocityvelocity) (velocity)
* Box2dBody:[GetLinearVelocity](#box2dbodygetlinearvelocity) ()
* Box2dBody:[SetAngularVelocity](#box2dbodysetangularvelocityomega) (omega)
* Box2dBody:[GetAngularVelocity](#box2dbodygetangularvelocity) ()
* Box2dBody:[ApplyForce](#box2dbodyapplyforceforce-point-wake) (force, point, wake)
* Box2dBody:[ApplyForceToCenter](#box2dbodyapplyforcetocenterforce-wake) (force, wake)
* Box2dBody:[ApplyTorque](#box2dbodyapplytorquetorque-wake) (torque, wake)
* Box2dBody:[ApplyLinearImpulse](#box2dbodyapplylinearimpulseimpulse-point-wake) (impulse, point, wake)
* Box2dBody:[ApplyLinearImpulseToCenter](#box2dbodyapplylinearimpulsetocenterimpulse-wake) (impulse, wake)
* Box2dBody:[ApplyAngularImpulse](#box2dbodyapplyangularimpulseimpulse-wake) (impulse, wake)
* Box2dBody:[GetMass](#box2dbodygetmass) ()
* Box2dBody:[GetInertia](#box2dbodygetinertia) ()
* Box2dBody:[ResetMassData](#box2dbodyresetmassdata) ()
* Box2dBody:[GetMassData](#box2dbodygetmassdata) ()
* Box2dBody:[SetMassData](#box2dbodysetmassdatadata) (data)
* Box2dBody:[GetWorldPoint](#box2dbodygetworldpointlocalpoint) (localPoint)
* Box2dBody:[GetWorldVector](#box2dbodygetworldvectorlocalvector) (localVector)
* Box2dBody:[GetLocalPoint](#box2dbodygetlocalpointworldpoint) (worldPoint)
* Box2dBody:[GetLocalVector](#box2dbodygetlocalvectorworldvector) (worldVector)
* Box2dBody:[GetLinearVelocityFromWorldPoint](#box2dbodygetlinearvelocityfromworldpointworldpoint) (worldPoint)
* Box2dBody:[GetLinearVelocityFromLocalPoint](#box2dbodygetlinearvelocityfromlocalpointlocalpoint) (localPoint)
* Box2dBody:[SetLinearDamping](#box2dbodysetlineardampinglineardamping) (linearDamping)
* Box2dBody:[GetLinearDamping](#box2dbodygetlineardamping) ()
* Box2dBody:[SetAngularDamping](#box2dbodysetangulardampingangulardamping) (angularDamping)
* Box2dBody:[GetAngularDamping](#box2dbodygetangulardamping) ()
* Box2dBody:[SetGravityScale](#box2dbodysetgravityscalescale) (scale)
* Box2dBody:[GetGravityScale](#box2dbodygetgravityscale) ()
* Box2dBody:[SetType](#box2dbodysettypetype) (type)
* Box2dBody:[GetType](#box2dbodygettype) ()
* Box2dBody:[SetBullet](#box2dbodysetbulletflag) (flag)
* Box2dBody:[IsBullet](#box2dbodyisbullet) ()
* Box2dBody:[SetSleepingAllowed](#box2dbodysetsleepingallowedflag) (flag)
* Box2dBody:[IsSleepingAllowed](#box2dbodyissleepingallowed) ()
* Box2dBody:[SetAwake](#box2dbodysetawakeflag) (flag)
* Box2dBody:[IsAwake](#box2dbodyisawake) ()
* Box2dBody:[SetEnabled](#box2dbodysetenabledflag) (flag)
* Box2dBody:[IsEnabled](#box2dbodyisenabled) ()
* Box2dBody:[SetFixedRotation](#box2dbodysetfixedrotationflag) (flag)
* Box2dBody:[IsFixedRotation](#box2dbodyisfixedrotation) ()
* Box2dBody:[GetNext](#box2dbodygetnext) ()
* Box2dBody:[GetFixtureList](#box2dbodygetfixturelist) ()
* Box2dBody:[GetUserData](#box2dbodygetuserdata) ()
* Box2dBody:[SetUserData](#box2dbodysetuserdatadata) (data)
* Box2dBody:[GetWorld](#box2dbodygetworld) ()
* Box2dBody:[Dump](#box2dbodydump) ()

---
### Box2dBody:CreateFixture(def)
Creates a fixture and attach it to this body. Use this function if you need
to set some fixture parameters, like friction. Otherwise you can create the
fixture directly from a shape.
If the density is non-zero, this function automatically updates the mass of the body.
Contacts are not created until the next time step.
_Warning:_ This function is locked during callbacks.

**PARAMETERS**
* `def` [(Box2dFixtureDef)](FixtureDef.md)

**RETURN**
* [(Box2dFixture)](Fixture.md)

---
### Box2dBody:CreateFixture(shape, density)
Creates a fixture from a shape and attach it to this body.
This is a convenience function. Use b2FixtureDef if you need to set parameters
like friction, restitution, user data, or filtering.
If the density is non-zero, this function automatically updates the mass of the body.
_Warning:_ This function is locked during callbacks.

**PARAMETERS**
* `shape` [(Box2dShape)](Shape.md) -
* `density` (number) - The shape density (set to zero for static bodies)

**RETURN**
* [(Box2dFixture)](Fixture.md)

---
### Box2dBody:DestroyFixture(fixture)
Destroy a fixture. This removes the fixture from the broad-phase and
destroys all contacts associated with this fixture. This will
automatically adjust the mass of the body if the body is dynamic and the
fixture has positive density.
All fixtures attached to a body are implicitly destroyed when the body is destroyed.
_Warning:_ This function is locked during callbacks.

**PARAMETERS**
* `fixture` [(Box2dFixture)](Fixture.md) -

---
### Box2dBody:SetTransform(position, angle)
Set the position of the body's origin and rotation.
Manipulating a body's transform may cause non-physical behavior.
Note: contacts are updated on the next call to b2World::Step.

**PARAMETERS**
* `position` (vector3) - The world position of the body's local origin.
* `angle` (number|nil) - The world rotation in radians. If nil use current angle

---
### Box2dBody:GetTransform()
Get the body transform for the body's origin.

**RETURN**
* (vector3) - Position
* (number) - Angle

---
### Box2dBody:GetPosition()
Get the world body origin position.

**RETURN**
* (vector3)

---
### Box2dBody:GetAngle()
Get the angle in radians.

**RETURN**
* (number)

---
### Box2dBody:GetWorldCenter()
Get the world position of the center of mass.

**RETURN**
* (vector3)

---
### Box2dBody:GetLocalCenter()
Get the local position of the center of mass.

**RETURN**
* (vector3)

---
### Box2dBody:SetLinearVelocity(velocity)
Set the linear velocity of the center of mass.

**PARAMETERS**
* `velocity` (vector3) -

---
### Box2dBody:GetLinearVelocity()
Get the linear velocity of the center of mass.

**RETURN**
* (vector3)

---
### Box2dBody:SetAngularVelocity(omega)
Set the angular velocity.

**PARAMETERS**
* `omega` (number) - The new angular velocity in radians/second.

---
### Box2dBody:GetAngularVelocity()
Get the angular velocity.

**RETURN**
* (number) - The angular velocity in radians/second.

---
### Box2dBody:ApplyForce(force, point, wake)
Apply a force at a world point. If the force is not
applied at the center of mass, it will generate a torque and
affect the angular velocity. This wakes up the body.

**PARAMETERS**
* `force` (vector3) - Force the world force vector, usually in Newtons (N).
* `point` (vector3) - Point the world position of the point of application.
* `wake` (boolean) - Wake also wake up the body

---
### Box2dBody:ApplyForceToCenter(force, wake)
Apply a force to the center of mass. This wakes up the body.

**PARAMETERS**
* `force` (vector3) - Force the world force vector, usually in Newtons (N).
* `wake` (boolean) - Wake also wake up the body

---
### Box2dBody:ApplyTorque(torque, wake)
Apply a torque. This affects the angular velocity
without affecting the linear velocity of the center of mass.

**PARAMETERS**
* `torque` (number) - Torque about the z-axis (out of the screen), usually in N-m.
* `wake` (boolean) - Wake also wake up the body

---
### Box2dBody:ApplyLinearImpulse(impulse, point, wake)
Apply an impulse at a point. This immediately modifies the velocity.
It also modifies the angular velocity if the point of application
is not at the center of mass. This wakes up the body.

**PARAMETERS**
* `impulse` (vector3) - Impulse the world impulse vector, usually in N-seconds or kg-m/s.
* `point` (vector3) - Point the world position of the point of application.
* `wake` (boolean) - Wake also wake up the body

---
### Box2dBody:ApplyLinearImpulseToCenter(impulse, wake)
Apply an impulse to the center of mass. This immediately modifies the velocity.

**PARAMETERS**
* `impulse` (vector3) - Impulse the world impulse vector, usually in N-seconds or kg-m/s.
* `wake` (boolean) - Wake also wake up the body

---
### Box2dBody:ApplyAngularImpulse(impulse, wake)
Apply an angular impulse.

**PARAMETERS**
* `impulse` (vector3) - Impulse the angular impulse in units of kg*m*m/s
* `wake` (boolean) - Wake also wake up the body

---
### Box2dBody:GetMass()
Get the total mass of the body.

**RETURN**
* (number) - The mass, usually in kilograms (kg).

---
### Box2dBody:GetInertia()
Get the rotational inertia of the body about the local origin.

**RETURN**
* (number) - The rotational inertia, usually in kg-m^2.

---
### Box2dBody:ResetMassData()
This resets the mass properties to the sum of the mass properties of the fixtures.
This normally does not need to be called unless you called SetMassData to override
the mass and you later want to reset the mass.

---
### Box2dBody:GetMassData()
Get the mass data of the body.

**RETURN**
* [(Box2dMassData)](Box2dMassData.md) - A struct containing the mass, inertia and center of ### bod

---
### Box2dBody:SetMassData(data)
Set the mass properties to override the mass properties of the fixtures.
Note that this changes the center of mass position.
Note that creating or destroying fixtures can also alter the mass.
This function has no effect if the body isn't dynamic.

**PARAMETERS**
* `data` [(Box2dMassData)](Box2dMassData.md) - The mass properties.

---
### Box2dBody:GetWorldPoint(localPoint)
Get the world coordinates of a point given the local coordinates.

**PARAMETERS**
* `localPoint` (vector3) - A point on the body measured relative the the body's origin.

**RETURN**
* (vector3) - The same point expressed in world coordinates.

---
### Box2dBody:GetWorldVector(localVector)
Get the world coordinates of a vector given the local coordinates.

**PARAMETERS**
* `localVector` (vector3) - LocalVector a vector fixed in the body.

**RETURN**
* (vector3) - The same vector expressed in world coordinates.

---
### Box2dBody:GetLocalPoint(worldPoint)
Gets a local point relative to the body's origin given a world point.

**PARAMETERS**
* `worldPoint` (vector3) - WorldPoint a point in world coordinates.

**RETURN**
* (vector3) - The corresponding local point relative to the body's origin.

---
### Box2dBody:GetLocalVector(worldVector)
Gets a local vector given a world vector.

**PARAMETERS**
* `worldVector` (vector3) - WorldVector a vector in world coordinates.

**RETURN**
* (vector3) - The corresponding local vector.

---
### Box2dBody:GetLinearVelocityFromWorldPoint(worldPoint)
Get the world linear velocity of a world point attached to this body.

**PARAMETERS**
* `worldPoint` (vector3) - WorldPoint a point in world coordinates.

**RETURN**
* (vector3) - The world velocity of a point.

---
### Box2dBody:GetLinearVelocityFromLocalPoint(localPoint)
Get the world velocity of a local point.

**PARAMETERS**
* `localPoint` (vector3) - LocalPoint a point in local coordinates.

**RETURN**
* (vector3) - The world velocity of a point.

---
### Box2dBody:SetLinearDamping(linearDamping)
Set the linear damping of the body.

**PARAMETERS**
* `linearDamping` (number) -

---
### Box2dBody:GetLinearDamping()
Get the linear damping of the body.

**RETURN**
* (number)

---
### Box2dBody:SetAngularDamping(angularDamping)
Set the angular damping of the body.

**PARAMETERS**
* `angularDamping` (number) -

---
### Box2dBody:GetAngularDamping()
Get the angular damping of the body.

**RETURN**
* (number)

---
### Box2dBody:SetGravityScale(scale)
Set the gravity scale of the body.

**PARAMETERS**
* `scale` (number) -

---
### Box2dBody:GetGravityScale()
Get the gravity scale of the body.

**RETURN**
* (number)

---
### Box2dBody:SetType(type)
Set the type of this body. This may alter the mass and velocity.

**PARAMETERS**
* `type` (number) - Box2d.b2BodyType

---
### Box2dBody:GetType()
Get the type of this body.

**RETURN**
* (number) - Box2d.b2BodyType

---
### Box2dBody:SetBullet(flag)
Should this body be treated like a bullet for continuous collision detection?

**PARAMETERS**
* `flag` (boolean) -

---
### Box2dBody:IsBullet()
Is this body treated like a bullet for continuous collision detection?

**RETURN**
* (boolean)

---
### Box2dBody:SetSleepingAllowed(flag)
You can disable sleeping on this body. If you disable sleeping, the
body will be woken.

**PARAMETERS**
* `flag` (boolean) -

---
### Box2dBody:IsSleepingAllowed()
Is this body allowed to sleep

**RETURN**
* (boolean)

---
### Box2dBody:SetAwake(flag)
Set the sleep state of the body. A sleeping body has very
low CPU cost.

**PARAMETERS**
* `flag` (boolean) - Flag set to true to wake the body, false to put it to sleep.

---
### Box2dBody:IsAwake()
Get the sleeping state of this body.

**RETURN**
* (boolean) -  true if the body is awake.

---
### Box2dBody:SetEnabled(flag)
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

**PARAMETERS**
* `flag` (boolean) -

---
### Box2dBody:IsEnabled()
Get the active state of the body.

**RETURN**
* (boolean)

---
### Box2dBody:SetFixedRotation(flag)
Set this body to have fixed rotation. This causes the mass
to be reset.

**PARAMETERS**
* `flag` (boolean) -

---
### Box2dBody:IsFixedRotation()
Does this body have fixed rotation?

**RETURN**
* (boolean)

---
### Box2dBody:GetNext()
Get the next body in the world's body list.

**RETURN**
* [(Box2dBody)](Body.md)

---
### Box2dBody:GetFixtureList()
Get the first fixture in list of all fixtures attached to this body or nil

**RETURN**
* [(Box2dFixture)](Fixture.md)|(nil)

---
### Box2dBody:GetUserData()
Get the user data table. Use this to store your application specific data.

**RETURN**
* (table|nil)

---
### Box2dBody:SetUserData(data)
Set the user data. Use this to store your application specific data.

**PARAMETERS**
* `data` (table|nil) -

---
### Box2dBody:GetWorld()
Get the parent world of this body.

**RETURN**
* [(Box2dWorld)](World.md)

---
### Box2dBody:Dump()
Dump this body to a file
