#pragma once

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <string>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <SDL3/SDL_image.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

struct Vortex {
    glm::vec3 Position;
    glm::vec3 Normals;
    glm::vec2 Textures;
};

struct Mesh {
    GLuint VAO = 0, VBO = 0, EBO = 0;  // Vertex Array Object, Vertex Buffer Object, Element Buffer Object.
    glm::mat4 objToWorldMatrix;
    GLsizei indexCount = 0;
    GLuint texture0 = 0;
    GLuint texture1 = 0;
};

struct StaticMeshInfo {
    glm::mat4 objToWorldMatrix;
    GLsizei indexCount;
    GLuint baseIndex;
    GLint baseVertex;
    GLuint texture0 = 0;
    GLuint texture1 = 0;
};

class ObjectGenerator {
   public:
    glm::vec2 uploadObj(std::string filepath, GLenum usage = GL_STATIC_DRAW);
    GLuint uploadImg(const char* filepath);
    void transform(glm::vec2& object_name, glm::vec3 translate, glm::vec3 rotate = glm::vec3(0.0f, 0.0f, 0.0f));
    void attach(glm::vec2 obj_index, GLuint img_index, bool affected_by_specular);
    void process();
    GLuint getStaticVao();
    const std::vector<Mesh>& getDynamicMeshes() const;
    const std::vector<StaticMeshInfo>& getStaticMeshes() const;
    void cleanup();

   private:
    // Dynamic
    std::vector<Mesh> Meshes;
    // Static Objects
    GLuint s_vao = 0;
    GLuint s_vbo = 0;
    GLuint s_ebo = 0;
    GLsizei currIndexSize = 0;
    GLsizei currVertexSize = 0;

    std::vector<GLfloat> s_verticesAndNormals;
    std::vector<GLfloat> s_textureCoordinates;
    std::vector<GLuint> s_indices;
    std::vector<StaticMeshInfo> s_meshes;

    // Texture
    std::vector<GLuint> sampleImages;
};
