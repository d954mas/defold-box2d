# GearJoint
A gear joint is used to connect two joints together. Either joint
can be a revolute or prismatic joint. You specify a gear ratio
to bind the motions together:
coordinate1 + ratio * coordinate2 = constant
The ratio can be negative or positive. If one joint is a revolute joint
and the other joint is a prismatic joint, then the ratio will have units
of length or units of 1/length.
_Warning:_ You have to manually destroy the gear joint if joint1 or joint2
is destroyed.

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
Gear joint definition. This definition requires two existing
revolute or prismatic joints (any combination will work).
@_Warning:_ bodyB on the input joints must both be dynamic

```lua
local Box2dGearJointDef = {
    --region JointNeeded
    The first revolute/prismatic joint attached to the gear joint.
    @type Box2dJoint
    joint1 = nil,

    The second revolute/prismatic joint attached to the gear joint.
    @type Box2dJoint
    joint2 = nil,
    --endregion

    --region JointOptional
    The gear ratio.
    @see Box2dGearJoint for explanation.
    ratio = 0
    --endregion
}
```

## Methods

* Box2dGearJoint:[GetJoint1](#box2dgearjointgetjoint1) ()
* Box2dGearJoint:[GetJoint2](#box2dgearjointgetjoint2) ()
* Box2dGearJoint:[SetRatio](#box2dgearjointsetratioratio) (ratio)
* Box2dGearJoint:[GetRatio](#box2dgearjointgetratio) ()

#### Box2dGearJoint:GetJoint1()
Get the first joint.

_RETURNS_
* <kbd>Box2dJoint</kbd>

#### Box2dGearJoint:GetJoint2()
Get the second joint.

_RETURNS_
* <kbd>Box2dJoint</kbd>

#### Box2dGearJoint:SetRatio(ratio)
Set/Get the gear ratio.

_ARGUMENTS_
* __ratio__ <kbd>number</kbd> -

#### Box2dGearJoint:GetRatio()

_RETURNS_
* <kbd>number</kbd>
