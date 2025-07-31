#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/gl.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <memory>

#include "window.hpp"
#include "shaders.hpp"
#include "camera.hpp"
#include "shapeGenerator.hpp"
#include "objectGenerator.hpp"

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
    // VAOS
    GLuint cubeVertexArrayID;
    GLuint arrowVertexArrayID;
    GLuint normalVertexArrayID;

    // BUFFERS
    GLuint theVertexBufferID;
    GLuint theIndexBufferID;
    GLuint normalBufferID;

    // Shaders
    GLuint shaderProgram;
    GLuint opShaderProgram;
    GLuint stencilShaderProgram;
    GLuint testShaders;

    // Class instances
    Camera camera;
    ShapeData ArrowShape = ShapeGenerator::makeArrow();
    ShapeData CubeShape = ShapeGenerator::makeCube();

    // Model Storage
    std::vector<std::unique_ptr<AssimpObject>> modelObjects;

    // FIXME: temporary variables
    float move_straight = -0.3f;
    GLfloat fov = 60;

    GLuint fbo;  // or frame buffer object
    GLuint texture;
};
