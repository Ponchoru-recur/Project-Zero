#include "shapeData.hpp"

GLsizei ShapeData::getvertices_size() const {
    return num_vertices * sizeof(Vertex);
}

GLsizei ShapeData::getindices_size() const {
    return num_indices * sizeof(GLushort);
}

ShapeData::~ShapeData() {
    delete[] vertices;
    delete[] indices;
}
