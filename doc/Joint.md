# Joint
The base joint class. Joints are used to constraint two bodies together in
various fashions. Some joints also feature limits and motors.

This is a constraint used to hold two or more bodies together. Box2D supports several joint types: revolute, prismatic, distance, and more. Some joints may have limits and motors.

Box2dJointDef is based for other joint def.
Joint have needed and optional fields.
If jointDef have Initialize method for example b2PrismaticJointDef, it will be called when create joint def.

## Constructor

#### Box2dWorld:CreateJoint(def)
Create a joint to constrain bodies together.
This may cause the connected bodies to cease colliding.
_Warning:_ This function is locked during callbacks.

_ARGUMENTS_
* __def__ [`Box2dJointDef`](Joint.md) -

#### JointDef
```lua
local Box2dJointDef = {
    --region JointNeeded
    The joint type
    type = box2d.b2JointType.e_revoluteJoint,

    @type Box2dBody
    bodyA = nil,

    @type Box2dBody
    bodyB = nil,
    --endregion

    --region JointOptional
    -- Use this to attach application specific data to your joints.
    @type table|nil
    userData = nil,

    -- Set this flag to true if the attached bodies should collide.
    collideConnected = false,
    --endregion

}
```

_RETURNS_
* [`Box2dJoint`](Joint.md)

## Methods

* Box2dJoint:[GetType](#box2djointgettype) ()
* Box2dJoint:[GetBodyA](#box2djointgetbodya) ()
* Box2dJoint:[GetBodyA](#box2djointgetbodya) ()
* Box2dJoint:[GetAnchorA](#box2djointgetanchora) ()
* Box2dJoint:[GetAnchorB](#box2djointgetanchorb) ()
* Box2dJoint:[GetReactionForce](#box2djointgetreactionforceinvdt) (inv_dt)
* Box2dJoint:[GetReactionTorque](#box2djointgetreactiontorqueinvdt) (inv_dt)
* Box2dJoint:[GetNext](#box2djointgetnext) ()
* Box2dJoint:[GetUserData](#box2djointgetuserdata) ()
* Box2dJoint:[SetUserData](#box2djointsetuserdatauserdata) (userdata)
* Box2dJoint:[IsEnabled](#box2djointisenabled) ()
* Box2dJoint:[GetCollideConnected](#box2djointgetcollideconnected) ()
* Box2dJoint:[Dump](#box2djointdump) ()
* Box2dJoint:[ShiftOrigin](#box2djointshiftoriginneworigin) (newOrigin)

#### Box2dJoint:GetType()
Get the type of the concrete joint.

_RETURNS_
* <kbd>number</kbd> - Box2d.b2JointType

#### Box2dJoint:GetBodyA()
Get the first body attached to this joint.

_RETURNS_
* [`Box2dBody`](Body.md) - BodyA

#### Box2dJoint:GetBodyA()
Get the second body attached to this joint.

_RETURNS_
* [`Box2dBody`](Body.md) - BodyB

#### Box2dJoint:GetAnchorA()
Get the anchor point on bodyA in world coordinates.

_RETURNS_
* <kbd>vector3</kbd>

#### Box2dJoint:GetAnchorB()
Get the anchor point on bodyB in world coordinates.

_RETURNS_
* <kbd>vector3</kbd>

#### Box2dJoint:GetReactionForce(inv_dt)
Get the reaction force on bodyB at the joint anchor in Newtons.

_ARGUMENTS_
* __inv_dt__ <kbd>number</kbd> -

_RETURNS_
* <kbd>vector3</kbd>

#### Box2dJoint:GetReactionTorque(inv_dt)
Get the reaction torque on bodyB in N*m.

_ARGUMENTS_
* __inv_dt__ <kbd>number</kbd> -

_RETURNS_
* <kbd>vector3</kbd>

#### Box2dJoint:GetNext()
Get the next joint the world joint list.

_RETURNS_
* [`Box2dJoint`](Joint.md)|<kbd>nil</kbd>

#### Box2dJoint:GetUserData()
Get the user data.
Use this to store your application specific data.

_RETURNS_
* <kbd>table|nil</kbd>

#### Box2dJoint:SetUserData(userdata)
Set the user data.
Use this to store your application specific data.

_ARGUMENTS_
* __userdata__ <kbd>table|nil</kbd> -

#### Box2dJoint:IsEnabled()
Short-cut function to determine if either body is enabled.

_RETURNS_
* <kbd>boolean</kbd>

#### Box2dJoint:GetCollideConnected()
Get collide connected.
Note: modifying the collide connect flag won't work correctly because
the flag is only checked when fixture AABBs begin to overlap.

_RETURNS_
* <kbd>boolean</kbd>

#### Box2dJoint:Dump()
Dump this joint to the log file.

#### Box2dJoint:ShiftOrigin(newOrigin)
Shift the origin for any points stored in world coordinates.

_ARGUMENTS_
* __newOrigin__ <kbd>vector3</kbd> -
