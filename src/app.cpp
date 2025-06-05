#include "app.hpp"

void App::init() {
    // Important! Init the shaders first!
    GLuint vertShader = Shader::compileShader(vertexShaderSource, GL_VERTEX_SHADER);
    GLuint fragShader = Shader::compileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
    shaderProgram = Shader::linkProgram(vertShader, fragShader);

    // Important! make this first to make opengl remember how you described the data.
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Generate a buffer for information of the triangle
    glGenBuffers(1, &vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, ArrowShape.getvertices_size(), ArrowShape.vertices, GL_STATIC_DRAW);

    // Describe data (position = 0) then (color = 1)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (void*)(sizeof(GLfloat) * 3));

    glGenBuffers(1, &indexBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ArrowShape.getindices_size(), ArrowShape.indices, GL_STATIC_DRAW);
    // Enable the pipelines
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &fullTransformationMatrixBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, fullTransformationMatrixBufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * 2, 0, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(float) * 0));
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(float) * 4));
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(float) * 8));
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(float) * 12));

    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glEnableVertexAttribArray(4);
    glEnableVertexAttribArray(5);

    glVertexAttribDivisor(2, 1);
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);

    glBindVertexArray(0);

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

    glUseProgram(shaderProgram);
    // First arrow
    glm::mat4 fullMatrixProjection = projectionMatrix * camera.getWorldToViewMatrix() * glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, +0.0f, -2.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(60.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 fullTransforms[] = {
        projectionMatrix * camera.getWorldToViewMatrix() * glm::translate(glm::mat4(1.0f), glm::vec3(-1.5f, +0.0f, -2.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(60.0f), glm::vec3(1.0f, 0.0f, 0.0f)),
        projectionMatrix * camera.getWorldToViewMatrix() * glm::translate(glm::mat4(1.0f), glm::vec3(+1.5f, +0.0f, -2.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(160.0f), glm::vec3(0.0f, 1.0f, 0.0f))};
    glBindBuffer(GL_ARRAY_BUFFER, fullTransformationMatrixBufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(fullTransforms), fullTransforms, GL_DYNAMIC_DRAW);
}

void App::render() {
    glBindVertexArray(VAO);
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL Error: " << err << std::endl;
    }

    glDrawElementsInstanced(GL_TRIANGLES, ArrowShape.num_indices, GL_UNSIGNED_SHORT, 0, 2);

    glBindVertexArray(0);
}

void App::cleanup() {
    // ArrowShape.cleanup();
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &vertexBufferID);
    glDeleteBuffers(1, &indexBufferID);
    glDeleteProgram(shaderProgram);
    std::cout << "Cleanup done.\n";
}
