### WeldJoint
A weld joint essentially glues two bodies together. A weld joint may
distort somewhat because the island constraint solver is approximate.

## Constructor

#### Box2dWorld:CreateJoint(def)
Create a joint to constrain bodies together.
This may cause the connected bodies to cease colliding.
_Warning:_ This function is locked during callbacks.

_ARGUMENTS_
* __def__ [`Box2dJointDef`](../Joint.md) - Weld joint definition.

_RETURNS_
* [`Box2dJoint`](../Joint.md)

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

#### Box2dWeldJoint:GetLocalAnchorA()
The local anchor point relative to bodyA's origin.

_RETURNS_
* <kbd>vector3</kbd>

#### Box2dWeldJoint:GetLocalAnchorB()
The local anchor point relative to bodyB's origin.

_RETURNS_
* <kbd>vector3</kbd>

#### Box2dWeldJoint:GetReferenceAngle()
Get the reference angle.

_RETURNS_
* <kbd>number</kbd>

#### Box2dWeldJoint:SetStiffness(hz)
Set/get stiffness in N*m

_ARGUMENTS_
* __hz__ <kbd>number</kbd> -

#### Box2dWeldJoint:GetStiffness()

_RETURNS_
* <kbd>number</kbd>

#### Box2dWeldJoint:SetDamping(damping)
Set/get damping in N*m*s

_ARGUMENTS_
* __damping__ <kbd>number</kbd> -

#### Box2dWeldJoint:GetDamping()

_RETURNS_
* <kbd>number</kbd>
