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
    void init(int width, int height, bool fullscreen, const char* name);
    void run();
    static void render();
    static void reshape(int width, int height);
    static void keyboard(unsigned char key, int x, int y);
    static void timer(int value);
    static void mouseMotion(int x, int y);
    static void mouseClick(int button, int state, int x, int y);
    static void setFramesPerSec(int newFramesPerSec);
    static void switchTurn();
    static void renderImGui();

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
    void cleanUp();
    void setupImGui();
    void cleanupImGui();
};