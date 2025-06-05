#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <iostream>
#include <memory>

#include "vertex.hpp"

class ShapeData {
   public:
    ShapeData() : vertices(0), num_vertices(0), indices(0), num_indices(0) {}
    Vertex *vertices;
    GLushort *indices;

    // Calculates the amount of bytes space needed for buffers
    GLsizei getvertices_size() const;
    GLsizei getindices_size() const;

    GLsizei num_vertices;
    GLsizei num_indices;
    ~ShapeData();

   private:
};
