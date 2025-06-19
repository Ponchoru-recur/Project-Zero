#pragma once

#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <iostream>
#include <memory>
#include <vector>

// Assimp testing
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

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
    // Private functions | TESTING |
    void processMesh(aiMesh* mesh);
    void processNode(aiNode* node, const aiScene* scene);
    // VAOS
    GLuint cubeVertexArrayID;
    GLuint arrowVertexArrayID;
    GLuint normalVertexArrayID;
    GLuint SceneVertexArrayID;
    // BUFFERS
    GLuint theVertexBufferID;
    GLuint theIndexBufferID;
    GLuint normalBufferID;
    GLuint SceneVertexBufferID;
    GLuint SceneElementBufferID;

    GLuint shaderProgram;

    // Class instances
    Camera camera;
    ShapeData ArrowShape = ShapeGenerator::makeArrow();
    ShapeData CubeShape = ShapeGenerator::makeCube();
    // The pov basically
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(60.0f), static_cast<float>(window.getWidth()) / static_cast<float>(window.getHeight()), 1.0f, 40.0f);
    // Vectors

    std::vector<GLfloat> vertices;  // TESTING
    std::vector<GLuint> indices;    // TESTING
    // temporary variables
    float move_straight = 0;
};
