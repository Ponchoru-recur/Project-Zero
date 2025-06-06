#include "app.hpp"

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
    glGenVertexArrays(1, &ArrowVertexArrayID);
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
    glBindVertexArray(cubeVertexArrayID);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, theVertexBufferID);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (void*)(sizeof(GLfloat) * 3));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theIndexBufferID);
    // Tell Opengl to store how it reads the data : FOR CUBE
    glBindVertexArray(ArrowVertexArrayID);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, theVertexBufferID);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (void*)(CubeShape.getVerticeBufferSize()));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (void*)(CubeShape.getVerticeBufferSize() + sizeof(GLfloat) * 3));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theIndexBufferID);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // Enable the pipelines

    std::cout << "Game initialzied.\n";
}

void App::handleEvent(const SDL_Event& event) {
    glm::vec2 mouse;
    SDL_GetRelativeMouseState(&mouse.x, &mouse.y);
    std::cout << "X : " << mouse.x << "\n";
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
    }
}

void App::render() {
    glUseProgram(shaderProgram);
    GLuint getFullMatrixTransformLocation = glGetUniformLocation(shaderProgram, "FullMatrixTransform");

    // Cube
    glBindVertexArray(cubeVertexArrayID);
    glm::mat4 MatrixGangUwu = projectionMatrix * camera.getWorldToViewMatrix() * glm::translate(glm::mat4(1.0f), glm::vec3(-1.5f, +0.0f, -2.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(60.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(getFullMatrixTransformLocation, 1, GL_FALSE, glm::value_ptr(MatrixGangUwu));
    glDrawElements(GL_TRIANGLES, CubeShape.num_indices, GL_UNSIGNED_SHORT, 0);

    glBindVertexArray(cubeVertexArrayID);
    MatrixGangUwu = projectionMatrix * camera.getWorldToViewMatrix() * glm::translate(glm::mat4(1.0f), glm::vec3(-3.5f, +0.0f, -2.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(60.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(getFullMatrixTransformLocation, 1, GL_FALSE, glm::value_ptr(MatrixGangUwu));
    glDrawElements(GL_TRIANGLES, CubeShape.num_indices, GL_UNSIGNED_SHORT, 0);

    // Arrow
    glBindVertexArray(ArrowVertexArrayID);
    MatrixGangUwu = projectionMatrix * camera.getWorldToViewMatrix() * glm::translate(glm::mat4(1.0f), glm::vec3(-5.5f, +0.0f, -2.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(60.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(getFullMatrixTransformLocation, 1, GL_FALSE, glm::value_ptr(MatrixGangUwu));
    glDrawElements(GL_TRIANGLES, ArrowShape.num_indices, GL_UNSIGNED_SHORT, (void*)(CubeShape.getIndiceBufferSize()));

    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL Error: " << err << std::endl;
    }

    glBindVertexArray(0);
}

void App::cleanup() {
    // ArrowShape.cleanup();
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteVertexArrays(1, &cubeVertexArrayID);
    glDeleteVertexArrays(1, &ArrowVertexArrayID);
    glDeleteBuffers(1, &theVertexBufferID);
    glDeleteBuffers(1, &theIndexBufferID);
    glDeleteProgram(shaderProgram);
    std::cout << "Cleanup done.\n";
}
