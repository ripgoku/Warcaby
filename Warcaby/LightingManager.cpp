#include "LightingManager.h"

LightingManager::LightingManager() {
    glEnable(GL_LIGHTING);
}

void LightingManager::addLightSource(const LightSource& light) {
    lightSources.push_back(light);
}

void LightingManager::applyLighting() {
    for (auto& light : lightSources) {
        if (!light.isEnabled()) continue;

        glm::vec4 lightPos = light.getPosition();
        glLightfv(light.getLightId(), GL_POSITION, glm::value_ptr(lightPos));

        glm::vec4 ambient = light.getAmbient();
        glm::vec4 diffuse = light.getDiffuse();
        glm::vec4 specular = light.getSpecular();

        glLightfv(light.getLightId(), GL_AMBIENT, glm::value_ptr(ambient));
        glLightfv(light.getLightId(), GL_DIFFUSE, glm::value_ptr(diffuse));
        glLightfv(light.getLightId(), GL_SPECULAR, glm::value_ptr(specular));
    }
}

