
# Box2D for Defold

Box2D lua bindings for the Defold Game Engine.

I tried to keep the lua api the same as the c++ api when possible.

If you like the extension you can support me on patreon.
It will help me make more items for defold.

[![](https://c5.patreon.com/external/logo/become_a_patron_button.png)](https://www.patreon.com/d954mas)

Try the demo: https://d954mas.github.io/defold-box2d/

<img src="https://github.com/d954mas/defold-box2d/blob/master/files/screenshot.png">

# Table of Contents
- [Box2D for Defold](#box2d-for-defold)
  * [Installation](#installation)
  * [Box2D](#box2d)
  * [Limitations](#limitations)
  * API:
    + [Extension](doc/base.md)
    + [World](doc/World.md)
    + [DebugDraw](doc/DebugDraw.md)
    + [Contact](doc/Contact.md)
    + [Shape](doc/Shape.md)
    + [FixtureDef](doc/FixtureDef.md)
    + [Fixture](doc/Fixture.md)
    + [BodyDef](doc/BodyDef.md)
    + [Body](doc/Body.md)
    + [Joint](doc/Joint.md)
      - [RevoluteJoint](doc/joints/RevoluteJoint.md)
      - [PrismaticJoint](doc/joints/PrismaticJoint.md)
      - [DistanceJoint](doc/joints/DistanceJoint.md)
      - [PulleyJoint](doc/joints/PulleyJoint.md)
      - [MouseJoint](doc/joints/MouseJoint.md)
      - [GearJoint](doc/joints/GearJoint.md)
      - [WheelJoint](doc/joints/WheelJoint.md)
      - [WeldJoint](doc/joints/WeldJoint.md)
      - [FrictionJoint](doc/joints/FrictionJoint.md)
      - [MotorJoint](doc/joints/MotorJoint.md)
    + [Box2dManifold](doc/Box2dManifold.md)
    + [Box2dWorldManifold](doc/Box2dWorldManifold.md)
    + [Box2dContactImpulse](doc/Box2dContactImpulse.md)
    + [Box2dFilter](doc/Box2dFilter.md)
    + [Box2dProfile](doc/Box2dProfile.md)
    + [Box2dMassData](doc/Box2dMassData.md)

## Installation

__1)__ Add defold-box2d in your own project as a Defold library dependency. Open your game.project file and in the dependencies field under project add:
https://github.com/d954mas/defold-box2d/archive/refs/tags/1.0.0.zip

__2)__ Remove Defold engine box2d. If it's not removed there will be a conflict between this box2d and engine box2d.
Open your game.project file and in the App Manifest field under Native Extension add manifest.

1. Use /box2d/manifest.appmanifest, OR
2. You can generate a manifest yourself https://britzl.github.io/manifestation/

## API
Supports emmylua. box2d_header.lua

## Box2D
If you need info about how Box2D works, read its documentation.
https://box2d.org/documentation/

Box2d version: 2.4.1

## Limitations

__1)__ No binding for b2Vec2. Use defold vector(vmath.vector3)

__2)__ No binding for some b2World functions.

	void SetContactFilter(b2ContactFilter* filter);
	const b2ContactManager& GetContactManager() const;

__3)__ No binding for some b2Joint functions.

	virtual void Draw(b2Draw* draw) const;

