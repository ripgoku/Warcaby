#pragma comment(lib, "freeglut.lib")

#include <GL/glew.h>
#include <iostream>
#include "Engine.h"

int main(int argc, char** argv)
{
    Engine engine(argc, argv);
    engine.init();
    engine.run();
    return 0;
}