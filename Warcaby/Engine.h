#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <windows.h>
#include "imgui.h"
#include "imgui_impl_glut.h"
#include "imgui_impl_opengl3.h"
#include "Camera.h"
#include "LightingManager.h"
#include "LightSource.h"
#include "Board.h"
#include "Texture.h"

class Engine {
public:
    Engine(int argc, char** argv);
    ~Engine();
    void init();
    void run();

private:
    static Camera camera;
    static int windowWidth;
    static int windowHeight;
    static int framesPerSecond;
    static bool isFullscreen;
    const char* windowTitle;
    static bool isCursorCaptured;
    static bool rotateCamera;
    static Turn playerTurn;
    static Board gameBoard;

    void initGL();
    static void setupViewport();
    static void update();
    static void resetGame();
    static void renderImGui();
    static void switchTurn();
    static void setFramesPerSec(int newFramesPerSec);
    static void mouseClick(int button, int state, int x, int y);
    static void mouseMotion(int x, int y);
    static void render();
    static void reshape(int width, int height);
    static void keyboard(unsigned char key, int x, int y);
    static void timer(int value);
    void cleanUp();
    void setupImGui();
    void cleanupImGui();
};