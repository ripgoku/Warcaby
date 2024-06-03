#pragma once

#include <GL/glew.h>
#include <string>
#include <iostream>

class Texture {
public:
    Texture();
    ~Texture();
    void bind(unsigned int slot = 0) const;
    void loadTexture(const std::string& path);

private:
    unsigned int ID;
};