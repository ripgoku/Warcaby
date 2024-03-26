#pragma once
#include <GL/glew.h>
#include <stdio.h>
#include "Window.h"
#include "Mouse.h"
#include "Camera.h"

class Engine
{
private:
	static Camera camera;
public:
	Engine(int argc, char** argv);
	void init();
	void run();
};

