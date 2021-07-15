# PulleyJoint
The pulley joint is connected to two bodies and two fixed ground points.
he pulley supports a ratio such that:
length1 + ratio * length2 <= constant
Yes, the force transmitted is scaled by the ratio.
Warning: the pulley joint can get a bit squirrelly by itself. They often
work better when combined with prismatic joints. You should also cover the
the anchor points with static shapes to prevent one side from going to
zero length.

## Constructor

### Box2dWorld:CreateJoint(def)
Create a joint to constrain bodies together.
This may cause the connected bodies to cease colliding.
_Warning:_ This function is locked during callbacks.

**PARAMETERS**
* `def` [(Box2dJointDef)](../Joint.md) - Pulley joint definition.

**RETURN**
* [(Box2dJoint)](../Joint.md)

#### JointDef
Pulley joint definition. This requires two ground anchors,
two dynamic body anchor points, and a pulley ratio.

```lua
local Box2dPulleyJointDef = {
    Initialize the bodies, anchors, lengths, max lengths, and ratio using the world anchors.
    void Initialize(b2Body* bodyA, b2Body* bodyB,
        const b2Vec2& groundAnchorA, const b2Vec2& groundAnchorB,
        const b2Vec2& anchorA, const b2Vec2& anchorB,
        float ratio);

    --region JointNeeded
    anchorA = vmath.vector3(0), --for Initialize

    anchorB = vmath.vector3(0), --for Initialize

    The first ground anchor in world coordinates. This point never moves.
    groundAnchorA = vmath.vector3(0), --for Initialize

    The second ground anchor in world coordinates. This point never moves.
    groundAnchorB = vmath.vector3(0), --for Initialize

    The pulley ratio, used to simulate a block-and-tackle.
    ratio = 0, for Initialize
    --endregion

    --region JointOptional
    The local anchor point relative to bodyA's origin.
    localAnchorA = vmath.vector3(0, 0, 0),

    The local anchor point relative to bodyB\'s origin.
    localAnchorB = vmath.vector3(0, 0, 0),

    The a reference length for the segment attached to bodyA.
    lengthA = 0,

    The a reference length for the segment attached to bodyB.
    lengthB = 0
    --endregion
}
```

## Methods

* Box2dPulleyJoint:[GetGroundAnchorA](#box2dpulleyjointgetgroundanchora) ()
* Box2dPulleyJoint:[GetGroundAnchorB](#box2dpulleyjointgetgroundanchorb) ()
* Box2dPulleyJoint:[GetLengthA](#box2dpulleyjointgetlengtha) ()
* Box2dPulleyJoint:[GetLengthB](#box2dpulleyjointgetlengthb) ()
* Box2dPulleyJoint:[GetRatio](#box2dpulleyjointgetratio) ()
* Box2dPulleyJoint:[GetCurrentLengthA](#box2dpulleyjointgetcurrentlengtha) ()
* Box2dPulleyJoint:[GetCurrentLengthB](#box2dpulleyjointgetcurrentlengthb) ()

### Box2dPulleyJoint:GetGroundAnchorA()
Get the first ground anchor.

**RETURN**
* (vector3)

### Box2dPulleyJoint:GetGroundAnchorA()
Get the second ground anchor.

**RETURN**
* (vector3)

### Box2dPulleyJoint:GetGroundAnchorA()
Get the current length of the segment attached to bodyA.

**RETURN**
* (number)

### Box2dPulleyJoint:GetGroundAnchorA()
Get the current length of the segment attached to bodyB.

**RETURN**
* (number)

### Box2dPulleyJoint:GetGroundAnchorA()
Get the pulley ratio.

**RETURN**
* (number)

### Box2dPulleyJoint:GetGroundAnchorA()
Get the current length of the segment attached to bodyA.

**RETURN**
* (number)

### Box2dPulleyJoint:GetGroundAnchorA()
Get the current length of the segment attached to bodyB.

**RETURN**
* (number)
