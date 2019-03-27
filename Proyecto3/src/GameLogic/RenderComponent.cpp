#include "RenderComponent.h"
#include <OgreSceneNode.h>
#include <OgreEntity.h>

void RenderComponent::setUp() {
	if (isInited()) return;
	setInited();

	//get the ogrePair with the node and the correct entity built
	auto pair = getOgrePair(cfg_["shape"]);
	node = pair.first;
	entity = pair.second;

	//other properties
	node->setScale(nap_vector3(cfg_["scale"]).ogre());
	entity->setMaterialName(cfg_["material"]);
}

///////////////////////////////////////////////////////////////////////////////

OgrePair RenderComponent::getOgrePair(nap_json shape) {
	RenderSystemInterface* rsi = RenderSystemInterface::getSingleton();
	OgrePair pair;

	//switch the type to construct the correct shape
	string type = shape["type"];
	if (type == "BOX") {
		pair = rsi->createOgreEntity(shape["name"], shape["mesh"]);
	}

	return pair;
}

///////////////////////////////////////////////////////////////////////////////

void RenderComponent::late_update(GameObject * o, float time) {
	if (o->getUpToDate_rend()) return;

	node->setPosition(o->getPosition().ogre() * ogre_scale);
	node->setOrientation(o->getOrientation().ogre());
	o->setUpToDate_rend();
}