#pragma once

#include <SDL3/SDL_image.h>
#include <glad/gl.h>
#include <iostream>

#include <string>
#include <vector>
#include <cstddef>
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

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

    std::vector<GLuint> globalIndices;
    std::vector<GLuint> imageIndices;  // This takes the array position of the images in the textureHandles
    static std::vector<GLuint64> textureHandles;

    void applyTransformation(glm::vec3 translate, glm::vec3 rotate = glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f));
    glm::mat4 getModelToWorldTransform();

   private:  // Note glm uses ZYX instead of XYZ
    glm::mat4 modelToWorld = glm::mat4(1.0f);

    SDL_Surface* createImage(const char* filepath);
    void processToHandle(SDL_Surface* image_format);
    void loadTextureIndex(std::string path);
    void processNode(aiNode* node, const aiScene* scene, std::vector<Vertex>& interleavedData, std::vector<GLuint>& indices, GLuint& vertexBase);
    void processMesh(aiMesh* mesh, const aiScene* scene, std::vector<Vertex>& interleavedData, std::vector<GLuint>& indices, GLuint& vertexBase);

    std::vector<Vertex> globalInterleavedData;
    std::vector<GLuint> textures;
    // Temporary varaibles
    GLfloat temp = 0;

    // VERY IMPORTANT
    static GLuint imageIndexCounter;
    static std::unordered_map<std::string, size_t> textureIndexMap;
};
