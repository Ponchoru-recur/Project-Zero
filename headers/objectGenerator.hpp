#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cstddef>
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SDL3/SDL_image.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

struct Vortex {
    glm::vec3 Positions;
    glm::vec3 Normals;
    glm::vec2 Textures;
};

struct dynamicMesh {
    GLuint VAO = 0, VBO = 0, EBO = 0;  // Vertex Array Object, Vertex Buffer Object, Element Buffer Object.
    glm::mat4 objToWorldMatrix;
    GLsizei indexCount = 0;
    GLint data[30] = {0};
    std::vector<GLint> usedData;
};

struct staticMesh {
    glm::mat4 objToWorldMatrix;
    GLsizei indexCount;
    GLuint baseIndex;
    GLint baseVertex;
    GLint data[30] = {0};
    std::vector<GLint> usedData;
};

class ObjectGenerator {
   public:
    glm::vec2 uploadObj(std::string filepath, GLenum usage = GL_STATIC_DRAW);
    GLuint uploadImg(const char* filepath);
    void transform(glm::vec2& object_name, glm::vec3 translate, glm::vec3 rotate = glm::vec3(0.0f, 0.0f, 0.0f));
    void attach(glm::vec2 obj_index, GLuint img_index, GLshort textureOffset);
    void process();
    GLuint getStaticVao();
    const std::vector<dynamicMesh>& getDynamicMeshes() const;
    const std::vector<staticMesh>& getStaticMeshes() const;
    void cleanup();

   private:
    // Dynamic
    std::vector<dynamicMesh> Meshes;
    // Static Objects
    GLuint s_vao = 0;
    GLuint s_vbo = 0;
    GLuint s_ebo = 0;
    GLsizei currIndexSize = 0;
    GLsizei currVertexSize = 0;

    std::vector<Vortex> globalInterleavedData;
    std::vector<GLuint> globalIndices;
    std::vector<staticMesh> globalMeshes;
    // Texture
    std::vector<GLuint> sampleImages;
};
