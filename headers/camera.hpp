#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
   public:
    Camera();
    void mouseUpdate(const glm::vec2 &newMousePosition);
    glm::mat4 getWorldToViewMatrix() const;

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
    glm::vec2 oldMousePosition;
};
