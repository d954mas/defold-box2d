# Box2D
The extension creates a global module, `box2d`.

## Constants:
```lua
box2d.b2Shape = {
    e_circle = 0,
    e_edge = 1,
    e_polygon = 2,
    e_chain = 3,
}

box2d.b2BodyType = {
    b2_staticBody = 0,
    b2_kinematicBody = 1,
    b2_dynamicBody = 2,
}

box2d.b2JointType = {
    e_unknownJoint = 0, e_revoluteJoint = 1,
    e_prismaticJoint = 2, e_distanceJoint = 3,
    e_pulleyJoint = 4, e_mouseJoint = 5,
    e_gearJoint = 6, e_wheelJoint = 7,
    e_weldJoint = 8, e_frictionJoint = 9,
    e_ropeJoint = 10, e_motorJoint = 11,
}

box2d.b2Draw = {
    e_shapeBit = 1, e_jointBit = 2,
    e_aabbBit = 4, e_pairBit = 8,
    e_centerOfMassBit = 16
}
```

## Functions

* box2d.[NewWorld](#box2dnewworldgravity) (gravity)
* box2d.[NewDebugDraw](#box2dnewdebugdrawdata) (data)
* box2d.[b2LinearStiffness](#box2db2linearstiffnessfrequencyhertz-dampingratio-bodya-bodyb) (frequencyHertz, dampingRatio, bodyA, bodyB)
* box2d.[b2AngularStiffness](#box2db2angularstiffnessfrequencyhertz-dampingratio-bodya-bodyb) (frequencyHertz, dampingRatio, bodyA, bodyB)

#### box2d.NewWorld(gravity)

_ARGUMENTS_
* __gravity__ <kbd>vector3|nil</kbd> - The world gravity vector.

_RETURNS_
* [`Box2dWorld`](doc/World.md)

#### box2d.NewDebugDraw(data)

_ARGUMENTS_
* __data__ <kbd>table</kbd> -

_RETURNS_
* [`Box2dDebugDraw`](doc/DebugDraw.md)

#### box2d.b2LinearStiffness(frequencyHertz, dampingRatio, bodyA, bodyB)
Utility to compute linear stiffness values from frequency and damping ratio

_ARGUMENTS_
* __frequencyHertz__ <kbd>number</kbd> -
* __dampingRatio__ <kbd>number</kbd> -
* __bodyA__ [`Box2dBody`](doc/Body.md) -
* __bodyB__ [`Box2dBody`](doc/Body.md) -

_RETURNS_
* <kbd>number</kbd> - Stiffness
* <kbd>number</kbd> - Damping

#### box2d.b2AngularStiffness(frequencyHertz, dampingRatio, bodyA, bodyB)
Utility to compute rotational stiffness values from frequency and damping ratio

_ARGUMENTS_
* __frequencyHertz__ <kbd>number</kbd> -
* __dampingRatio__ <kbd>number</kbd> -
* __bodyA__ [`Box2dBody`](doc/Body.md) -
* __bodyB__ [`Box2dBody`](doc/Body.md) -

_RETURNS_
* <kbd>number</kbd> - Stiffness
* <kbd>number</kbd> - Damping
