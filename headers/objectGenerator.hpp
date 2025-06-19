#pragma once

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

struct Mesh {
    GLuint VAO, VBO, EBO;  // Vertex Array Object, Vertex Buffer Object, Element Buffer Object.
    GLsizei indexCount;    // Amount of indices.
};

class ObjectGenerator {
   public:
    void uploadObj(std::string filepath);
    std::vector<Mesh>& getinfo();

   private:
    std::vector<Mesh> ObjectStorage;
};
