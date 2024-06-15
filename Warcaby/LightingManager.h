#pragma once

#include <GL/glew.h>
#include "LightSource.h"
#include <vector>

class LightingManager {
public:
    LightingManager();
    void addLightSource(const LightSource& light);
    void applyLighting();

private:
    std::vector<LightSource> lightSources;
};
