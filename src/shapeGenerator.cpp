#include "shapeGenerator.hpp"

#define num_array_elements(a) sizeof(a) / sizeof(*a)

ShapeData ShapeGenerator::makeArrow() {
    ShapeData ret;

    Vertex arr1[] = {
        /* Position | Color | Normal */

        // TOP
        {glm::vec3(-0.5f, +0.0f, -1.5f), glm::vec3(+1.0f, +0.0f, +0.0f), glm::vec3(+0.0f, +1.0f, +0.0f)},  // 0 LEFT-BACK
        {glm::vec3(-0.5f, +0.0f, +0.0f), glm::vec3(+0.0f, +0.0f, +1.0f), glm::vec3(+0.0f, +1.0f, +0.0f)},  // 1 LEFT-FRONT
        {glm::vec3(+0.5f, +0.0f, +0.0f), glm::vec3(+0.0f, +0.0f, +1.0f), glm::vec3(+0.0f, +1.0f, +0.0f)},  // 2 RIGHT-FRONT

        {glm::vec3(-0.5f, +0.0f, -1.5f), glm::vec3(+1.0f, +0.0f, +0.0f), glm::vec3(+0.0f, +1.0f, +0.0f)},  // 3 LEFT-BACK
        {glm::vec3(+0.5f, +0.0f, -1.5f), glm::vec3(+1.0f, +0.0f, +0.0f), glm::vec3(+0.0f, +1.0f, +0.0f)},  // 4 RIGHT-BACK
        {glm::vec3(+0.5f, +0.0f, +0.0f), glm::vec3(+0.0f, +0.0f, +1.0f), glm::vec3(+0.0f, +1.0f, +0.0f)},  // 5 RIGHT-FRONT
        // BOTTOM
        {glm::vec3(-0.5f, -0.5f, -1.5f), glm::vec3(+1.0f, +0.0f, +0.0f), glm::vec3(+0.0f, -1.0f, +0.0f)},  // 6 LEFT-BACK
        {glm::vec3(-0.5f, -0.5f, +0.0f), glm::vec3(+0.0f, +0.0f, +1.0f), glm::vec3(+0.0f, -1.0f, +0.0f)},  // 7 LEFT-FRONT
        {glm::vec3(+0.5f, -0.5f, +0.0f), glm::vec3(+0.0f, +0.0f, +1.0f), glm::vec3(+0.0f, -1.0f, +0.0f)},  // 8 RIGHT-FRONT

        {glm::vec3(-0.5f, -0.5f, -1.5f), glm::vec3(+1.0f, +0.0f, +0.0f), glm::vec3(+0.0f, -1.0f, +0.0f)},  // 9 LEFT-BACK
        {glm::vec3(+0.5f, -0.5f, -1.5f), glm::vec3(+1.0f, +0.0f, +0.0f), glm::vec3(+0.0f, -1.0f, +0.0f)},  // 10 RIGHT-BACK
        {glm::vec3(+0.5f, -0.5f, +0.0f), glm::vec3(+0.0f, +0.0f, +1.0f), glm::vec3(+0.0f, -1.0f, +0.0f)},  // 11 RIGHT-FRONT
        // RIGHT SIDE
        {glm::vec3(+0.5f, +0.0f, +0.0f), glm::vec3(+1.0f, +0.0f, +0.0f), glm::vec3(+1.0f, +0.0f, +0.0f)},  // 12 TOP-RIGHT
        {glm::vec3(+0.5f, -0.5f, +0.0f), glm::vec3(+1.0f, +0.0f, +0.0f), glm::vec3(+1.0f, +0.0f, +0.0f)},  // 13 BOTTOM-RIGHT
        {glm::vec3(+0.5f, -0.5f, -1.5f), glm::vec3(+0.0f, +0.0f, +1.0f), glm::vec3(+1.0f, +0.0f, +0.0f)},  // 14 BOTTOM-RIGHT-BACK

        {glm::vec3(+0.5f, +0.0f, +0.0f), glm::vec3(+1.0f, +0.0f, +0.0f), glm::vec3(+1.0f, +0.0f, +0.0f)},  // 15 TOP-RIGHT
        {glm::vec3(+0.5f, +0.0f, -1.5f), glm::vec3(+1.0f, +0.0f, +0.0f), glm::vec3(+1.0f, +0.0f, +0.0f)},  // 16 TOP-RIGHT-BACK
        {glm::vec3(+0.5f, -0.5f, -1.5f), glm::vec3(+0.0f, +0.0f, +1.0f), glm::vec3(+1.0f, +0.0f, +0.0f)},  // 17 BOTTOM-RIGHT-BACK
        // LEFT SIDE
        {glm::vec3(-0.5f, +0.0f, +0.0f), glm::vec3(+1.0f, +0.0f, +0.0f), glm::vec3(-1.0f, +0.0f, +0.0f)},  // 18 TOP-RIGHT
        {glm::vec3(-0.5f, -0.5f, +0.0f), glm::vec3(+1.0f, +0.0f, +0.0f), glm::vec3(-1.0f, +0.0f, +0.0f)},  // 19 BOTTOM-RIGHT
        {glm::vec3(-0.5f, -0.5f, -1.5f), glm::vec3(+0.0f, +0.0f, +1.0f), glm::vec3(-1.0f, +0.0f, +0.0f)},  // 20 BOTTOM-RIGHT-BACK

        {glm::vec3(-0.5f, +0.0f, +0.0f), glm::vec3(+1.0f, +0.0f, +0.0f), glm::vec3(-1.0f, +0.0f, +0.0f)},  // 21 TOP-RIGHT
        {glm::vec3(-0.5f, +0.0f, -1.5f), glm::vec3(+1.0f, +0.0f, +0.0f), glm::vec3(-1.0f, +0.0f, +0.0f)},  // 22 TOP-RIGHT-BACK
        {glm::vec3(-0.5f, -0.5f, -1.5f), glm::vec3(+0.0f, +0.0f, +1.0f), glm::vec3(-1.0f, +0.0f, +0.0f)},  // 23 BOTTOM-RIGHT-BACK
        // BACK
        {glm::vec3(-0.5f, +0.0f, -1.5f), glm::vec3(+1.0f, +0.0f, +0.0f), glm::vec3(+0.0f, +0.0f, -1.0f)},  // 24 TOP-LEFT-BACK
        {glm::vec3(-0.5f, -0.5f, -1.5f), glm::vec3(+1.0f, +0.0f, +0.0f), glm::vec3(+0.0f, +0.0f, -1.0f)},  // 25 BOTTOM-LEFT-BACK
        {glm::vec3(+0.5f, +0.0f, -1.5f), glm::vec3(+0.0f, +0.0f, +1.0f), glm::vec3(+0.0f, +0.0f, -1.0f)},  // 26 TOP-RIGHT-BACK

        {glm::vec3(+0.5f, +0.0f, -1.5f), glm::vec3(+1.0f, +0.0f, +0.0f), glm::vec3(+0.0f, +0.0f, -1.0f)},  // 27 TOP-RIGHT-BACK
        {glm::vec3(-0.5f, -0.5f, -1.5f), glm::vec3(+1.0f, +0.0f, +0.0f), glm::vec3(+0.0f, +0.0f, -1.0f)},  // 28 BOTTOM-LEFT-BACK
        {glm::vec3(+0.5f, -0.5f, -1.5f), glm::vec3(+0.0f, +0.0f, +1.0f), glm::vec3(+0.0f, +0.0f, -1.0f)},  // 29 BOTTOM-RIGHT-BACK
        // FRONT
        {glm::vec3(-0.5f, +0.0f, +0.0f), glm::vec3(+1.0f, +0.0f, +0.0f), glm::vec3(+0.0f, +0.0f, +1.0f)},  // 30 TOP-LEFT-FRONT
        {glm::vec3(-0.5f, -0.5f, +0.0f), glm::vec3(+1.0f, +0.0f, +0.0f), glm::vec3(+0.0f, +0.0f, +1.0f)},  // 31 BOTTOM-LEFT-FRONT
        {glm::vec3(+0.5f, +0.0f, +0.0f), glm::vec3(+0.0f, +0.0f, +1.0f), glm::vec3(+0.0f, +0.0f, +1.0f)},  // 32 TOP-RIGHT-FRONT

        {glm::vec3(+0.5f, +0.0f, +0.0f), glm::vec3(+1.0f, +0.0f, +0.0f), glm::vec3(+0.0f, +0.0f, +1.0f)},  // 33 TOP-RIGHT-FRONT
        {glm::vec3(-0.5f, -0.5f, +0.0f), glm::vec3(+1.0f, +0.0f, +0.0f), glm::vec3(+0.0f, +0.0f, +1.0f)},  // 34 BOTTOM-LEFT-FRONT
        {glm::vec3(+0.5f, -0.5f, +0.0f), glm::vec3(+0.0f, +0.0f, +1.0f), glm::vec3(+0.0f, +0.0f, +1.0f)},  // 35 BOTTOM-RIGHT-FRONT
    };

    GLushort indexes[] = {
        // TOP
        0,
        1,
        2,
        4,
        3,
        5,
        // BOTTOM
        6,
        8,
        7,
        9,
        10,
        11,
        // RIGHT SIDE
        14,
        12,
        13,
        15,
        17,
        16,
        // LEFT SIDE
        19,
        18,
        20,
        22,
        23,
        21,
        // BACK
        24,
        26,
        25,
        27,
        29,
        28,
        // FRONT
        30,
        31,
        32,
        33,
        34,
        35,
    };

    // Passing the memory to ret.vertices
    ret.num_vertices = num_array_elements(arr1);
    ret.vertices = new Vertex[ret.num_vertices];
    memcpy(ret.vertices, arr1, sizeof(arr1));

    ret.num_indices = num_array_elements(indexes);
    ret.indices = new GLushort[ret.num_indices];
    memcpy(ret.indices, indexes, sizeof(indexes));

    return ret;
}

ShapeData ShapeGenerator::makeCube() {
    ShapeData ret;

    Vertex arr1[] = {
        // Face 1 (Top)
        {glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
        {glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
        {glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
        {glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},

        // Face 2 (Front)
        {glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)},
        {glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)},
        {glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)},
        {glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)},

        // Face 3 (Left)
        {glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f)},
        {glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f)},
        {glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f)},
        {glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f)},

        // Face 4 (Bottom)
        {glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)},
        {glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)},
        {glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)},
        {glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)},

        // Face 5 (Right)
        {glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f)},
        {glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f)},
        {glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f)},
        {glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f)},

        // Face 6 (Back)
        {glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f)},
        {glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f)},
        {glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f)},
        {glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f)},
    };

    GLushort indexes[] = {
        0, 1, 2, 0, 2, 3,        // Top
        4, 5, 6, 4, 6, 7,        // Front
        8, 9, 10, 8, 10, 11,     // Left
        12, 13, 14, 12, 14, 15,  // Bottom
        16, 17, 18, 16, 18, 19,  // Right
        20, 21, 22, 20, 22, 23   // Back
    };

    // Passing the memory to ret.vertices
    ret.num_vertices = num_array_elements(arr1);
    ret.vertices = new Vertex[ret.num_vertices];
    memcpy(ret.vertices, arr1, sizeof(arr1));

    ret.num_indices = num_array_elements(indexes);
    ret.indices = new GLushort[ret.num_indices];
    memcpy(ret.indices, indexes, sizeof(indexes));

    return ret;
}

ShapeData ShapeGenerator::makePlatform() {
    ShapeData ret;

    Vertex arr1[] = {
        /* Position            | Color (gray)       | Normal (up)       */
        // First triangle
        {glm::vec3(-10.0f, 0.0f, -10.0f), glm::vec3(0.6f, 0.6f, 0.6f), glm::vec3(0.0f, 1.0f, 0.0f)},  // 0
        {glm::vec3(-10.0f, 0.0f, 10.0f), glm::vec3(0.6f, 0.6f, 0.6f), glm::vec3(0.0f, 1.0f, 0.0f)},   // 1
        {glm::vec3(10.0f, 0.0f, 10.0f), glm::vec3(0.6f, 0.6f, 0.6f), glm::vec3(0.0f, 1.0f, 0.0f)},    // 2

        // Second triangle
        {glm::vec3(-10.0f, 0.0f, -10.0f), glm::vec3(0.6f, 0.6f, 0.6f), glm::vec3(0.0f, 1.0f, 0.0f)},  // 3
        {glm::vec3(10.0f, 0.0f, 10.0f), glm::vec3(0.6f, 0.6f, 0.6f), glm::vec3(0.0f, 1.0f, 0.0f)},    // 4
        {glm::vec3(10.0f, 0.0f, -10.0f), glm::vec3(0.6f, 0.6f, 0.6f), glm::vec3(0.0f, 1.0f, 0.0f)},   // 5
    };

    GLushort indexes[] = {
        0, 1, 2,  // First triangle
        0, 2, 3   // Second triangle
    };

    // Passing the memory to ret.vertices
    ret.num_vertices = num_array_elements(arr1);
    ret.vertices = new Vertex[ret.num_vertices];
    memcpy(ret.vertices, arr1, sizeof(arr1));

    ret.num_indices = num_array_elements(indexes);
    ret.indices = new GLushort[ret.num_indices];
    memcpy(ret.indices, indexes, sizeof(indexes));

    return ret;
}
