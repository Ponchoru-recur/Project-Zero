#pragma once

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <string>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

struct Mesh {
    GLuint VAO = 0, VBO = 0, EBO = 0;  // Vertex Array Object, Vertex Buffer Object, Element Buffer Object.
    glm::mat4 objToWorldMatrix;
    GLsizei indexCount = 0;
};

struct StaticMeshInfo {
    glm::mat4 objToWorldMatrix;
    GLsizei indexCount;
    GLuint baseIndex;
    GLint baseVertex;
};

class ObjectGenerator {
   public:
    glm::vec2 uploadObj(std::string filepath, GLenum usage = GL_STATIC_DRAW);
    void transform(glm::vec2& object_name, glm::vec3 translate, glm::vec3 rotate = glm::vec3(0.0f, 0.0f, 0.0f));
    void process();
    GLuint getStaticVao();
    const std::vector<Mesh>& getDynamicMeshes() const;
    const std::vector<StaticMeshInfo>& getStaticMeshes() const;
    void cleanup();

   private:
    // Static Objects
    GLuint s_vao = 0;
    GLuint s_vbo = 0;
    GLuint s_ebo = 0;
    GLsizei currIndexSize = 0;
    GLsizei currVertexSize = 0;

    std::vector<GLfloat> s_verticesAndNormals;
    std::vector<GLfloat> s_color;
    std::vector<GLuint> s_indices;
    std::vector<Mesh> Meshes;
    std::vector<StaticMeshInfo> s_meshes;
};
