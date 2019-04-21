//Nap_Time_Studios
#ifndef WEAPON_H_
#define WEAPON_H_

#include <string>
using namespace std;

//fowarding
class nap_transform;
class nap_Pool;

#include "Activable.h"
//base weapon class
class Weapon : public Activable
{
public:
	Weapon(string prefab, float vel, double shootSpeed);
	virtual ~Weapon();

	virtual void mouseUpdate(bool down);
	virtual void shootUpdate(nap_transform* owner_trans,
		float relY, float relZ, double time);
	virtual void shoot(nap_transform* owner_trans,
		float relY, float relZ);
	virtual void swapDelay();

protected:
	bool down_ = false;
	nap_Pool* pool_ = nullptr;
	float vel_ = 0;
	double shootSpeed_ = 0.2, timer = 0;
};

//automatic shooting
class BaseSpoon : public Weapon
{
public:
	BaseSpoon(string prefab, float vel, double shootSpeed);
	virtual ~BaseSpoon();
	virtual void shoot(nap_transform* owner_trans,
		float relY, float relZ);
};

//powerfull semi-automatic shot
class PowerSpoon : public Weapon
{
public:
	PowerSpoon(string prefab, float vel, double shootSpeed);
	virtual ~PowerSpoon();
	virtual void shoot(nap_transform* owner_trans,
		float relY, float relZ);
};

//powerfull automatic shooting (multiple bullets with spread)
class ShotSpoon : public Weapon
{
public:
	ShotSpoon(string prefab, float vel, double shootSpeed);
	virtual ~ShotSpoon();
	virtual void shoot(nap_transform* owner_trans,
		float relY, float relZ);
};

#endif /* WEAPON_H_ */