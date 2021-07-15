# Contact
The class manages contact between two shapes. A contact exists for each overlapping AABB in the broad-phase (except if filtered). Therefore a contact object may exist that has no contact points.

## Constructor
Never constructed. Sent as a parameter in the contact lister functions: BeginContact, EndContact, PreSolve, PostSolve

## Methods

#### Box2dContact:GetManifold()
Get the local manifold.

_RETURNS_
* <kbd>Box2dManifold</kbd>

#### Box2dContact:GetWorldManifold()
Get the world manifold.

_RETURNS_
* <kbd>Box2dWorldManifold</kbd>

#### Box2dContact:IsTouching()
Is this contact touching?

_RETURNS_
* <kbd>boolean</kbd>

#### Box2dContact:SetEnabled(flag)
Enable/disable this contact. This can be used inside the pre-solve
contact listener. The contact is only disabled for the current
time step (or sub-step in continuous collisions).

_ARGUMENTS_
* __flag__ <kbd>boolean</kbd>

#### Box2dContact:IsEnabled()
Has this contact been disabled?

_RETURNS_
* <kbd>boolean</kbd>

#### Box2dContact:GetFixtureA()
Get fixture A in this contact.

_RETURNS_
* <kbd>Box2dFixture</kbd>

#### Box2dContact:GetChildIndexA()
Get the child primitive index for fixture A.

_RETURNS_
* <kbd>number</kbd>

#### Box2dContact:GetFixtureB()
Get fixture B in this contact.

_RETURNS_
* <kbd>Box2dFixture</kbd>

#### Box2dContact:GetChildIndexB()
Get the child primitive index for fixture B.

_RETURNS_
* <kbd>number</kbd>

#### Box2dContact:SetFriction(friction)
Override the default friction mixture. You can call this in b2ContactListener::PreSolve.
This value persists until set or reset.

_ARGUMENTS_
* __friction__ <kbd>number</kbd>

#### Box2dContact:GetFriction()
Get the friction.

_RETURNS_
* <kbd>number</kbd>

#### Box2dContact:ResetFriction()
Reset the friction mixture to the default value.

#### Box2dContact:SetRestitution(restitution)
Override the default restitution mixture. You can call this in b2ContactListener::PreSolve.
The value persists until you set or reset.

_ARGUMENTS_
* __restitution__ <kbd>number</kbd>

#### Box2dContact:GetRestitution()
Get the restitution.

_RETURNS_
* <kbd>number</kbd>

#### Box2dContact:ResetRestitution()
Reset the restitution to the default value.

#### Box2dContact:SetRestitutionThreshold(threshold)
Override the default restitution velocity threshold mixture. You can call this in b2ContactListener::PreSolve.
The value persists until you set or reset.

_ARGUMENTS_
* __threshold__ <kbd>number</kbd>

#### Box2dContact:GetRestitutionThreshold()
Get the restitution threshold.

_RETURNS_
* <kbd>number</kbd>

#### Box2dContact:ResetRestitutionThreshold()
Reset the restitution threshold to the default value.

#### Box2dContact:SetTangentSpeed(speed)
Set the desired tangent speed for a conveyor belt behavior. In meters per second.

_ARGUMENTS_
* __speed__ <kbd>number</kbd>

#### Box2dContact:GetTangentSpeed()
Get the desired tangent speed. In meters per second.

_RETURNS_
* <kbd>number</kbd>
