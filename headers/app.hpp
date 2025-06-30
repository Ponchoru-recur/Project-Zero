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
    // Private functions | TESTING |

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
    GLuint testShaders;

    // Class instances
    Camera camera;
    ShapeData ArrowShape = ShapeGenerator::makeArrow();
    ShapeData CubeShape = ShapeGenerator::makeCube();
    // The pov basically

    // temporary variables
    float move_straight = -0.3f;
    GLfloat fov = 60;
};
