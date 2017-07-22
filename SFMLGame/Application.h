#pragma once

#include <memory>
#include <stack>

#include "resmgr\ResourceManager.h"

class Application
{
public:
	Application(int frameCap, int updateCap);

	void runLoop();

private:
	int updateRate;
	ResourceManager resourceManager;
};
