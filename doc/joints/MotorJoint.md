# MotorJoint
A motor joint is used to control the relative motion
between two bodies. A typical usage is to control the movement
of a dynamic body with respect to the ground.

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
Motor joint definition.

```lua
local Box2MotorJointDef = {
    -- Initialize the bodies and offsets using the current transforms.
    --void Initialize(b2Body* bodyA, b2Body* bodyB);
    --region JointNeeded
    --endregion

    --region JointOptional
    The maximum motor force in N.
    maxForce = vmath.vector3(0, 0, 0),

    The maximum motor torque in N-m.
    maxTorque = vmath.vector3(0, 0, 0),

    Position of bodyB minus the position of bodyA, in bodyA's frame, in meters.
    linearOffset = 0,

    The bodyB angle minus bodyA angle in radians.
    angularOffset = 0,

    Position correction factor in the range [0,1].
    correctionFactor = 0,
    --endregion
}
```

## Methods

* Box2dMotorJoint:[SetLinearOffset](#box2dmotorjointsetlinearoffsetlinearoffset) (linearOffset)
* Box2dMotorJoint:[GetLinearOffset](#box2dmotorjointgetlinearoffset) ()
* Box2dMotorJoint:[SetAngularOffset](#box2dmotorjointsetangularoffsetangularoffset) (angularOffset)
* Box2dMotorJoint:[GetAngularOffset](#box2dmotorjointgetangularoffset) ()
* Box2dMotorJoint:[SetMaxForce](#box2dmotorjointsetmaxforceforce) (force)
* Box2dMotorJoint:[GetMaxForce](#box2dmotorjointgetmaxforce) ()
* Box2dMotorJoint:[SetMaxTorque](#box2dmotorjointsetmaxtorquetorque) (torque)
* Box2dMotorJoint:[GetMaxTorque](#box2dmotorjointgetmaxtorque) ()
* Box2dMotorJoint:[SetCorrectionFactor](#box2dmotorjointsetcorrectionfactorfactor) (factor)
* Box2dMotorJoint:[GetCorrectionFactor](#box2dmotorjointgetcorrectionfactor) ()

#### Box2dMotorJoint:SetLinearOffset(linearOffset)
Set/get the target linear offset, in frame A, in meters.
* __linearOffset__ <kbd>vector3</kbd> -

#### Box2dMotorJoint:GetLinearOffset()

_RETURNS_
* <kbd>vector3</kbd>

#### Box2dMotorJoint:SetAngularOffset(angularOffset)
Set/get the target angular offset, in radians.

_ARGUMENTS_
* __angularOffset__ <kbd>number</kbd> -

#### Box2dMotorJoint:GetAngularOffset()

_RETURNS_
* <kbd>number</kbd>

#### Box2dMotorJoint:SetMaxForce(force)
Set the maximum friction force in N.

_ARGUMENTS_
* __force__ <kbd>number</kbd> -

#### Box2dMotorJoint:GetMaxForce()
Get the maximum friction force in N.

_RETURNS_
* <kbd>number</kbd>

#### Box2dMotorJoint:SetMaxTorque(torque)
Set the maximum friction torque in N*m.

_ARGUMENTS_
* __torque__ <kbd>number</kbd> -

#### Box2dMotorJoint:GetMaxTorque()
Get the maximum friction torque in N*m.

_RETURNS_
* <kbd>number</kbd>

#### Box2dMotorJoint:SetCorrectionFactor(factor)
Set the position correction factor in the range [0,1].

_ARGUMENTS_
* __factor__ <kbd>number</kbd> -

#### Box2dMotorJoint:GetCorrectionFactor()
Get the position correction factor in the range [0,1].

_RETURNS_
* <kbd>number</kbd>
