#ifndef LIGHTING_MANAGER_H
#define LIGHTING_MANAGER_H

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

#endif // LIGHTING_MANAGER_H
