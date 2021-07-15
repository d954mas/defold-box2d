# PrismaticJoint
A prismatic joint. This joint provides one degree of freedom: translation
along an axis fixed in bodyA. Relative rotation is prevented. You can
use a joint limit to restrict the range of motion and a joint motor to
drive the motion or to model joint friction.

## Constructor

### Box2dWorld:CreateJoint(def)
Create a joint to constrain bodies together.
This may cause the connected bodies to cease colliding.
_Warning:_ This function is locked during callbacks.

**PARAMETERS**
* `def` [(Box2dJointDef)](../Joint.md) - Prismatic joint definition.

**RETURN**
* [(Box2dJoint)](../Joint.md)

#### JointDef
Prismatic joint definition. This requires defining a line of
motion using an axis and an anchor point. The definition uses local
anchor points and a local axis so that the initial configuration
can violate the constraint slightly. The joint translation is zero
when the local anchor points coincide in world space. Using local
anchors and a local axis helps when saving and loading a game.

```lua
local Box2dPrismaticJointDef = {
    Initialize the bodies, anchors, axis, and reference angle using the world
    anchor and unit world axis.
    void Initialize(b2Body* bodyA, b2Body* bodyB, const b2Vec2& anchor, const b2Vec2& axis);
    --region JointNeeded
    anchor = vmath.vector3(0), for Initialize
    axis = vmath.vector3(0), for Initialize
    --endregion

    --region JointOptional
    The local anchor point relative to bodyA's origin.
    localAnchorA = vmath.vector3(0, 0, 0),

    The local anchor point relative to bodyB's origin.
    localAnchorB = vmath.vector3(0, 0, 0),

    The constrained angle between the bodies: bodyB_angle - bodyA_angle.
    referenceAngle = 0,

    Enable/disable the joint limit.
    enableLimit = false,

    Enable/disable the joint motor.
    enableMotor = false,

    The desired motor speed in radians per second.
    motorSpeed = 0,

    The local translation unit axis in bodyA.
    localAxisA = vmath.vector3(1,0,0),

    The lower translation limit, usually in meters.
    lowerTranslation = 0,

    The upper translation limit, usually in meters.
    upperTranslation = 0,

    The maximum motor torque, usually in N-m.
    maxMotorForce = 0,
    --endregion
}
```

## Methods

* Box2dPrismaticJoint:[GetLocalAnchorA](#box2dprismaticjointgetlocalanchora) ()
* Box2dPrismaticJoint:[GetLocalAnchorB](#box2dprismaticjointgetlocalanchorb) ()
* Box2dPrismaticJoint:[GetLocalAxisA](#box2dprismaticjointgetlocalaxisa) ()
* Box2dPrismaticJoint:[GetReferenceAngle](#box2dprismaticjointgetreferenceangle) ()
* Box2dPrismaticJoint:[GetJointTranslation](#box2dprismaticjointgetjointtranslation) ()
* Box2dPrismaticJoint:[GetJointSpeed](#box2dprismaticjointgetjointspeed) ()
* Box2dPrismaticJoint:[IsLimitEnabled](#box2dprismaticjointislimitenabled) ()
* Box2dPrismaticJoint:[EnableLimit](#box2dprismaticjointenablelimitflag) (flag)
* Box2dPrismaticJoint:[GetLowerLimit](#box2dprismaticjointgetlowerlimit) ()
* Box2dPrismaticJoint:[GetUpperLimit](#box2dprismaticjointgetupperlimit) ()
* Box2dPrismaticJoint:[SetLimits](#box2dprismaticjointsetlimitslower-upper) (lower, upper)
* Box2dPrismaticJoint:[IsMotorEnabled](#box2dprismaticjointismotorenabled) ()
* Box2dPrismaticJoint:[EnableMotor](#box2dprismaticjointenablemotorflag) (flag)
* Box2dPrismaticJoint:[SetMotorSpeed](#box2dprismaticjointsetmotorspeedspeed) (speed)
* Box2dPrismaticJoint:[GetMotorSpeed](#box2dprismaticjointgetmotorspeed) ()
* Box2dPrismaticJoint:[SetMaxMotorForce](#box2dprismaticjointsetmaxmotorforceforce) (force)
* Box2dPrismaticJoint:[GetMaxMotorForce](#box2dprismaticjointgetmaxmotorforce) ()
* Box2dPrismaticJoint:[GetMotorForce](#box2dprismaticjointgetmotorforceinvdt) (inv_dt)

---
### Box2dPrismaticJoint:GetLocalAnchorA()
The local anchor point relative to bodyA's origin.

**RETURN**
* (vector3)

---
### Box2dPrismaticJoint:GetLocalAnchorB()
The local anchor point relative to bodyB's origin.

**RETURN**
* (vector3)

---
### Box2dPrismaticJoint:GetLocalAxisA()
The local joint axis relative to bodyA.

**RETURN**
* (vector3)

---
### Box2dPrismaticJoint:GetReferenceAngle()
Get the reference angle.

**RETURN**
* (number)

---
### Box2dPrismaticJoint:GetJointTranslation()
Get the current joint translation, usually in meters.

**RETURN**
* (number)

---
### Box2dPrismaticJoint:GetJointSpeed()
Get the current joint translation speed, usually in meters per second.

**RETURN**
* (number)

---
### Box2dPrismaticJoint:IsLimitEnabled()
Is the joint limit enabled?

**RETURN**
* (boolean)

---
### Box2dPrismaticJoint:EnableLimit(flag)
Enable/disable the joint limit.

**PARAMETERS**
* `flag` (boolean) -

---
### Box2dPrismaticJoint:GetLowerLimit()
Get the lower joint limit, usually in meters.

**RETURN**
* (number)

---
### Box2dPrismaticJoint:GetUpperLimit()
Get the upper joint limit, usually in meters.

**RETURN**
* (number)

---
### Box2dPrismaticJoint:SetLimits(lower, upper)
Set the joint limits, usually in meters.

**PARAMETERS**
* `lower` (number) -
* `upper` (number) -

---
### Box2dPrismaticJoint:IsMotorEnabled()
Is the joint motor enabled?

**RETURN**
* (boolean)

---
### Box2dPrismaticJoint:EnableMotor(flag)
Enable/disable the joint motor.

**PARAMETERS**
* `flag` (boolean) -

---
### Box2dPrismaticJoint:SetMotorSpeed(speed)
Set the motor speed, usually in meters per second.

**PARAMETERS**
* `speed` (number) -

---
### Box2dPrismaticJoint:GetMotorSpeed()
Get the motor speed, usually in meters per second.

**RETURN**
* (number)

---
### Box2dPrismaticJoint:SetMaxMotorForce(force)
Set the maximum motor force, usually in N.

**PARAMETERS**
* `force` (number) -

---
### Box2dPrismaticJoint:GetMaxMotorForce()

**RETURN**
* (number)

---
### Box2dPrismaticJoint:GetMotorForce(inv_dt)
Get the current motor force given the inverse time step, usually in N.

**PARAMETERS**
* `inv_dt` (number) -

**RETURN**
* (number)
