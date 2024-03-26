#include "Engine.h"

Camera Engine::camera;

Engine::Engine(int argc, char** argv) {
    glutInit(&argc, argv);
}

void Engine::init() {
    Window window;

    GLenum glewStatus = glewInit();
    if (glewStatus != GLEW_OK) {
        fprintf(stderr, "glewInit error: %s\n", glewGetErrorString(glewStatus));
        exit(EXIT_FAILURE);
    }

    //glutDisplayFunc(Engine::render);
    //glutReshapeFunc(Engine::reshape);
    //glutKeyboardFunc(Engine::keyboard);
    //glutKeyboardUpFunc(Engine::keyboardUp);
    //glutMouseFunc(Engine::mouseClick);
    glutPassiveMotionFunc(Mouse::motion);
    //glutTimerFunc(1000 / framesPerSecond, Engine::timer, 0);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Engine::run() {
    //isRunning = true;

    glutMainLoop();
}