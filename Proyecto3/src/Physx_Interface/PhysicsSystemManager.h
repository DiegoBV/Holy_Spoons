//Nap_Time_Studios
#pragma once

#include <ctype.h>
#include <PxPhysicsAPI.h>
#define PVD 0 //visual debbuger
using namespace physx;

#include "EventReporter.h"

// Materials
#define BaseMat "BASE"
#include <map>

class PhysicsSystemManager
{
public:
	// Creates / returns the singleton instance
	static PhysicsSystemManager* getSingleton();
	static void shutdownSingleton();

	void stepPhysics(double t);
	void updateNodes();

	inline void setGravity(PxVec3 v) { gScene->setGravity(v); }

	//creating bodies
	PxShape * createShape(PxGeometry * geo, std::string mat);
	PxRigidDynamic* createDynamicBody(PxShape* shape, PxTransform const &trans);
	PxRigidStatic* createStaticBody(PxShape* shape, PxTransform const &trans);

private:
	// Foundation and Scene
	PxDefaultAllocator gAllocator;
	PxFoundation *gFoundation = NULL;
	PxPhysics *gPhysics = NULL;
	PxDefaultCpuDispatcher *gDispatcher = NULL;
	PxScene *gScene = NULL;

#if PVD //visual debugger
	PxPvd *gPvd				= NULL;
#endif

	// Collisions and events
	std::map<std::string, PxMaterial*> mats_; //different materials
	EventReporter eventReporter_;
	PxDefaultErrorCallback errorCallback_; //unused atm

	///////////////////////////////////////////////////////////////////////////

	//singleton pattern
	static PhysicsSystemManager* instance_;
	void setupInstance();
	void shutdownInstance();

	//private constructor
	PhysicsSystemManager() { setupInstance(); };
	~PhysicsSystemManager() { shutdownInstance(); };
};