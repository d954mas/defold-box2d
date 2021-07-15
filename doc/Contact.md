# Contact
The class manages contact between two shapes. A contact exists for each overlapping AABB in the broad-phase (except if filtered). Therefore a contact object may exist that has no contact points.

## Constructor
Never constructed. Sent as a parameter in the contact listener functions: BeginContact, EndContact, PreSolve, and PostSolve (see [`World:SetContactListener`](World.md#box2dworldsetcontactlistenerlistener)).

## Methods

* Box2dContact:[GetManifold](#box2dcontactgetmanifold) ()
* Box2dContact:[GetWorldManifold](#box2dcontactgetworldmanifold) ()
* Box2dContact:[IsTouching](#box2dcontactistouching) ()
* Box2dContact:[SetEnabled](#box2dcontactsetenabledflag) (flag)
* Box2dContact:[IsEnabled](#box2dcontactisenabled) ()
* Box2dContact:[GetFixtureA](#box2dcontactgetfixturea) ()
* Box2dContact:[GetChildIndexA](#box2dcontactgetchildindexa) ()
* Box2dContact:[GetFixtureB](#box2dcontactgetfixtureb) ()
* Box2dContact:[GetChildIndexB](#box2dcontactgetchildindexb) ()
* Box2dContact:[SetFriction](#box2dcontactsetfrictionfriction) (friction)
* Box2dContact:[GetFriction](#box2dcontactgetfriction) ()
* Box2dContact:[ResetFriction](#box2dcontactresetfriction) ()
* Box2dContact:[SetRestitution](#box2dcontactsetrestitutionrestitution) (restitution)
* Box2dContact:[GetRestitution](#box2dcontactgetrestitution) ()
* Box2dContact:[ResetRestitution](#box2dcontactresetrestitution) ()
* Box2dContact:[SetRestitutionThreshold](#box2dcontactsetrestitutionthresholdthreshold) (threshold)
* Box2dContact:[GetRestitutionThreshold](#box2dcontactgetrestitutionthreshold) ()
* Box2dContact:[ResetRestitutionThreshold](#box2dcontactresetrestitutionthreshold) ()
* Box2dContact:[SetTangentSpeed](#box2dcontactsettangentspeedspeed) (speed)
* Box2dContact:[GetTangentSpeed](#box2dcontactgettangentspeed) ()

### Box2dContact:GetManifold()
Get the local manifold.

**RETURN**
* [(Box2dManifold)](Box2dManifold.md)

### Box2dContact:GetWorldManifold()
Get the world manifold.

**RETURN**
* [(Box2dWorldManifold)](Box2dWorldManifold.md)

### Box2dContact:IsTouching()
Is this contact touching?

**RETURN**
* (boolean)

### Box2dContact:SetEnabled(flag)
Enable/disable this contact. This can be used inside the pre-solve
contact listener. The contact is only disabled for the current
time step (or sub-step in continuous collisions).

**PARAMETERS**
* `flag` (boolean)

### Box2dContact:IsEnabled()
Has this contact been disabled?

**RETURN**
* (boolean)

### Box2dContact:GetFixtureA()
Get fixture A in this contact.

**RETURN**
* [(Box2dFixture)](Fixture.md)

### Box2dContact:GetChildIndexA()
Get the child primitive index for fixture A.

**RETURN**
* (number)

### Box2dContact:GetFixtureB()
Get fixture B in this contact.

**RETURN**
* [(Box2dFixture)](Fixture.md)

### Box2dContact:GetChildIndexB()
Get the child primitive index for fixture B.

**RETURN**
* (number)

### Box2dContact:SetFriction(friction)
Override the default friction mixture. You can call this in b2ContactListener::PreSolve.
This value persists until set or reset.

**PARAMETERS**
* `friction` (number)

### Box2dContact:GetFriction()
Get the friction.

**RETURN**
* (number)

### Box2dContact:ResetFriction()
Reset the friction mixture to the default value.

### Box2dContact:SetRestitution(restitution)
Override the default restitution mixture. You can call this in b2ContactListener::PreSolve.
The value persists until you set or reset.

**PARAMETERS**
* `restitution` (number)

### Box2dContact:GetRestitution()
Get the restitution.

**RETURN**
* (number)

### Box2dContact:ResetRestitution()
Reset the restitution to the default value.

### Box2dContact:SetRestitutionThreshold(threshold)
Override the default restitution velocity threshold mixture. You can call this in b2ContactListener::PreSolve.
The value persists until you set or reset.

**PARAMETERS**
* `threshold` (number)

### Box2dContact:GetRestitutionThreshold()
Get the restitution threshold.

**RETURN**
* (number)

### Box2dContact:ResetRestitutionThreshold()
Reset the restitution threshold to the default value.

### Box2dContact:SetTangentSpeed(speed)
Set the desired tangent speed for a conveyor belt behavior. In meters per second.

**PARAMETERS**
* `speed` (number)

### Box2dContact:GetTangentSpeed()
Get the desired tangent speed. In meters per second.

**RETURN**
* (number)
