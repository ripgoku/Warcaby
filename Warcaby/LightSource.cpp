#include "LightSource.h"

LightSource::LightSource(GLenum lightId) : lightId(lightId), enabled(false) {
    glEnable(lightId);
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
    glLightfv(lightId, GL_POSITION, glm::value_ptr(position));
}

void LightSource::setAmbient(const glm::vec4& amb) {
    ambient = amb;
    glLightfv(lightId, GL_AMBIENT, glm::value_ptr(ambient));
}

void LightSource::setDiffuse(const glm::vec4& diff) {
    diffuse = diff;
    glLightfv(lightId, GL_DIFFUSE, glm::value_ptr(diffuse));
}

void LightSource::setSpecular(const glm::vec4& spec) {
    specular = spec;
    glLightfv(lightId, GL_SPECULAR, glm::value_ptr(specular));
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