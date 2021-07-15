# RevoluteJoint
A revolute joint constrains two bodies to share a common point while they
are free to rotate about the point. The relative rotation about the shared
point is the joint angle. You can limit the relative rotation with
a joint limit that specifies a lower and upper angle. You can use a motor
to drive the relative rotation about the shared point. A maximum motor torque is provided so that infinite forces are not generated.

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
Revolute joint definition. This requires defining an anchor point where the
bodies are joined. The definition uses local anchor points so that the
initial configuration can violate the constraint slightly. You also need to
specify the initial relative angle for joint limits. This helps when saving
and loading a game.

The local anchor points are measured from the body's origin
rather than the center of mass because:
1. you might not know where the center of mass will be.
2. if you add/remove shapes from a body and recompute the mass,the joints will be broken.

```lua
local Box2dRevoluteJointDef = {
    -- Initialize the bodies, anchors, and reference angle using a world
    -- anchor point.
    -- void Initialize(b2Body* bodyA, b2Body* bodyB, const b2Vec2& anchor);

    --region JointNeeded
    anchor = vmath.vector3(0), for Initialize
    --endregion

    --region JointOptional
    The local anchor point relative to bodyA's origin.
    localAnchorA = vmath.vector3(0, 0, 0),

    The local anchor point relative to bodyB's origin.
    localAnchorB = vmath.vector3(0, 0, 0),

    The bodyB angle minus bodyA angle in the reference state (radians).
    referenceAngle = 0,

    A flag to enable joint limits.
    enableLimit = false,

    The lower angle for the joint limit (radians).
    lowerAngle = 0,

    The upper angle for the joint limit (radians).
    upperAngle = 0,

    A flag to enable the joint motor.
    enableMotor = false,

    The desired motor speed. Usually in radians per second.
    motorSpeed = 0,

    The maximum motor torque used to achieve the desired motor speed.
    Usually in N-m.
    maxMotorTorque = 0,
    --endregion
}
```

## Methods

* Box2dRevoluteJoint:[GetLocalAnchorA](#box2drevolutejointgetlocalanchora) ()
* Box2dRevoluteJoint:[GetLocalAnchorB](#box2drevolutejointgetlocalanchorb) ()
* Box2dRevoluteJoint:[GetReferenceAngle](#box2drevolutejointgetreferenceangle) ()
* Box2dRevoluteJoint:[GetJointAngle](#box2drevolutejointgetjointangle) ()
* Box2dRevoluteJoint:[GetJointSpeed](#box2drevolutejointgetjointspeed) ()
* Box2dRevoluteJoint:[IsLimitEnabled](#box2drevolutejointislimitenabled) ()
* Box2dRevoluteJoint:[EnableLimit](#box2drevolutejointenablelimitflag) (flag)
* Box2dRevoluteJoint:[GetLowerLimit](#box2drevolutejointgetlowerlimit) ()
* Box2dRevoluteJoint:[GetUpperLimit](#box2drevolutejointgetupperlimit) ()
* Box2dRevoluteJoint:[SetLimits](#box2drevolutejointsetlimitslower-upper) (lower, upper)
* Box2dRevoluteJoint:[IsMotorEnabled](#box2drevolutejointismotorenabled) ()
* Box2dRevoluteJoint:[EnableMotor](#box2drevolutejointenablemotorflag) (flag)
* Box2dRevoluteJoint:[SetMotorSpeed](#box2drevolutejointsetmotorspeedspeed) (speed)
* Box2dRevoluteJoint:[GetMotorSpeed](#box2drevolutejointgetmotorspeed) ()
* Box2dRevoluteJoint:[SetMaxMotorTorque](#box2drevolutejointsetmaxmotortorquetorque) (torque)
* Box2dRevoluteJoint:[GetMaxMotorTorque](#box2drevolutejointgetmaxmotortorque) ()
* Box2dRevoluteJoint:[GetMotorTorque](#box2drevolutejointgetmotortorqueinvdt) (inv_dt)

#### Box2dRevoluteJoint:GetLocalAnchorA()
The local anchor point relative to bodyA's origin.

_RETURNS_
* <kbd>vector3</kbd>

#### Box2dRevoluteJoint:GetLocalAnchorB()
The local anchor point relative to bodyB's origin.

_RETURNS_
* <kbd>vector3</kbd>

#### Box2dRevoluteJoint:GetReferenceAngle()
Get the reference angle.

_RETURNS_
* <kbd>float</kbd>

#### Box2dRevoluteJoint:GetJointAngle(
Get the current joint angle in radians.

_RETURNS_
* <kbd>float</kbd>

#### Box2dRevoluteJoint:GetJointSpeed()
Get the current joint angle speed in radians per second.

_RETURNS_
* <kbd>float</kbd>

#### Box2dRevoluteJoint:IsLimitEnabled()
Is the joint limit enabled?

_RETURNS_
* <kbd>boolean</kbd>

#### Box2dRevoluteJoint:EnableLimit(flag)
Enable/disable the joint limit.

_ARGUMENTS_
* __flag__ <kbd>boolean</kbd> -

#### Box2dRevoluteJoint:GetLowerLimit()
Get the lower joint limit in radians.

_RETURNS_
* <kbd>float</kbd>

#### Box2dRevoluteJoint:GetUpperLimit()
Get the upper joint limit in radians.

_RETURNS_
* <kbd>float</kbd>

#### Box2dRevoluteJoint:SetLimits(lower, upper)
Set the joint limits in radians.

_ARGUMENTS_
* __lower__ <kbd>number</kbd> -
* __upper__ <kbd>number</kbd> -

#### Box2dRevoluteJoint:IsMotorEnabled()
Is the joint motor enabled?

_RETURNS_
* <kbd>boolean</kbd>

#### Box2dRevoluteJoint:EnableMotor(flag)
Enable/disable the joint motor.

_ARGUMENTS_
* __flag__ <kbd>boolean</kbd> -

#### Box2dRevoluteJoint:SetMotorSpeed(speed)
Set the motor speed in radians per second.

_ARGUMENTS_
* __speed__ <kbd>number</kbd> -

#### Box2dRevoluteJoint:GetMotorSpeed()
Get the motor speed in radians per second.

_RETURNS_
* <kbd>float</kbd>

#### Box2dRevoluteJoint:SetMaxMotorTorque(torque)
Set the maximum motor torque, usually in N-m.

_ARGUMENTS_
* __torque__ <kbd>number</kbd> -

#### Box2dRevoluteJoint:GetMaxMotorTorque()

_RETURNS_
* <kbd>float</kbd>

#### Box2dRevoluteJoint:GetMotorTorque(inv_dt)
Get the current motor torque given the inverse time step.
Unit is N*m.

_ARGUMENTS_
* __inv_dt__ <kbd>number</kbd> -

_RETURNS_
* <kbd>float</kbd>
