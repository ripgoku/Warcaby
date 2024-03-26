#include "Camera.h"

Camera::Camera() :
    position(glm::vec3(0.0f, 0.0f, 3.0f)),
    front(glm::vec3(0.0f, 0.0f, -1.0f)),
    up(glm::vec3(0.0f, 1.0f, 0.0f)),
    yaw(-90.0f),
    pitch(0.0f),
    movementSpeed(0.4f),
    sensitivity(0.1f) {
    updateCameraVectors();
}

void Camera::setPosition(const glm::vec3& newPosition) {
    position = newPosition;
    updateCameraVectors();
}

void Camera::move(const glm::vec3& offset) {
    position += offset * movementSpeed;
    updateCameraVectors();
}

void Camera::rotate(float deltaYaw, float deltaPitch) {
    yaw += deltaYaw * sensitivity;
    pitch += deltaPitch * sensitivity;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    updateCameraVectors();
}

void Camera::processMouseMovement(float xOffset, float yOffset, bool constrainPitch) {
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

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + front, up);
}

void Camera::updateCameraVectors() {
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(newFront);
}

glm::vec3 Camera::getRightVector() const {
    return glm::normalize(glm::cross(front, up));
}

glm::vec3 Camera::getFrontVector() const {
    return glm::normalize(front);
}