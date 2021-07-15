# WheelJoint
A wheel joint. This joint provides two degrees of freedom: translation along an axis fixed in bodyA and rotation in the plane. In other words, it is a point to line constraint with a rotational motor and a linear spring/damper. The spring/damper is initialized upon creation. This joint is designed for vehicle suspensions.

## Constructor

### Box2dWorld:CreateJoint(def)
Create a joint to constrain bodies together.
This may cause the connected bodies to cease colliding.
_Warning:_ This function is locked during callbacks.

**PARAMETERS**
* `def` [(Box2dJointDef)](../Joint.md) - Wheel joint definition.

**RETURN**
* [(Box2dJoint)](../Joint.md)

#### JointDef
Wheel joint definition. This requires defining a line of
motion using an axis and an anchor point. The definition uses local
anchor points and a local axis so that the initial configuration
can violate the constraint slightly. The joint translation is zero
when the local anchor points coincide in world space. Using local
anchors and a local axis helps when saving and loading a game.

```lua
local Box2dWheelJointDef = {
    Initialize the bodies, anchors, axis, and reference angle using the world
    anchor and world axis.
    void Initialize(b2Body* bodyA, b2Body* bodyB, const b2Vec2& anchor, const b2Vec2& axis);
    --region JointNeeded
    anchor = vmath.vector3(0), --for Initialize
    axis = vmath.vector3(0), --for Initialize
    --endregion

    --region JointOptional
    The local anchor point relative to bodyA's origin.
    localAnchorA = vmath.vector3(0, 0, 0),

    The local anchor point relative to bodyB\'s origin.
    localAnchorB = vmath.vector3(0, 0, 0),

    Enable/disable the joint limit.
    enableLimit = false,

Enable/disable the joint motor.
    enableMotor = false,

    The desired motor speed in radians per second.
    motorSpeed = 0,

    The maximum motor torque, usually in N-m.
    maxMotorTorque = 0,

    The local translation axis in bodyA.
    localAxisA = vmath.vector3(0),

The lower translation limit, usually in meters.
    lowerTranslation = 0,

The upper translation limit, usually in meters.
    upperTranslation = 0,

Suspension stiffness. Typically in units N/m.
    stiffness = 0,

Suspension damping. Typically in units of N*s/m.
    damping = 0,
    --endregion
}
```

## Methods

* Box2dWheelJoint:[GetLocalAnchorA](#box2dwheeljointgetlocalanchora) ()
* Box2dWheelJoint:[GetLocalAnchorB](#box2dwheeljointgetlocalanchorb) ()
* Box2dWheelJoint:[GetLocalAxisA](#box2dwheeljointgetlocalaxisa) ()
* Box2dWheelJoint:[GetJointTranslation](#box2dwheeljointgetjointtranslation) ()
* Box2dWheelJoint:[GetJointLinearSpeed](#box2dwheeljointgetjointlinearspeed) ()
* Box2dWheelJoint:[GetJointAngle](#box2dwheeljointgetjointangle) ()
* Box2dWheelJoint:[GetJointAngularSpeed](#box2dwheeljointgetjointangularspeed) ()
* Box2dWheelJoint:[IsLimitEnabled](#box2dwheeljointislimitenabled) ()
* Box2dWheelJoint:[EnableLimit](#box2dwheeljointenablelimitflag) (flag)
* Box2dWheelJoint:[GetLowerLimit](#box2dwheeljointgetlowerlimit) ()
* Box2dWheelJoint:[GetUpperLimit](#box2dwheeljointgetupperlimit) ()
* Box2dWheelJoint:[SetLimits](#box2dwheeljointsetlimitslower-upper) (lower, upper)
* Box2dWheelJoint:[IsMotorEnabled](#box2dwheeljointismotorenabled) ()
* Box2dWheelJoint:[EnableMotor](#box2dwheeljointenablemotorflag) (flag)
* Box2dWheelJoint:[SetMotorSpeed](#box2dwheeljointsetmotorspeedspeed) (speed)
* Box2dWheelJoint:[GetMotorSpeed](#box2dwheeljointgetmotorspeed) ()
* Box2dWheelJoint:[SetMaxMotorTorque](#box2dwheeljointsetmaxmotortorquetorque) (torque)
* Box2dWheelJoint:[GetMaxMotorTorque](#box2dwheeljointgetmaxmotortorque) ()
* Box2dWheelJoint:[GetMotorTorque](#box2dwheeljointgetmotortorqueinvdt) (inv_dt)
* Box2dWheelJoint:[SetStiffness](#box2dwheeljointsetstiffnessstiffness) (stiffness)
* Box2dWheelJoint:[GetStiffness](#box2dwheeljointgetstiffness) ()
* Box2dWheelJoint:[SetDamping](#box2dwheeljointsetdampingdamping) (damping)
* Box2dWheelJoint:[GetDamping](#box2dwheeljointgetdamping) ()

### Box2dWheelJoint:GetLocalAnchorA()
The local anchor point relative to bodyA's origin.

**RETURN**
* (vector3)

### Box2dWheelJoint:GetLocalAnchorB()
The local anchor point relative to bodyB's origin.

**RETURN**
* (vector3)

### Box2dWheelJoint:GetLocalAxisA()
The local joint axis relative to bodyA.

**RETURN**
* (vector3)

### Box2dWheelJoint:GetJointTranslation()
Get the current joint translation, usually in meters.

**RETURN**
* (number)

### Box2dWheelJoint:GetJointLinearSpeed()
Get the current joint linear speed, usually in meters per second.

**RETURN**
* (number)

### Box2dWheelJoint:GetJointAngle()
Get the current joint angle in radians.

**RETURN**
* (number)

### Box2dWheelJoint:GetJointAngularSpeed()
Get the current joint angular speed in radians per second.

**RETURN**
* (number)

### Box2dWheelJoint:IsLimitEnabled()
Is the joint limit enabled?

**RETURN**
* (boolean)

### Box2dWheelJoint:EnableLimit(flag)
Enable/disable the joint translation limit.

**PARAMETERS**
* `flag` (boolean) -

### Box2dWheelJoint:GetLowerLimit()
Get the lower joint translation limit, usually in meters.

**RETURN**
* (number)

### Box2dWheelJoint:GetUpperLimit()
Get the upper joint translation limit, usually in meters.

**RETURN**
* (number)

### Box2dWheelJoint:SetLimits(lower, upper)
Set the joint translation limits, usually in meters.

**PARAMETERS**
* `lower` (number) -
* `upper` (number) -

### Box2dWheelJoint:IsMotorEnabled()
Is the joint motor enabled?

**RETURN**
* (boolean)

### Box2dWheelJoint:EnableMotor(flag)
Enable/disable the joint motor.

**PARAMETERS**
* `flag` (boolean) -

### Box2dWheelJoint:SetMotorSpeed(speed)
Set the motor speed, usually in radians per second.

**PARAMETERS**
* `speed` (number) -

### Box2dWheelJoint:GetMotorSpeed()
Get the motor speed, usually in radians per second.

**RETURN**
* (number)

### Box2dWheelJoint:SetMaxMotorTorque(torque)
Set/Get the maximum motor force, usually in N-m.

**PARAMETERS**
* `torque` (number) -

### Box2dWheelJoint:GetMaxMotorTorque()

**RETURN**
* (number)

### Box2dWheelJoint:GetMotorTorque(inv_dt)
Get the current motor torque given the inverse time step, usually in N-m.

**PARAMETERS**
* `inv_dt` (number) -

**RETURN**
* (number)

### Box2dWheelJoint:SetStiffness(stiffness)
Access spring stiffness

**PARAMETERS**
* `stiffness` (number) -

### Box2dWheelJoint:GetStiffness()

**RETURN**
* (number)

### Box2dWheelJoint:SetDamping(damping)
Access damping

**PARAMETERS**
* `damping` (number) -

### Box2dWheelJoint:GetDamping()

**RETURN**
* (number)
