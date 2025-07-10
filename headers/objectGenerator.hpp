#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cstddef>
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SDL3/SDL_image.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <camera.hpp>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 textureCoord;
    GLfloat textureFace;
};

struct Material {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    GLuint shininess;
};

class AssimpObject {
   public:
    AssimpObject(std::string filepath);
    ~AssimpObject();

    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
    std::vector<GLuint64> textureHandles;
    std::vector<GLuint> globalIndices;

   private:
    SDL_Surface* createImage(const char* filepath);
    void processToHandle(SDL_Surface* image_format);
    void processNode(aiNode* node, const aiScene* scene, std::vector<Vertex>& interleavedData, std::vector<GLuint>& indices, GLuint& vertexBase);
    void processMesh(aiMesh* mesh, const aiScene* scene, std::vector<Vertex>& interleavedData, std::vector<GLuint>& indices, GLuint& vertexBase);

    std::vector<Vertex> globalInterleavedData;
    // Temporary varaibles
    GLfloat temp = 0;
};

class testingOBJ {
   public:
    testingOBJ() = default;
    ~testingOBJ() = default;
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;

    void btestingOBJ() {
        GLfloat vertexAndTexturePos[] = {
            -1.0f, +1.0f, +0.0f, +0.0f, +1.0f, 0.0f,  // top-left
            +0.0f, +1.0f, +0.0f, +1.0f, +1.0f, 0.0f,  // top-right
            -1.0f, +0.0f, +0.0f, +0.0f, +0.0f, 0.0f,  // bottom-left

            +0.0f, +1.0f, +0.0f, +1.0f, +1.0f, 0.0f,  // top-right
            -1.0f, +0.0f, +0.0f, +0.0f, +0.0f, 0.0f,  // bottom-left
            +0.0f, +0.0f, +0.0f, +1.0f, +0.0f, 0.0f,  // bottom-right

            -1.0f, +1.0f, +1.0f, +0.0f, +1.0f, 1.0f,  // top-left
            +0.0f, +1.0f, +1.0f, +1.0f, +1.0f, 1.0f,  // top-right
            -1.0f, +0.0f, +1.0f, +0.0f, +0.0f, 1.0f,  // bottom-left

            +0.0f, +1.0f, +1.0f, +1.0f, +1.0f, 1.0f,  // top-right
            -1.0f, +0.0f, +1.0f, +0.0f, +0.0f, 1.0f,  // bottom-left
            +0.0f, +0.0f, +1.0f, +1.0f, +0.0f, 1.0f,  // bottom-right
        };
        GLuint elementIndices[] = {
            0, 2, 1,
            4, 5, 3,
            7, 8, 6,
            10, 11, 9};

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexAndTexturePos), vertexAndTexturePos, GL_STATIC_DRAW);

        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elementIndices), elementIndices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (void*)(0));
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (void*)(sizeof(GLfloat) * 3));
        glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (void*)(sizeof(GLfloat) * 5));
    }
};
