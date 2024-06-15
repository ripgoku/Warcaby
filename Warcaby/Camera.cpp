#include "Camera.h"

Camera::Camera() :
    position(glm::vec3(0.0f, 8.0f, 0.0f)),
    front(glm::vec3(0.0f, 0.0f, 0.0f)),
    up(glm::vec3(0.0f, 1.0f, 0.0f)),
    yaw(-90.0f),
    pitch(-45.0f),
    movementSpeed(0.4f),
    sensitivity(0.1f),
    freeMode(false),
    orbitRadius(8.0f),
    orbitSpeed(5.0f),
    orbitAngle(90.0f) {
    updateCameraVectors();
}

void Camera::setPosition(const glm::vec3& newPosition) {
    position = newPosition;
    updateCameraVectors();
}

glm::vec3 Camera::getPosition() {
    return this->position;
}

void Camera::move(const glm::vec3& offset) {
    if (freeMode)
    {
        position += offset * movementSpeed;
        updateCameraVectors();
    }
}

void Camera::rotate() {
    updateCameraVectors();
}

void Camera::processMouseMovement(float xOffset, float yOffset, bool constrainPitch) {
    if (freeMode) {
        xOffset *= sensitivity;
        yOffset *= sensitivity;

        yaw += xOffset;
        pitch += yOffset;

        if (constrainPitch) {
            if (pitch > 89.0f) pitch = 89.0f;
            if (pitch < -89.0f) pitch = -89.0f;
        }

        updateCameraVectors();
    }
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + front, up);
}

void Camera::updateCameraVectors() {
    if(freeMode) {
        glm::vec3 newFront;
        newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        newFront.y = sin(glm::radians(pitch));
        newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(newFront);
    }
    else {
        position.x = orbitRadius * cos(glm::radians(orbitAngle));
        position.z = orbitRadius * sin(glm::radians(orbitAngle));

        front = glm::normalize(glm::vec3(0.0f, 0.0f, 0.0f) - position);

        orbitAngle += orbitSpeed;

        if (orbitAngle > 360.0f)
            orbitAngle -= 360.0f;
    }
}

glm::vec3 Camera::getRightVector() const {
    return glm::normalize(glm::cross(front, up));
}

glm::vec3 Camera::getFrontVector() const {
    return glm::normalize(front);
}

void Camera::setFreeMode(bool enable) {
    this->freeMode = enable;
}

bool Camera::getFreeMode() {
    return this->freeMode;
}

double Camera::getOrbitAngle() {
    return orbitAngle;
}