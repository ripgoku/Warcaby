#pragma once

#include <GL/glew.h>
#include <string>
#include <iostream>

class Texture {
public:
    Texture();
    ~Texture();
    void loadTexture(const std::string& path);

private:
    unsigned int ID;
};