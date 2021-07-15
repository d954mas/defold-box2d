# MouseJoint
A mouse joint is used to make a point on a body track a
specified world point. This a soft constraint with a maximum
force. This allows the constraint to stretch and without
applying huge forces.
NOTE: this joint is not documented in the manual because it was
developed to be used in the testbed. If you want to learn how to
use the mouse joint, look at the testbed.

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
Mouse joint definition. This requires a world target point,
tuning parameters, and the time step.

```lua
local Box2dMouseJointDef = {
    --region JointNeeded
    --endregion

    --region JointOptional
    The linear stiffness in N/m
    stiffness = 0,

    The linear damping in N*s/m
    damping = 0,

    The initial world target point. This is assumed
    to coincide with the body anchor initially.
    target = vmath.vector3(0),

    The maximum constraint force that can be exerted
    to move the candidate body. Usually you will express
    as some multiple of the weight (multiplier * mass * gravity).
    maxForce = 0
    --endregion
}
```

## Methods

* Box2dMouseJoint:[SetTarget](#box2dmousejointsettargettarget) (target)
* Box2dMouseJoint:[GetTarget](#box2dmousejointgettarget) ()
* Box2dMouseJoint:[SetMaxForce](#box2dmousejointsetmaxforceforce) (force)
* Box2dMouseJoint:[GetMaxForce](#box2dmousejointgetmaxforce) ()
* Box2dMouseJoint:[SetStiffness](#box2dmousejointsetstiffnessstiffness) (stiffness)
* Box2dMouseJoint:[GetStiffness](#box2dmousejointgetstiffness) ()
* Box2dMouseJoint:[SetDamping](#box2dmousejointsetdampingdamping) (damping)
* Box2dMouseJoint:[GetDamping](#box2dmousejointgetdamping) ()

#### Box2dMouseJoint:SetTarget(target)
Use this to update the target point.

_ARGUMENTS_
* __target__ <kbd>vector3</kbd> -

#### Box2dMouseJoint:GetTarget()

_RETURNS_
* <kbd>vector3</kbd>

#### Box2dMouseJoint:SetMaxForce(force)
Set/get the maximum force in Newtons.

_ARGUMENTS_
* __force__ <kbd>number</kbd> -

#### Box2dMouseJoint:GetMaxForce()

_RETURNS_
* <kbd>number</kbd>

#### Box2dMouseJoint:SetStiffness(stiffness)
Set/get the linear stiffness in N/m

_ARGUMENTS_
* __stiffness__ <kbd>number</kbd> -

#### Box2dMouseJoint:GetStiffness()

_RETURNS_
* <kbd>number</kbd>

#### Box2dMouseJoint:SetDamping(damping)
Set/get linear damping in N*s/m

_ARGUMENTS_
* __damping__ <kbd>number</kbd> -

#### Box2dMouseJoint:GetDamping()

_RETURNS_
* <kbd>number</kbd>
