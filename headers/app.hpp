#pragma once

#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <iostream>
#include <memory>

#include "window.hpp"
#include "shaders.hpp"
#include "camera.hpp"
#include "shapeGenerator.hpp"

#define num_array_elements(a) sizeof(a) / sizeof(*a)

class App {
   public:
    App() = default;
    void init();
    void handleEvent(const SDL_Event& event);
    void update();
    void render();
    void cleanup();
    ~App() = default;

   private:
    struct Vertex {
        glm::vec3 position;
        glm::vec3 color;
    };

    GLuint VAO;
    GLuint vertexBufferID;
    GLuint indexBufferID;
    GLuint fullTransformationMatrixBufferID;
    GLuint shaderProgram;

    // Class instances
    Camera camera;
    ShapeData ArrowShape = ShapeGenerator::makeArrow();
    //
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(60.0f), static_cast<float>(window.getWidth()) / static_cast<float>(window.getHeight()), 1.0f, 10.0f);
};
