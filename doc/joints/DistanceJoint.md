# DistanceJoint
A distance joint constrains two points on two bodies to remain at a fixed
distance from each other. You can view this as a massless, rigid rod.

## Constructor

#### Box2dWorld:CreateJoint(def)
Create a joint to constrain bodies together.
This may cause the connected bodies to cease colliding.
_Warning:_ This function is locked during callbacks.

_ARGUMENTS_
* __def__ <kbd>Box2dJointDef</kbd> -

_RETURNS_
* <kbd>Box2dJoint</kbd>
Friction joint definition.

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

#### Box2dDistanceJoint:GetLocalAnchorA()
The local anchor point relative to bodyA's origin.

_RETURNS_
* <kbd>vector3</kbd>

#### Box2dDistanceJoint:GetLocalAnchorB()
The local anchor point relative to bodyB's origin.

_RETURNS_
* <kbd>vector3</kbd>

#### Box2dDistanceJoint:GetLength()
Get the rest length

_RETURNS_
* <kbd>number</kbd>

#### Box2dDistanceJoint:SetLength(length)
Set the rest length

_ARGUMENTS_
* __length__ <kbd>number</kbd> -

_RETURNS_
* <kbd>number</kbd> - Clamped rest length

#### Box2dDistanceJoint:GetMinLength()
Get the minimum length

_RETURNS_
* <kbd>number</kbd>

#### Box2dDistanceJoint:SetMinLength(minLength)
Set the minimum length

_ARGUMENTS_
* __minLength__ <kbd>number</kbd> -

_RETURNS_
* <kbd>number</kbd> - The clamped minimum length

#### Box2dDistanceJoint:GetMaxLength()
Get the maximum length

_RETURNS_
* <kbd>number</kbd>

#### Box2dDistanceJoint:SetMaxLength(maxLength)
Set the maximum length

_ARGUMENTS_
* __maxLength__ <kbd>number</kbd> -

_RETURNS_
* <kbd>number</kbd> - The clamped maximum length

#### Box2dDistanceJoint:GetCurrentLength()
Get the current length

_RETURNS_
* <kbd>number</kbd>

#### Box2dDistanceJoint:SetStiffness(stiffness)
Set/get the linear stiffness in N/m

_ARGUMENTS_
* __stiffness__ <kbd>number</kbd> -

#### Box2dDistanceJoint:GetStiffness()

_RETURNS_
* <kbd>number</kbd>

#### Box2dDistanceJoint:SetDamping(damping)
Set/get linear damping in N*s/m

_ARGUMENTS_
* __damping__ <kbd>number</kbd> -

#### Box2dDistanceJoint:GetDamping()

_RETURNS_
* <kbd>number</kbd>
