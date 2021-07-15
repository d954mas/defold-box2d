### WeldJoint
A weld joint essentially glues two bodies together. A weld joint may
distort somewhat because the island constraint solver is approximate.

## Constructor

### Box2dWorld:CreateJoint(def)
Create a joint to constrain bodies together.
This may cause the connected bodies to cease colliding.
_Warning:_ This function is locked during callbacks.

**PARAMETERS**
* `def` [(Box2dJointDef)](../Joint.md) - Weld joint definition.

**RETURN**
* [(Box2dJoint)](../Joint.md)

#### JointDef
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

## Methods

* Box2dWeldJoint:[GetLocalAnchorA](#box2dweldjointgetlocalanchora) ()
* Box2dWeldJoint:[GetLocalAnchorB](#box2dweldjointgetlocalanchorb) ()
* Box2dWeldJoint:[GetReferenceAngle](#box2dweldjointgetreferenceangle) ()
* Box2dWeldJoint:[SetStiffness](#box2dweldjointsetstiffnesshz) (hz)
* Box2dWeldJoint:[GetStiffness](#box2dweldjointgetstiffness) ()
* Box2dWeldJoint:[SetDamping](#box2dweldjointsetdampingdamping) (damping)
* Box2dWeldJoint:[GetDamping](#box2dweldjointgetdamping) ()

### Box2dWeldJoint:GetLocalAnchorA()
The local anchor point relative to bodyA's origin.

**RETURN**
* (vector3)

### Box2dWeldJoint:GetLocalAnchorB()
The local anchor point relative to bodyB's origin.

**RETURN**
* (vector3)

### Box2dWeldJoint:GetReferenceAngle()
Get the reference angle.

**RETURN**
* (number)

### Box2dWeldJoint:SetStiffness(hz)
Set/get stiffness in N*m

**PARAMETERS**
* `hz` (number) -

### Box2dWeldJoint:GetStiffness()

**RETURN**
* (number)

### Box2dWeldJoint:SetDamping(damping)
Set/get damping in N*m*s

**PARAMETERS**
* `damping` (number) -

### Box2dWeldJoint:GetDamping()

**RETURN**
* (number)
