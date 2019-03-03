#ifndef RENDERSYSTEMINTERFACE_H_
#define RENDERSYSTEMINTERFACE_H_

#include <OgreBuildSettings.h>
#include <OgreRoot.h>

using namespace Ogre;
class RenderSystemInterface
{
private:
	SceneManager * mScnMgr = nullptr;
public:
	RenderSystemInterface() {};
	RenderSystemInterface(SceneManager * mScnMgr): mScnMgr(mScnMgr){};
	virtual ~RenderSystemInterface() {};

	//Resto de interfaz, a�adir material, a�adir como nodo, shaders (?), a�adir como hijo, buscar nodo, camara, luces, viewport...
};

#endif /*RENDERSYSTEMINTERFACE_H_*/

