# FrictionJoint
Friction joint. This is used for top-down friction.
It provides 2D translational friction and angular friction.

## Constructor

### Box2dWorld:CreateJoint(def)
Create a joint to constrain bodies together.
This may cause the connected bodies to cease colliding.
_Warning:_ This function is locked during callbacks.

**PARAMETERS**
* `def` [(Box2dJointDef)](../Joint.md) - Friction joint definition.

**RETURN**
* [(Box2dJoint)](../Joint.md)

#### JointDef
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

## Methods

* Box2FrictionJoint:[GetLocalAnchorA](#box2frictionjointgetlocalanchora) ()
* Box2FrictionJoint:[GetLocalAnchorB](#box2frictionjointgetlocalanchorb) ()
* Box2FrictionJoint:[SetMaxForce](#box2frictionjointsetmaxforceforce) (force)
* Box2FrictionJoint:[GetMaxForce](#box2frictionjointgetmaxforce) ()
* Box2FrictionJoint:[SetMaxTorque](#box2frictionjointsetmaxtorquetorque) (torque)
* Box2FrictionJoint:[GetMaxTorque](#box2frictionjointgetmaxtorque) ()

### Box2FrictionJoint:GetLocalAnchorA()
The local anchor point relative to bodyA's origin.

**RETURN**
* (vector3)

### Box2FrictionJoint:GetLocalAnchorB()
The local anchor point relative to bodyB's origin.

**RETURN**
* (vector3)

### Box2FrictionJoint:SetMaxForce(force)
Set the maximum friction force in N.

**PARAMETERS**
* `force` (number) -

### Box2FrictionJoint:GetMaxForce()
Get the maximum friction force in N.

**RETURN**
* (number)

### Box2FrictionJoint:SetMaxTorque(torque)
Set the maximum friction torque in N*m.

**PARAMETERS**
* `torque` (number) -

### Box2FrictionJoint:GetMaxTorque()
Get the maximum friction torque in N*m.

**RETURN**
* (number)
