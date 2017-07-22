#pragma once

#include <memory>
#include <stack>

class Application
{
public:
	Application(int frameCap, int updateCap);

	void runLoop();

private:
	int updateRate;
};