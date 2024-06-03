#include "Engine.h"

int Engine::windowWidth;
int Engine::windowHeight;
int Engine::framesPerSecond;
bool Engine::isCursorCaptured;
Camera Engine::camera;
bool Engine::isFullscreen;
LightSource light(GL_LIGHT0);
LightSource light2(GL_LIGHT1);
bool Engine::rotateCamera;
Turn Engine::playerTurn;
Board Engine::gameBoard;

Engine::Engine(int argc, char** argv) {
    glutInit(&argc, argv);
    isFullscreen = true;
    windowWidth = 1920;
    windowHeight = 1080;
    windowTitle = "OpenGL Engine";
    framesPerSecond = 60;
    rotateCamera = false;
    playerTurn = PLAYER_1;
}

Engine::~Engine() {
}

void Engine::init(int width, int height, bool fullscreen, const char* name) {
    windowWidth = width;
    windowHeight = height;
    isFullscreen = fullscreen;
    windowTitle = name;
    isCursorCaptured = false;

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow(windowTitle);
    if (isFullscreen) {
        glutFullScreen();
    }

    GLenum glewStatus = glewInit();
    if (glewStatus != GLEW_OK) {
        fprintf(stderr, "glewInit error: %s\n", glewGetErrorString(glewStatus));
        exit(EXIT_FAILURE);
    }


    setupImGui();
    glutReshapeFunc(Engine::reshape);
    glutDisplayFunc(Engine::render);
    glutKeyboardFunc(Engine::keyboard);
    glutMouseFunc(Engine::mouseClick);
    glutPassiveMotionFunc(Engine::mouseMotion);
    glutMotionFunc(Engine::mouseMotion);
    glutMouseWheelFunc(ImGui_ImplGLUT_MouseWheelFunc);
    glutTimerFunc(1000 / framesPerSecond, Engine::timer, 0);

    initGL();
    gameBoard.initializeBoard();
}

void Engine::initGL() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.529f, 0.808f, 0.922f, 1.0f);
}

void Engine::setupViewport() {
    glViewport(0, 0, windowWidth, windowHeight);

    glm::mat4 projection = glm::perspective(glm::radians(60.0f), static_cast<float>(windowWidth) / static_cast<float>(windowHeight), 0.1f, 100.0f);
    glm::mat4 view = camera.getViewMatrix();

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(projection));
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(glm::value_ptr(view));
}

void Engine::run() {
    glutMainLoop();
}

void Engine::update() {

    if(gameBoard.getSelectedPiece() != nullptr && gameBoard.getSelectedPiece()->getAnimation()) {
        glm::vec3 way = glm::vec3(0, 0, 0);
        float x = gameBoard.getSelectedPiece()->getPosition().x;
        float dx = gameBoard.getSelectedPiece()->getDestPosition().x;
        float z = gameBoard.getSelectedPiece()->getPosition().y;
        float dz = gameBoard.getSelectedPiece()->getDestPosition().y;
        if(!(gameBoard.getSelectedPiece()->getXyzPosition().x + 3.4f < gameBoard.getSelectedPiece()->getDestPosition().x && gameBoard.getSelectedPiece()->getDestPosition().x < gameBoard.getSelectedPiece()->getXyzPosition().x + 3.6f))
        {
            if (gameBoard.getSelectedPiece()->getXyzPosition().y < 0.4f)
                gameBoard.getSelectedPiece()->setXyzPosition(glm::vec3(gameBoard.getSelectedPiece()->getXyzPosition().x, gameBoard.getSelectedPiece()->getXyzPosition().y + 0.1f, gameBoard.getSelectedPiece()->getXyzPosition().z));

            float diffX = dx - x;
            float diffZ = dz - z;

            glm::vec3 direction = glm::normalize(glm::vec3(diffX, 0.0f, diffZ));

            way = gameBoard.getSelectedPiece()->getXyzPosition() + direction * 0.1f;
            gameBoard.getSelectedPiece()->setXyzPosition(way);
        }

        if (gameBoard.getSelectedPiece()->getXyzPosition().x + 3.4f < gameBoard.getSelectedPiece()->getDestPosition().x && gameBoard.getSelectedPiece()->getDestPosition().x < gameBoard.getSelectedPiece()->getXyzPosition().x + 3.6f) {
            if (gameBoard.getSelectedPiece()->getXyzPosition().y > 0.0f)
            {
                gameBoard.getSelectedPiece()->setXyzPosition(glm::vec3(gameBoard.getSelectedPiece()->getXyzPosition().x, gameBoard.getSelectedPiece()->getXyzPosition().y - 0.1f, gameBoard.getSelectedPiece()->getXyzPosition().z));
                return;
            }
            gameBoard.getSelectedPiece()->setXyzPosition(glm::vec3(dx - 3.5, 0.0f, dz - 3.5));
            gameBoard.movePiece(gameBoard.getSelectedPiece()->getPosition().x, gameBoard.getSelectedPiece()->getPosition().y, gameBoard.getSelectedPiece()->getDestPosition().x, gameBoard.getSelectedPiece()->getDestPosition().y, playerTurn);
            gameBoard.getSelectedPiece()->setAnimation(false);
            gameBoard.deselectAllPieces();
            if(!gameBoard.checkGameOver())
                switchTurn();
        }
    }

    if (!camera.getFreeMode() && rotateCamera) {
        camera.rotate(0.0f, 10.0f);

        if ((camera.getOrbitAngle() == 275.0f && playerTurn == PLAYER_2) || (camera.getOrbitAngle() == 95.0f && playerTurn == PLAYER_1))
            rotateCamera = false;
    }
}

void Engine::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    setupViewport();

    LightingManager lightingManager;

    light.setPosition(glm::vec4(10, 7, 10, 0.0f));
    light.setAmbient(glm::vec4(0.3f, 0.3f, 0.3f, 1.0f));
    light.setDiffuse(glm::vec4(0.7f, 0.7f, 0.7f, 1.0f));
    light.setSpecular(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    lightingManager.addLightSource(light);
    light2.setPosition(glm::vec4(-10, 7, -10, 0.0f));
    light2.setAmbient(glm::vec4(0.3f, 0.3f, 0.3f, 1.0f));
    light2.setDiffuse(glm::vec4(0.7f, 0.7f, 0.7f, 1.0f));
    light2.setSpecular(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    lightingManager.addLightSource(light2);
    lightingManager.applyLighting();
    light.enable();
    light2.enable();
    
    gameBoard.renderBoard();
    renderImGui();

    setupViewport();

    glutSwapBuffers();
}

void Engine::reshape(int width, int height) {
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2((float)width, (float)height);
    windowWidth = width;
    windowHeight = height;
    setupViewport();
}

void Engine::keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'a':
    case 'A':
        camera.move(camera.getRightVector() * -1.0f);
        break;
    case 'd':
    case 'D':
        camera.move(camera.getRightVector());
        break;
    case 's':
    case 'S':
        camera.move(camera.getFrontVector() * -1.0f);
        break;
    case 'w':
    case 'W':
        camera.move(camera.getFrontVector());
        break;
    case '\t':
        if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
            isCursorCaptured = !isCursorCaptured;
            bool freeModeEnable = camera.getFreeMode();
            camera.setFreeMode(!freeModeEnable);
            if (isCursorCaptured && camera.getFreeMode()) {
                glutSetCursor(GLUT_CURSOR_NONE);
                glutWarpPointer(windowWidth / 2, windowHeight / 2);
            }
            else {
                glutSetCursor(GLUT_CURSOR_INHERIT);
            }
        }
        break;
    case 'f':
    case 'F':
        if (!isFullscreen) {
            glutFullScreen();
            isFullscreen = true;
        }
        else {
            glutPositionWindow(0, 0);
            reshape(windowWidth, windowHeight);
            isFullscreen = false;
        }
    }
}

void Engine::mouseMotion(int x, int y) {
    ImGuiIO& io = ImGui::GetIO();
    io.AddMousePosEvent((float)x, (float)y);

    if (isCursorCaptured) {
        static int lastX = windowWidth / 2;
        static int lastY = windowHeight / 2;
        float xOffset = x - lastX;
        float yOffset = lastY - y;

        camera.processMouseMovement(xOffset, yOffset, 1);

        glutWarpPointer(windowWidth / 2, windowHeight / 2);

        lastX = windowWidth / 2;
        lastY = windowHeight / 2;
    }
}

void Engine::mouseClick(int button, int state, int x, int y) {
    ImGuiIO& io = ImGui::GetIO();
    io.AddMousePosEvent((float)x, (float)y);
    int buttonn = -1;
    if (button == GLUT_LEFT_BUTTON) buttonn = 0;
    if (button == GLUT_RIGHT_BUTTON) buttonn = 1;
    if (button == GLUT_MIDDLE_BUTTON) buttonn = 2;
    if (buttonn != -1 && (state == GLUT_DOWN || state == GLUT_UP))
        io.AddMouseButtonEvent(buttonn, state == GLUT_DOWN);

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        GLint viewport[4];
        GLdouble modelview[16];
        GLdouble projection[16];
        GLfloat winX, winY, winZ;
        GLdouble posX, posY, posZ;

        glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
        glGetDoublev(GL_PROJECTION_MATRIX, projection);
        glGetIntegerv(GL_VIEWPORT, viewport);

        winX = static_cast<float>(x);
        winY = static_cast<float>(viewport[3]) - static_cast<float>(y);
        glReadPixels(x, static_cast<int>(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

        gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

        int boardX = static_cast<int>(posX + 4);
        int boardY = static_cast<int>(posZ + 4);

        if (gameBoard.getPieceAt(boardX, boardY) != nullptr) {
            gameBoard.selectPiece(boardX, boardY, playerTurn);
        }
        else if (gameBoard.getSelectedPiece() != nullptr) {
            int startX = gameBoard.getSelectedPiece()->getPosition().x;
            int startY = gameBoard.getSelectedPiece()->getPosition().y;
            if (gameBoard.isInBounds(startX, startY) && gameBoard.isInBounds(boardX, boardY)) {
                if (gameBoard.isValidMove(startX, startY, boardX, boardY)) {
                    Piece* piece = gameBoard.getPieceAt(startX, startY);
                    if (piece != nullptr && ((playerTurn == PLAYER_1 && piece->getColor() == PieceColor::WHITE) ||
                        (playerTurn == PLAYER_2 && piece->getColor() == PieceColor::BLACK))) {
                        piece->setDestPosition(glm::vec2(boardX, boardY));
                        piece->setAnimation(true);
                    }
                }
            }
        }

        glutPostRedisplay();
    }
}


void Engine::switchTurn() {
    rotateCamera = true;
    if (playerTurn == PLAYER_1)
        playerTurn = PLAYER_2;
    else
        playerTurn = PLAYER_1;
}

void Engine::setFramesPerSec(int newFramesPerSec) {
    framesPerSecond = newFramesPerSec;
}

void Engine::cleanUp() {
    cleanupImGui();
    glutDestroyWindow(glutGetWindow());
}

void Engine::timer(int value) {
    update();
    glutPostRedisplay();
    glutTimerFunc(1000 / framesPerSecond, Engine::timer, 0);
}

void Engine::setupImGui() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGLUT_Init();
    ImGui_ImplOpenGL3_Init("#version 130");
}

void Engine::cleanupImGui() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGLUT_Shutdown();
    ImGui::DestroyContext();
}

void Engine::renderImGui() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGLUT_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Game Control Panel");

    const char* activePlayer = (playerTurn == PLAYER_1) ? "White" : "Black";
    ImGui::Text("Active Player: %s", activePlayer);

    if (ImGui::Button("Reset Game")) {
        resetGame();
    }

    if (gameBoard.checkGameOver()) {
        ImGui::Text("Game Over!");
        ImGui::Text("Winner: %s", activePlayer);
    }

    if (ImGui::Button("Exit")) {
        exit(EXIT_SUCCESS);
    }

    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Engine::resetGame() {
    gameBoard.clearBoard();
    gameBoard.initializeBoard();
    if (playerTurn == PLAYER_2)
        switchTurn();
}