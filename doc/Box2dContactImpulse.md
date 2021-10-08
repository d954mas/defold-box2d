# Box2dContactImpulse
Contact impulses for reporting. Impulses are used instead of forces because
sub-step forces may approach infinity for rigid body collisions. These
match up one-to-one with the contact points in b2Manifold.

_FIELDS_
* `normalImpulses` (number[]) 
* `tangentImpulses` (number[]) 
* `count` (number)
