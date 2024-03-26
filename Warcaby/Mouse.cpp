#include "Mouse.h"

Mouse::Mouse(Camera& camera) {
    isCursorCaptured = true;
    camera = ;
}

void Mouse::capture(bool capture)
{
	this->isCursorCaptured = capture;
}

void Mouse::motion(int x, int y) {
    static int lastX = Window::width / 2;
    static int lastY = Window::height / 2;

    if (isCursorCaptured) {

        float xOffset = x - (float)lastX;
        float yOffset = (float)lastY - y;

        camera.processMouseMovement(xOffset, yOffset, 1);

        glutWarpPointer(Window::width / 2, Window::height / 2);

        lastX = Window::width / 2;
        lastY = Window::height / 2;
    }
}