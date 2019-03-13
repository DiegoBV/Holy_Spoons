#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <vector>
#include <SDL_events.h> //events

#include "Activable.h"
class Component;

using namespace std;

// this class accepts components (empty container waiting for functionality)
class GameObject : public Activable
{
private:
	std::vector<Component*> Components_; // component vector

public:
	GameObject();

	virtual bool handleEvents(const SDL_Event evt);
	virtual void update(float time);

	// it adds a component
	virtual void addComponent(Component* component);

	// it deletes a component
	virtual void delComponent(Component* component);

	virtual ~GameObject();
};

#endif /* GAMEOBJECT_H_ */

