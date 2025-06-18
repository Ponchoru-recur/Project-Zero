#include "camera.hpp"

Camera::Camera() : viewDirection(0.0f, 0.0f, -1.0f), UP(0.0f, 1.0f, 0.0f) {
}

void Camera::mouseUpdate(const glm::vec2 &newMousePosition) {
    const float sensitivity = 0.35;
    const float mouse_x = -newMousePosition.x * sensitivity;
    const float mouse_y = -newMousePosition.y * sensitivity;
    // Horizontal
    viewDirection = glm::mat3(glm::rotate(glm::mat4(1.0f), glm::radians(mouse_x), UP)) * viewDirection;
    // VErtical
    glm::vec3 rotateAround = glm::cross(viewDirection, UP);
    viewDirection = glm::mat3(glm::rotate(glm::mat4(1.0f), glm::radians(mouse_y), rotateAround)) * viewDirection;
}

glm::mat4 Camera::getWorldToViewMatrix() const {
    return glm::lookAt(position, position + viewDirection, UP);
}

glm::vec3 Camera::getPosition() {
    return position;
}

void Camera::moveForward() {
    position += movement_speed * viewDirection;
}

void Camera::moveBackward() {
    position += -movement_speed * viewDirection;
}

void Camera::strafeRight() {
    glm::vec3 straferight = glm::cross(viewDirection, UP);
    position += movement_speed * straferight;
}

void Camera::strafeLeft() {
    glm::vec3 strafeleft = glm::cross(viewDirection, UP);
    position += -movement_speed * strafeleft;
}

void Camera::moveUp() {
    position += movement_speed * UP;
}

void Camera::moveDown() {
    position += -movement_speed * UP;
}
