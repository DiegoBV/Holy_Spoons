//Nap_Time_Studios
#ifndef BULLETHIT_H_
#define BULLETHIT_H_

#include "CollisionListener.h"

#include "Component.h"
class BulletHit : public Component, public CollisionListener
{
public:
	inline BulletHit(){}
	inline BulletHit(nap_json const & cfg, GameObject* owner) : Component(cfg, owner), CollisionListener(owner) {};
	inline virtual ~BulletHit() {};
	virtual void setUp();

	virtual void onCollision(ID* other);
};

#endif /* BULLETHIT_H_ */