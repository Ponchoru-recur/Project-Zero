#include "shapeGenerator.hpp"

#define num_array_elements(a) sizeof(a) / sizeof(*a)

ShapeData ShapeGenerator::makeArrow() {
    ShapeData ret;

    Vertex arr1[] = {

        // Position
        // Color

        glm::vec3(-0.5f, -0.3f, -1.0f),  // 0 - left, back TOWARD THE SCREEN BTW
        glm::vec3(+1.0f, +0.0f, +0.0f),

        glm::vec3(+0.5f, -0.3f, -1.0f),  // 1 - right, back
        glm::vec3(+0.0f, +1.0f, +0.0f),

        glm::vec3(-0.5f, -0.3f, +0.5f),  // 2 - left, half-front
        glm::vec3(+0.0f, +0.0f, +1.0f),

        glm::vec3(+0.5f, -0.3f, +0.5f),  // 3 - right, half-front
        glm::vec3(+1.0f, +1.0f, +0.0f),

        glm::vec3(+0.7f, -0.3f, +0.5f),  // 4 - triangle tip right
        glm::vec3(+0.0f, +1.0f, +1.0f),

        glm::vec3(-0.7f, -0.3f, +0.5f),  // 5 - triangle tip left
        glm::vec3(+1.0f, +0.0f, +1.0f),

        glm::vec3(+0.0f, -0.3f, +1.0f),  // 6 - triangle tip center
        glm::vec3(+1.0f, +0.5f, +0.0f),

        // starting from here the coordinates are positioned to above the previous coords

        glm::vec3(-0.5f, +0.3f, -1.0f),  // 7 - left, back TOWARD THE SCREEN BTW
        glm::vec3(+0.5f, +0.0f, +0.5f),

        glm::vec3(+0.5f, +0.3f, -1.0f),  // 8 - right, back
        glm::vec3(+0.0f, +0.5f, +0.5f),

        glm::vec3(-0.5f, +0.3f, +0.5f),  // 9 - left, half-front
        glm::vec3(+0.5f, +1.0f, +0.0f),

        glm::vec3(+0.5f, +0.3f, +0.5f),  // 10 - right, half-front
        glm::vec3(+1.0f, +0.4f, +0.7f),

        glm::vec3(+0.7f, +0.3f, +0.5f),  // 11 - triangle tip right
        glm::vec3(+0.4f, +0.7f, +1.0f),

        glm::vec3(-0.7f, +0.3f, +0.5f),  // 12 - triangle tip left
        glm::vec3(+0.54f, +0.17f, +0.89f),

        glm::vec3(+0.0f, +0.3f, +1.0f),  // 13 - triangle tip center
        glm::vec3(+1.0f, +0.84f, +0.0f),
    };

    GLushort indexes[] = {
        // Up
        0, 1, 2,
        1, 3, 2,
        4, 5, 6,

        // Down
        7, 8, 9,
        8, 10, 9,
        11, 12, 13,

        // Sides

        // Back
        0, 1, 7,
        1, 7, 8,

        // Right
        1, 8, 10,
        1, 3, 10,

        // Left
        0, 2, 7,
        2, 7, 9,

        // Triangle tip
        // Right
        4, 6, 13,
        13, 11, 4,

        // Left
        6, 12, 13,
        6, 12, 5,

        // Behind the triangle tip
        5, 12, 11,
        5, 4, 11};

    // Passing the memory to ret.vertices
    ret.num_vertices = num_array_elements(arr1);
    ret.vertices = new Vertex[ret.num_vertices];
    memcpy(ret.vertices, arr1, sizeof(arr1));

    ret.num_indices = num_array_elements(indexes);
    ret.indices = new GLushort[ret.num_indices];
    memcpy(ret.indices, indexes, sizeof(indexes));

    return ret;
}
