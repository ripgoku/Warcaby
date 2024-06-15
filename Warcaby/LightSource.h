#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class LightSource {
public:
    LightSource(GLenum lightId);
    void enable();
    void disable();
    bool isEnabled() const;
    void setPosition(const glm::vec4& position);
    void setAmbient(const glm::vec4& ambient);
    void setDiffuse(const glm::vec4& diffuse);
    void setSpecular(const glm::vec4& specular);

    GLenum getLightId() const;
    glm::vec4 getPosition() const;
    glm::vec4 getAmbient() const;
    glm::vec4 getDiffuse() const;
    glm::vec4 getSpecular() const;

private:
    GLenum lightId;
    bool enabled;
    glm::vec4 position;
    glm::vec4 ambient;
    glm::vec4 diffuse;
    glm::vec4 specular;
};
