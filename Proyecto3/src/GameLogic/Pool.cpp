#include "Pool.h"
#include "GameObject.h"
#include "GOFactory.h"

GameObject * nap_Pool::spawn()
{
	GameObject* tmp = new GameObject(original); //creates a new GO based on the original
	pool.push_back(tmp);
	return tmp;
}

nap_Pool::nap_Pool(std::string entity)
{
	//getting prefab
	original = GOFactory::GetGOPrefab(entity);
}

nap_Pool::~nap_Pool()
{
	for (int i = 0; i < pool.size(); i++) {
		if (pool[i] != nullptr) {
			delete(pool[i]);
			pool[i] = nullptr;
		}
	}
	if (original != nullptr) {
		delete original;
		original = nullptr;
	}
}

GameObject * nap_Pool::getItem()
{
	//Returns the 1� aviable item, if there's none it creates a new one
	int i = 0;
	while (i < pool.size())
	{
		if (!pool[i]->isActive()) {
			return pool[i];
		}
		i++;
	}
	
	return spawn();
}

void nap_Pool::init()
{
	//Creates a default value of items to populate the pool from the start
	for (int i = 0; i < defaultValue-1; i++) {
		spawn();
		pool.back()->setActive(false);
	}
}
