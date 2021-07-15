# Fixture
A fixture binds a shape to a body and adds material properties such as density, friction, and restitution. A fixture puts a shape into the collision system (broad-phase) so that it can collide with other shapes.

## Constructors

#### Box2dBody:CreateFixture(def)
Creates a fixture and attach it to this body. Use this function if you need
to set some fixture parameters, like friction. Otherwise you can create the
fixture directly from a shape.
If the density is non-zero, this function automatically updates the mass of the body.
Contacts are not created until the next time step.
_Warning:_ This function is locked during callbacks.

_ARGUMENTS_
* __def__ [`Box2dFixtureDef`](doc/FixtureDef.md)

_RETURNS_
* [`Box2dFixture`](doc/Fixture.md)

#### Box2dBody:CreateFixture(shape, density)
Creates a fixture from a shape and attach it to this body.
This is a convenience function. Use b2FixtureDef if you need to set parameters
like friction, restitution, user data, or filtering.
If the density is non-zero, this function automatically updates the mass of the body.
_Warning:_ This function is locked during callbacks.

_ARGUMENTS_
* __shape__ [`Box2dShape`](doc/Shape.md) -
* __density__ <kbd>number</kbd> - The shape density (set to zero for static bodies)

_RETURNS_
* [`Box2dFixture`](doc/Fixture.md)

## Methods

* Box2dFixture:[GetType](#box2dfixturegettype) ()
* Box2dFixture:[SetSensor](#box2dfixturesetsensorsensor) (sensor)
* Box2dFixture:[IsSensor](#box2dfixtureissensor) ()
* Box2dFixture:[Refilter](#box2dfixturerefilter) ()
* Box2dFixture:[GetBody](#box2dfixturegetbody) ()
* Box2dFixture:[GetNext](#box2dfixturegetnext) ()
* Box2dFixture:[GetUserData](#box2dfixturegetuserdata) ()
* Box2dFixture:[SetUserData](#box2dfixturesetuserdatauserdata) (userdata)
* Box2dFixture:[TestPoint](#box2dfixturetestpointpoint) (point)
* Box2dFixture:[GetMassData](#box2dfixturegetmassdata) ()
* Box2dFixture:[GetDensity](#box2dfixturegetdensity) ()
* Box2dFixture:[SetDensity](#box2dfixturesetdensitydensity) (density)
* Box2dFixture:[GetFriction](#box2dfixturegetfriction) ()
* Box2dFixture:[SetFriction](#box2dfixturesetfrictionfriction) (friction)
* Box2dFixture:[GetRestitution](#box2dfixturegetrestitution) ()
* Box2dFixture:[SetRestitution](#box2dfixturesetrestitutionrestitution) (restitution)
* Box2dFixture:[GetRestitutionThreshold](#box2dfixturegetrestitutionthreshold) ()
* Box2dFixture:[SetRestitutionThreshold](#box2dfixturesetrestitutionthresholdthreshold) (threshold)
* Box2dFixture:[Dump](#box2dfixturedumpbodyindex) (bodyIndex)

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
* [`Box2dBody`](doc/Body.md) - The parent body

#### Box2dFixture:GetNext()
Get the next fixture in the parent body's fixture list.

_RETURNS_
* [`Box2dFixture`](doc/Fixture.md)|<kbd>nil</kbd>

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
* [`Box2dMassData`](doc/Box2dMassData.md)

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
