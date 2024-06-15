#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    Camera();
    void setPosition(const glm::vec3& newPosition);
    glm::vec3 getPosition();
    void move(const glm::vec3& offset);
    void rotate();
    void processMouseMovement(float xOffset, float yOffset, bool constrainPitch);
    glm::mat4 getViewMatrix() const;
    glm::vec3 getRightVector() const;
    glm::vec3 getFrontVector() const;
    void setFreeMode(bool enable);
    bool getFreeMode();
    double getOrbitAngle();

private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    float yaw;
    float pitch;
    float movementSpeed;
    float sensitivity;
    bool freeMode;
    double orbitRadius;
    double orbitAngle;
    double orbitSpeed;

    void updateCameraVectors();
};
