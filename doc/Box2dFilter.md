# Box2dFilter
This holds contact filtering data.

_FIELDS_
* `categoryBits` (number) - The collision category bits. Normally you would just set one bit. The collision mask bits. This states the categories that this shape would accept for collision.
* `maskBits` (number) - Collision groups allow a certain group of objects to never collide (negative) or always collide (positive). Zero means no collision group. Non-zero group filtering always wins against the mask bits.
* `groupIndex` (number)
