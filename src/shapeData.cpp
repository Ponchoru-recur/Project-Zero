#include "shapeData.hpp"

size_t ShapeData::getVerticeBufferSize() const {
    return num_vertices * sizeof(Vertex);
}

size_t ShapeData::getIndiceBufferSize() const {
    return num_indices * sizeof(GLushort);
}

void ShapeData::cleanup() {
    delete[] vertices;
    delete[] indices;
}
