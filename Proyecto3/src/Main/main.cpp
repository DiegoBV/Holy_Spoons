#include <iostream>
#include <OgreInterface.h>

int main(int argc, char *argv[])
{
	OgreInterface* renderInterface = OgreInterface::getSingleton();
	renderInterface->shutdown();
	return 0;
}
