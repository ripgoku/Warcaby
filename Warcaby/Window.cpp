#include "Window.h"

Window::Window() {
	width = 1280;
	height = 720;
	title = "Warcaby";
	fullscreen = true;
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow(title);
	if (fullscreen) {
		glutFullScreen();
	}
}