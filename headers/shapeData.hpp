#pragma once

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <iostream>
#include <memory>

#include "vertex.hpp"

class ShapeData {
   public:
    ShapeData() : vertices(0), indices(0), num_vertices(0), num_indices(0) {}
    Vertex *vertices;
    GLushort *indices;

    // Calculates the amount of bytes space needed for buffers
    size_t getVerticeBufferSize() const;
    size_t getIndiceBufferSize() const;

    GLsizei num_vertices;
    GLsizei num_indices;
    GLsizei num_normals;
    void cleanup();

   private:
};
