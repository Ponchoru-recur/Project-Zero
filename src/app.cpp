#include "app.hpp"

SDL_Surface* App::getImageFormat(const char* filepath) {
    SDL_Surface* surface = IMG_Load(filepath);
    if (!surface) {
        SDL_Log("Could not load image : %s", SDL_GetError());
        SDL_DestroySurface(surface);
        return nullptr;
    }

    SDL_Surface* formatted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);
    SDL_DestroySurface(surface);

    if (!formatted) {
        SDL_Log("Could not load format : %s", SDL_GetError());
        SDL_DestroySurface(formatted);
        return nullptr;
    }
    return formatted;
}

void App::makeTexture(SDL_Surface* image_format) {
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_format->w, image_format->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_format->pixels);
    glGenerateMipmap(GL_TEXTURE_2D);

    GLuint64 handle = glGetTextureHandleARB(texture);
    glMakeTextureHandleResidentARB(handle);

    textureHandles.push_back(handle);

    SDL_DestroySurface(image_format);

    glBindTexture(GL_TEXTURE_2D, 0);
    return;
}

const int VERTEX_BYTE_SIZE = 9;
/*
    BUFFER OVERVIEW GL_ARRAY_BUFFER : CUBEBUFFERSIZE | ARROWBUFFERSIZE
    BUFFER OVERVIEW GL_ELEMENT_ARRAY_BUFFER : CUBEINDICESIZE | ARROWINDICESIZE
*/

void App::init() {
    // Important! Init the shaders first!
    std::string vertexShaderSource = Shader::LoadShaderFileSource("../shaders/vertexShader.vs");
    std::string fragmentShaderSource = Shader::LoadShaderFileSource("../shaders/fragmentShader.fs");
    GLuint vertShader = Shader::compileShader(vertexShaderSource, GL_VERTEX_SHADER);
    GLuint fragShader = Shader::compileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
    shaderProgram = Shader::linkProgram(vertShader, fragShader);

    // Important! | Optimized Shaders |
    std::string OpVertSource = Shader::LoadShaderFileSource("../shaders/opvertexshader.vs");
    std::string OptestFragSource = Shader::LoadShaderFileSource("../shaders/opfragshader.fs");
    GLuint OpVert = Shader::compileShader(OpVertSource, GL_VERTEX_SHADER);
    GLuint OpFrag = Shader::compileShader(OptestFragSource, GL_FRAGMENT_SHADER);
    opShaderProgram = Shader::linkProgram(OpVert, OpFrag);

    std::string testVertSource = Shader::LoadShaderFileSource("../shaders/testVertShader.vs");
    std::string testFragSource = Shader::LoadShaderFileSource("../shaders/testFragShader.fs");
    GLuint testVertexShader = Shader::compileShader(testVertSource, GL_VERTEX_SHADER);
    GLuint testFragShader = Shader::compileShader(testFragSource, GL_FRAGMENT_SHADER);
    testShaders = Shader::linkProgram(testVertexShader, testFragShader);

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
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * VERTEX_BYTE_SIZE, (void*)(sizeof(GLfloat) * 3));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * VERTEX_BYTE_SIZE, (void*)(sizeof(GLfloat) * 6));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theIndexBufferID);
    // Tell Opengl to store how it reads the data : FOR ARROW
    currentBufferSize += CubeShape.getVerticeBufferSize();
    glBindVertexArray(arrowVertexArrayID);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, theVertexBufferID);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * VERTEX_BYTE_SIZE, (void*)(currentBufferSize));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * VERTEX_BYTE_SIZE, (void*)(currentBufferSize + sizeof(GLfloat) * 3));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * VERTEX_BYTE_SIZE, (void*)(currentBufferSize + sizeof(GLfloat) * 6));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theIndexBufferID);

    // Making yet another testing
    // Position | Texture Coordinates | Face
    GLfloat vertexAndTexturePos[] = {
        -1.0f, +1.0f, +0.0f, +0.0f, +1.0f, 0.0f,  // top-left
        +0.0f, +1.0f, +0.0f, +1.0f, +1.0f, 0.0f,  // top-right
        -1.0f, +0.0f, +0.0f, +0.0f, +0.0f, 0.0f,  // bottom-left

        +0.0f, +1.0f, +0.0f, +1.0f, +1.0f, 0.0f,  // top-right
        -1.0f, +0.0f, +0.0f, +0.0f, +0.0f, 0.0f,  // bottom-left
        +0.0f, +0.0f, +0.0f, +1.0f, +0.0f, 0.0f,  // bottom-right

        -1.0f, +1.0f, +1.0f, +0.0f, +1.0f, 1.0f,  // top-left
        +0.0f, +1.0f, +1.0f, +1.0f, +1.0f, 1.0f,  // top-right
        -1.0f, +0.0f, +1.0f, +0.0f, +0.0f, 1.0f,  // bottom-left

        +0.0f, +1.0f, +1.0f, +1.0f, +1.0f, 1.0f,  // top-right
        -1.0f, +0.0f, +1.0f, +0.0f, +0.0f, 1.0f,  // bottom-left
        +0.0f, +0.0f, +1.0f, +1.0f, +0.0f, 1.0f,  // bottom-right
    };
    GLuint elementIndices[] = {
        0, 2, 1,
        4, 5, 3,
        7, 8, 6,
        10, 11, 9};

    glGenVertexArrays(1, &testVAO);
    glBindVertexArray(testVAO);

    glGenBuffers(1, &testVBO);
    glBindBuffer(GL_ARRAY_BUFFER, testVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexAndTexturePos), vertexAndTexturePos, GL_STATIC_DRAW);

    glGenBuffers(1, &testEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, testEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elementIndices), elementIndices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (void*)(0));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (void*)(sizeof(GLfloat) * 3));
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (void*)(sizeof(GLfloat) * 5));

    // Images

    makeTexture(getImageFormat("../assets/images/awesomeface.png"));
    makeTexture(getImageFormat("../assets/images/subaru1.jpg"));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // Creating new objects here!
    std::vector<std::string> modelPaths = {
        "../assets/models/4D.obj",
    };

    for (std::string& path : modelPaths) {
        std::unique_ptr<AssimpObject> object = std::make_unique<AssimpObject>(path);

        modelObjects.push_back(std::move(object));
    }

    // Trying out SSBO
    GLuint textureHandleSSBO;
    glGenBuffers(1, &textureHandleSSBO);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, textureHandleSSBO);
    glBufferData(GL_SHADER_STORAGE_BUFFER, AssimpObject::textureHandles.size() * sizeof(GLuint64),
                 AssimpObject::textureHandles.data(), GL_STATIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, textureHandleSSBO);

    std::cout << "Game initialzied.\n";
}

void App::handleEvent(const SDL_Event& event) {
    switch (event.type) {
        case SDL_EVENT_MOUSE_WHEEL:

            if (event.wheel.y > 0) {
                fov -= 5.0f;

            } else if (event.wheel.y < 0) {
                fov += 5.0f;
            }
            if (fov > 120) {
                fov = 120;
            }
            if (fov <= 1) {
                fov = 1;
            }
            camera.changefov(fov);
            break;
        default:
            break;
    }
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
        move_straight -= 0.5f;
        std::cout << "move : " << move_straight << "\n";
    } else if (keyboardstate[SDL_SCANCODE_DOWN]) {
        move_straight += 0.5f;
        std::cout << "move : " << move_straight << "\n";
    }
    glUseProgram(shaderProgram);
    GLuint getAmbientLightUniformLocation = glGetUniformLocation(shaderProgram, "ambientLight");
    glm::vec4 ambientLight(0.15f, 0.15f, 0.15f, 1.0f);
    glUniform4fv(getAmbientLightUniformLocation, 1, glm::value_ptr(ambientLight));

    GLuint getLightPositionUniformLocation = glGetUniformLocation(shaderProgram, "lightPosition");
    glm::vec3 lightPosition(0.0f, -5.0f, 0);
    glUniform3fv(getLightPositionUniformLocation, 1, glm::value_ptr(lightPosition));

    GLuint getEyePositionWorldLocation = glGetUniformLocation(shaderProgram, "eyePositionWorld");
    glUniform3fv(getEyePositionWorldLocation, 1, glm::value_ptr(camera.getPosition()));
}

void App::render() {
    GLuint getModelToWorldProjectionMatrix = glGetUniformLocation(shaderProgram, "modelToWorldProjectionMatrix");
    GLuint getmodelToWorldTransformationMatrix = glGetUniformLocation(shaderProgram, "modelToWorldTransformMatrix");

    // Cube
    glBindVertexArray(cubeVertexArrayID);
    glm::mat4 cubeToWorldMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(3.5f, +0.0f, -2.0f)) /** glm::scale(glm::mat4(1.0f), glm::vec3(5.0f, 0.5f, 0.5f))*/;
    glm::mat4 MatrixGangUwu = camera.getProjectionMatrix() * camera.getWorldToViewMatrix() * cubeToWorldMatrix;
    glUniformMatrix4fv(getModelToWorldProjectionMatrix, 1, GL_FALSE, glm::value_ptr(MatrixGangUwu));
    glUniformMatrix4fv(getmodelToWorldTransformationMatrix, 1, GL_FALSE, glm::value_ptr(cubeToWorldMatrix));
    glDrawElements(GL_TRIANGLES, CubeShape.num_indices, GL_UNSIGNED_SHORT, 0);

    glBindVertexArray(cubeVertexArrayID);
    cubeToWorldMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-3.5f, +0.0f, -2.0f));
    MatrixGangUwu = camera.getProjectionMatrix() * camera.getWorldToViewMatrix() * cubeToWorldMatrix;
    glUniformMatrix4fv(getModelToWorldProjectionMatrix, 1, GL_FALSE, glm::value_ptr(MatrixGangUwu));
    glUniformMatrix4fv(getmodelToWorldTransformationMatrix, 1, GL_FALSE, glm::value_ptr(cubeToWorldMatrix));
    glDrawElements(GL_TRIANGLES, CubeShape.num_indices, GL_UNSIGNED_SHORT, 0);

    // Arrow
    glBindVertexArray(arrowVertexArrayID);
    glm::mat4 arrowToWorldMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-6.5f, +0.0f, -2.0f));
    MatrixGangUwu = camera.getProjectionMatrix() * camera.getWorldToViewMatrix() * arrowToWorldMatrix;
    glUniformMatrix4fv(getModelToWorldProjectionMatrix, 1, GL_FALSE, glm::value_ptr(MatrixGangUwu));
    glUniformMatrix4fv(getmodelToWorldTransformationMatrix, 1, GL_FALSE, glm::value_ptr(arrowToWorldMatrix));
    glDrawElements(GL_TRIANGLES, ArrowShape.num_indices, GL_UNSIGNED_SHORT, (void*)(CubeShape.getIndiceBufferSize()));

    // New objects made

    glUseProgram(testShaders);

    for (const auto& model : modelObjects) {
        glBindVertexArray(model->VAO);
        glm::mat4 testObjectToWorld = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));
        glm::mat4 testModelToWorldMatrix = camera.getProjectionMatrix() * camera.getWorldToViewMatrix() * testObjectToWorld;

        GLint loc1 = glGetUniformLocation(testShaders, "MVP");

        if (loc1 == -1) {
            std::cout << "Uniform lcoation is not active!" << "\n";
        }
        glUniformMatrix4fv(loc1, 1, GL_FALSE, glm::value_ptr(testModelToWorldMatrix));

        glUniform1uiv(glGetUniformLocation(testShaders, "textureIndices"), static_cast<GLsizei>(model->imageIndices.size()), model->imageIndices.data());

        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(model->globalIndices.size()), GL_UNSIGNED_INT, (void*)(0));
    }

    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL Error: " << err << std::endl;
    }

    glBindVertexArray(0);
}

void App::cleanup() {
    // generateObject.cleanup();
    CubeShape.cleanup();
    ArrowShape.cleanup();
    // delete cube;
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteVertexArrays(1, &cubeVertexArrayID);
    glDeleteVertexArrays(1, &arrowVertexArrayID);
    glDeleteBuffers(1, &theVertexBufferID);
    glDeleteBuffers(1, &theIndexBufferID);
    glDeleteProgram(shaderProgram);
    std::cout << "Cleanup done.\n";
}
