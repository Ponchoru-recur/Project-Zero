#include "app.hpp"

const int VERTEX_BYTE_SIZE = 9;
/*
    BUFFER OVERVIEW GL_ARRAY_BUFFER : CUBEBUFFERSIZE | ARROWBUFFERSIZE
    BUFFER OVERVIEW GL_ELEMENT_ARRAY_BUFFER : CUBEINDICESIZE | ARROWINDICESIZE
*/

void App::init() {
    // Important! Init the shaders first!
    GLuint vertShader = Shader::compileShader(vertexShaderSource, GL_VERTEX_SHADER);
    GLuint fragShader = Shader::compileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
    shaderProgram = Shader::linkProgram(vertShader, fragShader);
    // Generate a buffer for information of the triangle
    glGenBuffers(1, &theVertexBufferID);
    glGenBuffers(1, &theIndexBufferID);
    // Important! make this first to make opengl remember how you described the data.
    glGenVertexArrays(1, &cubeVertexArrayID);
    glGenVertexArrays(1, &arrowVertexArrayID);
    // Describe how big the data
    glBindBuffer(GL_ARRAY_BUFFER, theVertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, (CubeShape.getVerticeBufferSize() + ArrowShape.getVerticeBufferSize()), 0, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, CubeShape.getVerticeBufferSize(), CubeShape.vertices);
    glBufferSubData(GL_ARRAY_BUFFER, CubeShape.getVerticeBufferSize(), ArrowShape.getVerticeBufferSize(), ArrowShape.vertices);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theIndexBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (CubeShape.getIndiceBufferSize() + ArrowShape.getIndiceBufferSize()), 0, GL_STATIC_DRAW);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, CubeShape.getIndiceBufferSize(), CubeShape.indices);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, CubeShape.getIndiceBufferSize(), ArrowShape.getIndiceBufferSize(), ArrowShape.indices);
    // Tell Opengl to store how it reads the data : FOR CUBE
    // Storage for data size so i wont go insane
    size_t currentBufferSize = 0;
    glBindVertexArray(cubeVertexArrayID);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, theVertexBufferID);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * VERTEX_BYTE_SIZE, 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * VERTEX_BYTE_SIZE, (void*)(sizeof(GLfloat) * 3));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * VERTEX_BYTE_SIZE, (void*)(sizeof(GLfloat) * 6));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theIndexBufferID);
    // Tell Opengl to store how it reads the data : FOR ARROW
    currentBufferSize += CubeShape.getVerticeBufferSize();
    glBindVertexArray(arrowVertexArrayID);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, theVertexBufferID);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * VERTEX_BYTE_SIZE, (void*)(currentBufferSize));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * VERTEX_BYTE_SIZE, (void*)(currentBufferSize + sizeof(GLfloat) * 3));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * VERTEX_BYTE_SIZE, (void*)(currentBufferSize + sizeof(GLfloat) * 6));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theIndexBufferID);

    // TESTING
    glGenVertexArrays(1, &normalVertexArrayID);
    glBindVertexArray(normalVertexArrayID);

    glGenBuffers(1, &normalBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, normalBufferID);

    for (size_t i = 0; i < 24; i++) {
        glm::vec3 pos = CubeShape.vertices[i].position;
        glm::vec3 norm = CubeShape.vertices[i].normal;

        normals.push_back(pos);
        normals.push_back(pos + norm * 1.0f);
    }
    glBufferData(GL_ARRAY_BUFFER, (normals.size() * sizeof(glm::vec3)), normals.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, 0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile("../assets/objects/testing.obj", aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "Assimp error: " << importer.GetErrorString() << std::endl;
        
    }

    std::cout << "Game initialzied.\n";
}

void App::handleEvent(const SDL_Event& event) {
    glm::vec2 mouse;
    SDL_GetRelativeMouseState(&mouse.x, &mouse.y);
    camera.mouseUpdate(mouse);
}

void App::update() {
    const bool* keyboardstate = SDL_GetKeyboardState(NULL);
    // SDL_PumpEvents();
    if (keyboardstate[SDL_SCANCODE_A]) {
        camera.strafeLeft();
    } else if (keyboardstate[SDL_SCANCODE_D]) {
        camera.strafeRight();
    }
    if (keyboardstate[SDL_SCANCODE_W]) {
        camera.moveForward();
    } else if (keyboardstate[SDL_SCANCODE_S]) {
        camera.moveBackward();
    }
    if (keyboardstate[SDL_SCANCODE_E]) {
        camera.moveUp();
    } else if (keyboardstate[SDL_SCANCODE_Q]) {
        camera.moveDown();
    } else if (keyboardstate[SDL_SCANCODE_UP]) {
        move_straight += 0.5f;
        std::cout << "move : " << move_straight << "\n";
    } else if (keyboardstate[SDL_SCANCODE_DOWN]) {
        move_straight -= 0.5f;
        std::cout << "move : " << move_straight << "\n";
    }
    glUseProgram(shaderProgram);
    GLuint getAmbientLightUniformLocation = glGetUniformLocation(shaderProgram, "ambientLight");
    glm::vec3 ambientLight = glm::vec3(0.7f, 0.7f, 0.7f);
    glUniform3fv(getAmbientLightUniformLocation, 1, glm::value_ptr(ambientLight));

    GLuint getLightPositionUniformLocation = glGetUniformLocation(shaderProgram, "lightPosition");
    glm::vec3 lightPosition = glm::vec3(0.0f, 3.0f, move_straight);
    glUniform3fv(getLightPositionUniformLocation, 1, glm::value_ptr(lightPosition));
}

void App::render() {
    GLuint getFullMatrixTransformLocation = glGetUniformLocation(shaderProgram, "FullMatrixTransform");

    // Cube
    glBindVertexArray(cubeVertexArrayID);
    glm::mat4 MatrixGangUwu = projectionMatrix * camera.getWorldToViewMatrix() * glm::translate(glm::mat4(1.0f), glm::vec3(3.5f, +0.0f, -2.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(getFullMatrixTransformLocation, 1, GL_FALSE, glm::value_ptr(MatrixGangUwu));
    glDrawElements(GL_TRIANGLES, CubeShape.num_indices, GL_UNSIGNED_SHORT, 0);

    glBindVertexArray(cubeVertexArrayID);
    MatrixGangUwu = projectionMatrix * camera.getWorldToViewMatrix() * glm::translate(glm::mat4(1.0f), glm::vec3(-3.5f, +0.0f, -2.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(getFullMatrixTransformLocation, 1, GL_FALSE, glm::value_ptr(MatrixGangUwu));
    glDrawElements(GL_TRIANGLES, CubeShape.num_indices, GL_UNSIGNED_SHORT, 0);

    // Arrow
    glBindVertexArray(arrowVertexArrayID);
    MatrixGangUwu = projectionMatrix * camera.getWorldToViewMatrix() * glm::translate(glm::mat4(1.0f), glm::vec3(-6.5f, +0.0f, -2.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(getFullMatrixTransformLocation, 1, GL_FALSE, glm::value_ptr(MatrixGangUwu));
    glDrawElements(GL_TRIANGLES, ArrowShape.num_indices, GL_UNSIGNED_SHORT, (void*)(CubeShape.getIndiceBufferSize()));

    glBindVertexArray(normalBufferID);
    MatrixGangUwu = projectionMatrix * camera.getWorldToViewMatrix() * glm::translate(glm::mat4(1.0f), glm::vec3(3.5f, +0.0f, -2.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(getFullMatrixTransformLocation, 1, GL_FALSE, glm::value_ptr(MatrixGangUwu));
    glDrawArrays(GL_LINES, 0, normals.size());

    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL Error: " << err << std::endl;
    }

    glBindVertexArray(0);
}

void App::cleanup() {
    CubeShape.cleanup();
    ArrowShape.cleanup();
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteVertexArrays(1, &cubeVertexArrayID);
    glDeleteVertexArrays(1, &arrowVertexArrayID);
    glDeleteBuffers(1, &theVertexBufferID);
    glDeleteBuffers(1, &theIndexBufferID);
    glDeleteProgram(shaderProgram);
    std::cout << "Cleanup done.\n";
}
