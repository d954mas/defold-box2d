# DistanceJoint
A distance joint constrains two points on two bodies to remain at a fixed
distance from each other. You can view this as a massless, rigid rod.

## Constructor

### Box2dWorld:CreateJoint(def)
Create a joint to constrain bodies together.
This may cause the connected bodies to cease colliding.
_Warning:_ This function is locked during callbacks.

**PARAMETERS**
* `def` [(Box2dJointDef)](../Joint.md) - Distance joint definition.

**RETURN**
* [(Box2dJoint)](../Joint.md)

#### JointDef
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

## Methods

* Box2dDistanceJoint:[GetLocalAnchorA](#box2ddistancejointgetlocalanchora) ()
* Box2dDistanceJoint:[GetLocalAnchorB](#box2ddistancejointgetlocalanchorb) ()
* Box2dDistanceJoint:[GetLength](#box2ddistancejointgetlength) ()
* Box2dDistanceJoint:[SetLength](#box2ddistancejointsetlengthlength) (length)
* Box2dDistanceJoint:[GetMinLength](#box2ddistancejointgetminlength) ()
* Box2dDistanceJoint:[SetMinLength](#box2ddistancejointsetminlengthminlength) (minLength)
* Box2dDistanceJoint:[GetMaxLength](#box2ddistancejointgetmaxlength) ()
* Box2dDistanceJoint:[SetMaxLength](#box2ddistancejointsetmaxlengthmaxlength) (maxLength)
* Box2dDistanceJoint:[GetCurrentLength](#box2ddistancejointgetcurrentlength) ()
* Box2dDistanceJoint:[SetStiffness](#box2ddistancejointsetstiffnessstiffness) (stiffness)
* Box2dDistanceJoint:[GetStiffness](#box2ddistancejointgetstiffness) ()
* Box2dDistanceJoint:[SetDamping](#box2ddistancejointsetdampingdamping) (damping)
* Box2dDistanceJoint:[GetDamping](#box2ddistancejointgetdamping) ()

### Box2dDistanceJoint:GetLocalAnchorA()
The local anchor point relative to bodyA's origin.

**RETURN**
* (vector3)

### Box2dDistanceJoint:GetLocalAnchorB()
The local anchor point relative to bodyB's origin.

**RETURN**
* (vector3)

### Box2dDistanceJoint:GetLength()
Get the rest length

**RETURN**
* (number)

### Box2dDistanceJoint:SetLength(length)
Set the rest length

**PARAMETERS**
* `length` (number) -

**RETURN**
* (number) - Clamped rest length

### Box2dDistanceJoint:GetMinLength()
Get the minimum length

**RETURN**
* (number)

### Box2dDistanceJoint:SetMinLength(minLength)
Set the minimum length

**PARAMETERS**
* `minLength` (number) -

**RETURN**
* (number) - The clamped minimum length

### Box2dDistanceJoint:GetMaxLength()
Get the maximum length

**RETURN**
* (number)

### Box2dDistanceJoint:SetMaxLength(maxLength)
Set the maximum length

**PARAMETERS**
* `maxLength` (number) -

**RETURN**
* (number) - The clamped maximum length

### Box2dDistanceJoint:GetCurrentLength()
Get the current length

**RETURN**
* (number)

### Box2dDistanceJoint:SetStiffness(stiffness)
Set/get the linear stiffness in N/m

**PARAMETERS**
* `stiffness` (number) -

### Box2dDistanceJoint:GetStiffness()

**RETURN**
* (number)

### Box2dDistanceJoint:SetDamping(damping)
Set/get linear damping in N*s/m

**PARAMETERS**
* `damping` (number) -

### Box2dDistanceJoint:GetDamping()

**RETURN**
* (number)
