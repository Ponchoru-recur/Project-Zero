#pragma once

#include <glm/glm.hpp>
#include "window.hpp"
#include <glm/gtc/matrix_transform.hpp>

class Camera {
   public:
    Camera();
    void mouseUpdate(const glm::vec2 &newMousePosition);
    void changefov(GLfloat &fov);
    glm::mat4 getProjectionMatrix();
    glm::mat4 getWorldToViewMatrix() const;
    glm::vec3 getPosition();

    void moveForward();
    void moveBackward();
    void strafeRight();
    void strafeLeft();
    void moveUp();
    void moveDown();
    ~Camera() = default;

   private:
    const float movement_speed = 0.1f;
    glm::vec3 position;
    glm::vec3 viewDirection;
    const glm::vec3 UP;
    glm::mat4 projectionMatrix;
    GLfloat fov = 60.0f;
};
