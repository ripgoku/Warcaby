#pragma once
#include <GL/glew.h>
#include "Window.h"
#include "Camera.h"

class Mouse
{
private:
	static bool isCursorCaptured;
	static Camera camera;

public:
	Mouse();
	
	static void motion(int x, int y);
	
	void capture(bool capture);
};

