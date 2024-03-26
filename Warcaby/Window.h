#pragma once
#include <GL/glew.h>
#include <GL/freeglut_std.h>

class Window
{
private:
public:
	static int height;
	static int width;
	const char* title;
	static bool fullscreen;

	Window();
};

