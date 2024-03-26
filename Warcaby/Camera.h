#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    Camera();

    void setPosition(const glm::vec3& newPosition);
    void move(const glm::vec3& offset);
    void rotate(float deltaYaw, float deltaPitch);
    void processMouseMovement(float xOffset, float yOffset, bool constrainPitch);

    glm::mat4 getViewMatrix() const;
    glm::vec3 getRightVector() const;
    glm::vec3 getFrontVector() const;

private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    float yaw;
    float pitch;
    float movementSpeed;
    float sensitivity;

    void updateCameraVectors();
};
