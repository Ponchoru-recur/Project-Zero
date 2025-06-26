#include "app.hpp"

const int VERTEX_BYTE_SIZE = 9;
/*
    BUFFER OVERVIEW GL_ARRAY_BUFFER : CUBEBUFFERSIZE | ARROWBUFFERSIZE
    BUFFER OVERVIEW GL_ELEMENT_ARRAY_BUFFER : CUBEINDICESIZE | ARROWINDICESIZE
*/

ObjectGenerator generateObject;

void App::init() {
    glm::vec2 kan = generateObject.uploadObj("../assets/objects/kan.obj", GL_STATIC_DRAW);
    generateObject.transform(kan, glm::vec3(+0.0f, +2.0f, -4.0f));

    glm::vec2 platform = generateObject.uploadObj("../assets/objects/platform.obj", GL_DYNAMIC_DRAW);
    generateObject.transform(platform, glm::vec3(+0.0f, -5.0f, +0.0f));

    generateObject.process();

    // Important! Init the shaders first!
    std::string vertexShaderSource = Shader::LoadShaderFileSource("../shaders/vertexShader.vs");
    std::string fragmentShaderSource = Shader::LoadShaderFileSource("../shaders/fragmentShader.fs");
    GLuint vertShader = Shader::compileShader(vertexShaderSource, GL_VERTEX_SHADER);
    GLuint fragShader = Shader::compileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
    shaderProgram = Shader::linkProgram(vertShader, fragShader);

    // Important! | TEST SHADERS |
    std::string testVertSource = Shader::LoadShaderFileSource("../shaders/testVert.vs");
    std::string testFragSource = Shader::LoadShaderFileSource("../shaders/testFrag.fs");
    GLuint testVert = Shader::compileShader(testVertSource, GL_VERTEX_SHADER);
    GLuint testFrag = Shader::compileShader(testFragSource, GL_FRAGMENT_SHADER);
    testShaders = Shader::linkProgram(testVert, testFrag);

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

    // | TEST OBJECT |

    SDL_Surface* surface1 = IMG_Load("../assets/images/container2.png");
    if (!surface1) {
        SDL_Log("Couldn't load img Error : %s", SDL_GetError());
    }

    SDL_Surface* formatted1 = SDL_ConvertSurface(surface1, SDL_PIXELFORMAT_RGBA32);
    SDL_DestroySurface(surface1);

    SDL_Surface* surface2 = IMG_Load("../assets/images/container2_specular.png");
    if (!surface2) {
        SDL_Log("Couldn't load img Error : %s", SDL_GetError());
    }

    SDL_Surface* formatted2 = SDL_ConvertSurface(surface2, SDL_PIXELFORMAT_RGBA32);
    SDL_DestroySurface(surface2);

    SDL_Surface* surface3 = IMG_Load("../assets/images/lighting_maps_specular_color.png");
    if (!surface2) {
        SDL_Log("Couldn't load img Error : %s", SDL_GetError());
    }

    SDL_Surface* formatted3 = SDL_ConvertSurface(surface3, SDL_PIXELFORMAT_RGBA32);
    SDL_DestroySurface(surface3);

    glm::vec3 verts[] = {
        // position
        glm::vec3(+1.0f, +1.0f, +0.0f),
        glm::vec3(-1.0f, -1.0f, +0.0f),
        glm::vec3(+1.0f, -1.0f, +0.0f),

        glm::vec3(+1.0f, +1.0f, +0.0f),
        glm::vec3(-1.0f, -1.0f, +0.0f),
        glm::vec3(-1.0f, +1.0f, +0.0f)};

    glm::vec3 normals[] = {glm::vec3(+0.0f, +0.0f, +1.0f),
                           glm::vec3(+0.0f, +0.0f, +1.0f),
                           glm::vec3(+0.0f, +0.0f, +1.0f),
                           glm::vec3(+0.0f, +0.0f, +1.0f),
                           glm::vec3(+0.0f, +0.0f, +1.0f),
                           glm::vec3(+0.0f, +0.0f, +1.0f)

    };

    glm::vec2 textCoords[]{
        glm::vec2(+1.0f, +1.0f),
        glm::vec2(-0.0f, -0.0f),
        glm::vec2(+1.0f, -0.0f),

        glm::vec2(+1.0f, +1.0f),
        glm::vec2(-0.0f, -0.0f),
        glm::vec2(-0.0f, +1.0f)};

    glm::vec3 colors[] = {glm::vec3(1.0f, 1.0f, 1.0f)};

    GLuint indices[] = {0, 1, 2,
                        5, 4, 3};

    glGenVertexArrays(1, &testVertexArray);
    glBindVertexArray(testVertexArray);

    glGenBuffers(1, &testVertBufferObj);
    glGenBuffers(1, &testIndiceBufferObj);

    glBindBuffer(GL_ARRAY_BUFFER, testVertBufferObj);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts) + sizeof(normals) + sizeof(textCoords) + sizeof(colors), 0, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verts), verts);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(verts), sizeof(normals), normals);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(verts) + sizeof(normals), sizeof(textCoords), textCoords);
    glEnableVertexAttribArray(0);  // Position
    glEnableVertexAttribArray(1);  // normals
    glEnableVertexAttribArray(2);  // Texture Coordinates
    // glEnableVertexAttribArray(3);  // Color
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)(0));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(verts)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(verts) + sizeof(normals)));
    // glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(verts) + sizeof(textCoords) + sizeof(colors)));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, testIndiceBufferObj);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glGenTextures(1, &testTexture1);
    glBindTexture(GL_TEXTURE_2D, testTexture1);
    // set the texture wrapping / filtering options(on the currently bound texture object) glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, formatted1->w, formatted1->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, formatted1->pixels);
    glGenerateMipmap(GL_TEXTURE_2D);
    SDL_DestroySurface(formatted1);

    glBindTexture(GL_TEXTURE_2D, 0);

    glGenTextures(1, &testTexture2);
    glBindTexture(GL_TEXTURE_2D, testTexture2);
    // set the texture wrapping / filtering options(on the currently bound texture object) glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, formatted2->w, formatted2->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, formatted2->pixels);
    glGenerateMipmap(GL_TEXTURE_2D);
    SDL_DestroySurface(formatted2);

    glGenTextures(1, &testTexture3);
    glBindTexture(GL_TEXTURE_2D, testTexture3);
    // set the texture wrapping / filtering options(on the currently bound texture object) glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, formatted3->w, formatted3->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, formatted3->pixels);
    glGenerateMipmap(GL_TEXTURE_2D);
    SDL_DestroySurface(formatted3);

    glBindTexture(GL_TEXTURE_2D, 0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

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
    glm::mat4 cubeToWorldMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(3.5f, +0.0f, -2.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(5.0f, 0.5f, 0.5f));
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

    for (const auto& object : generateObject.getDynamicMeshes()) {
        glBindVertexArray(object.VAO);
        MatrixGangUwu = camera.getProjectionMatrix() * camera.getWorldToViewMatrix() * object.objToWorldMatrix;
        glUniformMatrix4fv(getModelToWorldProjectionMatrix, 1, GL_FALSE, glm::value_ptr(MatrixGangUwu));
        glUniformMatrix4fv(getmodelToWorldTransformationMatrix, 1, GL_FALSE, glm::value_ptr(object.objToWorldMatrix));
        glDrawElements(GL_TRIANGLES, object.indexCount, GL_UNSIGNED_INT, 0);
    }

    glBindVertexArray(generateObject.getStaticVao());
    for (auto& object : generateObject.getStaticMeshes()) {
        MatrixGangUwu = camera.getProjectionMatrix() * camera.getWorldToViewMatrix() * object.objToWorldMatrix;
        glUniformMatrix4fv(getModelToWorldProjectionMatrix, 1, GL_FALSE, glm::value_ptr(MatrixGangUwu));
        glDrawElementsBaseVertex(GL_TRIANGLES, object.indexCount, GL_UNSIGNED_INT, (void*)(object.baseIndex * sizeof(GLuint)), object.baseVertex);
    }

    /* | TESTING | */

    glUseProgram(testShaders);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, testTexture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, testTexture2);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, testTexture3);

    glBindVertexArray(testVertexArray);
    glm::mat4 modelTransformMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(5.0f, 5.0f, 5.0f));
    glm::mat4 modelToWorldMatrix = camera.getProjectionMatrix() * camera.getWorldToViewMatrix() * modelTransformMatrix;

    glUniformMatrix4fv(glGetUniformLocation(testShaders, "modelToWorldProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(modelToWorldMatrix));
    glUniformMatrix4fv(glGetUniformLocation(testShaders, "modelToWorldTransformation"), 1, GL_FALSE, glm::value_ptr(modelTransformMatrix));
    glUniform1i(glGetUniformLocation(testShaders, "material.diffuse"), 0);
    glUniform1i(glGetUniformLocation(testShaders, "material.specular"), 1);
    glUniform1i(glGetUniformLocation(testShaders, "emissionMap"), 2);
    glUniform1f(glGetUniformLocation(testShaders, "material.shininess"), 32.0f);
    glUniform3fv(glGetUniformLocation(testShaders, "light.position"), 1, glm::value_ptr(glm::vec3(-0.2f, -1.0f, move_straight)));
    glUniform3fv(glGetUniformLocation(testShaders, "light.ambient"), 1, glm::value_ptr(glm::vec3(0.2f, 0.2f, 0.2f)));
    glUniform3fv(glGetUniformLocation(testShaders, "light.diffuse"), 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
    glUniform3fv(glGetUniformLocation(testShaders, "light.specular"), 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
    glUniform3fv(glGetUniformLocation(testShaders, "viewPosition"), 1, glm::value_ptr(camera.getPosition()));

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(0));
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL Error: " << err << std::endl;
    }

    glBindVertexArray(0);
}

void App::cleanup() {
    generateObject.cleanup();
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
