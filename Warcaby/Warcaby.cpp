#pragma comment(lib, "freeglut.lib")

#include <GL/glew.h>
#include <iostream>
#include "Engine.h"

int main(int argc, char** argv)
{
    Engine engine(argc, argv);
    engine.init(1920, 1080, true, "Warcaby 3D");
    engine.run();
    return 0;
}