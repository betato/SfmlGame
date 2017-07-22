#pragma once

#include <memory>
#include <stack>

#include "resmgr\TextureManager.h"

class Application
{
public:
	Application(int frameCap, int updateCap);

	void runLoop();

private:
	int updateRate;
	TextureManager texturemgr;
};
