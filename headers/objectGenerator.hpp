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
    std::vector<GLuint> textures;
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
