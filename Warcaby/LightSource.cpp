#include "LightSource.h"

LightSource::LightSource(GLenum lightId) : lightId(lightId), enabled(false) {
}

void LightSource::enable() {
    enabled = true;
    glEnable(lightId);
}

void LightSource::disable() {
    enabled = false;
    glDisable(lightId);
}

bool LightSource::isEnabled() const {
    return enabled;
}

void LightSource::setPosition(const glm::vec4& pos) {
    position = pos;
}

void LightSource::setAmbient(const glm::vec4& amb) {
    ambient = amb;
}

void LightSource::setDiffuse(const glm::vec4& diff) {
    diffuse = diff;
}

void LightSource::setSpecular(const glm::vec4& spec) {
    specular = spec;
}

GLenum LightSource::getLightId() const {
    return lightId;
}

glm::vec4 LightSource::getPosition() const {
    return position;
}

glm::vec4 LightSource::getAmbient() const {
    return ambient;
}

glm::vec4 LightSource::getDiffuse() const {
    return diffuse;
}

glm::vec4 LightSource::getSpecular() const {
    return specular;
}