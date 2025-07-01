#include "app.hpp"

const int VERTEX_BYTE_SIZE = 9;
/*
    BUFFER OVERVIEW GL_ARRAY_BUFFER : CUBEBUFFERSIZE | ARROWBUFFERSIZE
    BUFFER OVERVIEW GL_ELEMENT_ARRAY_BUFFER : CUBEINDICESIZE | ARROWINDICESIZE
*/

ObjectGenerator generateObject;

void App::init() {
    GLuint grid = generateObject.uploadImg("../assets/images/uv_grid_opengl.jpg");
    GLuint subaru = generateObject.uploadImg("../assets/images/subaru1.jpg");

    glm::vec2 kan = generateObject.uploadObj("../assets/objects/plane.obj", GL_STATIC_DRAW);
    generateObject.attach(kan, grid, false);
    generateObject.transform(kan, glm::vec3(+0.0f, +2.0f, -4.0f));

    glm::vec2 platform1 = generateObject.uploadObj("../assets/objects/platform.obj", GL_STATIC_DRAW);
    generateObject.attach(platform1, subaru, false);
    generateObject.transform(platform1, glm::vec3(+0.0f, -5.0f, +0.0f));

    glm::vec2 platform2 = generateObject.uploadObj("../assets/objects/platform.obj", GL_STATIC_DRAW);
    generateObject.attach(platform2, subaru, false);
    generateObject.transform(platform2, glm::vec3(+20.0f, -5.0f, +0.0f));

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

    glUseProgram(testShaders);

    glm::vec3 pointLightPositions[4] = {
        glm::vec3(+0.7f, +2.0f, move_straight),
        glm::vec3(+2.3f, +2.0f, move_straight),
        glm::vec3(-4.0f, +2.0f, move_straight),
        glm::vec3(+0.0f, +2.0f, -move_straight)};

    // for (const auto& object : generateObject.getDynamicMeshes()) {
    //     glBindVertexArray(object.VAO);
    //     glActiveTexture(GL_TEXTURE0);
    //     glBindTexture(GL_TEXTURE_2D, object.texture0);
    //     glActiveTexture(GL_TEXTURE1);
    //     glBindTexture(GL_TEXTURE_2D, object.texture1);

    //     glUniform1i(glGetUniformLocation(testShaders, "material.diffuse"), 0);
    //     glUniform1i(glGetUniformLocation(testShaders, "material.specular"), 1);

    //     glUniform3fv(glGetUniformLocation(testShaders, "dirLight.direction"), 1, glm::value_ptr(glm::vec3(0.0f, move_straight, 0.0f)));
    //     glUniform3fv(glGetUniformLocation(testShaders, "dirLight.ambient"), 1, glm::value_ptr(glm::vec3(0.1f, 0.1f, 0.1f)));
    //     glUniform3fv(glGetUniformLocation(testShaders, "dirLight.diffuse"), 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
    //     glUniform3fv(glGetUniformLocation(testShaders, "dirLight.specular"), 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));

    //     glUniform1f(glGetUniformLocation(testShaders, "material.shininess"), 32.0f);
    //     glUniform3fv(glGetUniformLocation(testShaders, "pointLights[0].position"), 1, glm::value_ptr(pointLightPositions[0]));
    //     glUniform3fv(glGetUniformLocation(testShaders, "pointLights[1].position"), 1, glm::value_ptr(pointLightPositions[1]));
    //     glUniform3fv(glGetUniformLocation(testShaders, "pointLights[2].position"), 1, glm::value_ptr(pointLightPositions[2]));
    //     glUniform3fv(glGetUniformLocation(testShaders, "pointLights[3].position"), 1, glm::value_ptr(pointLightPositions[3]));

    //     glUniform1f(glGetUniformLocation(testShaders, "pointLights[0].constant"), 1.0f);
    //     glUniform1f(glGetUniformLocation(testShaders, "pointLights[1].constant"), 1.0f);
    //     glUniform1f(glGetUniformLocation(testShaders, "pointLights[2].constant"), 1.0f);
    //     glUniform1f(glGetUniformLocation(testShaders, "pointLights[3].constant"), 1.0f);

    //     glUniform1f(glGetUniformLocation(testShaders, "pointLights[0].linear"), 0.09f);
    //     glUniform1f(glGetUniformLocation(testShaders, "pointLights[1].linear"), 0.09f);
    //     glUniform1f(glGetUniformLocation(testShaders, "pointLights[2].linear"), 0.09f);
    //     glUniform1f(glGetUniformLocation(testShaders, "pointLights[3].linear"), 0.09f);

    //     glUniform1f(glGetUniformLocation(testShaders, "pointLights[0].quadratic"), 0.032f);
    //     glUniform1f(glGetUniformLocation(testShaders, "pointLights[1].quadratic"), 0.032f);
    //     glUniform1f(glGetUniformLocation(testShaders, "pointLights[2].quadratic"), 0.032f);
    //     glUniform1f(glGetUniformLocation(testShaders, "pointLights[3].quadratic"), 0.032f);

    //     glUniform3fv(glGetUniformLocation(testShaders, "pointLights[0].ambient"), 1, glm::value_ptr(glm::vec3(0.2f, 0.2f, 0.2f)));
    //     glUniform3fv(glGetUniformLocation(testShaders, "pointLights[1].ambient"), 1, glm::value_ptr(glm::vec3(0.2f, 0.2f, 0.2f)));
    //     glUniform3fv(glGetUniformLocation(testShaders, "pointLights[2].ambient"), 1, glm::value_ptr(glm::vec3(0.2f, 0.2f, 0.2f)));
    //     glUniform3fv(glGetUniformLocation(testShaders, "pointLights[3].ambient"), 1, glm::value_ptr(glm::vec3(0.2f, 0.2f, 0.2f)));

    //     glUniform3fv(glGetUniformLocation(testShaders, "pointLights[0].diffuse"), 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
    //     glUniform3fv(glGetUniformLocation(testShaders, "pointLights[1].diffuse"), 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
    //     glUniform3fv(glGetUniformLocation(testShaders, "pointLights[2].diffuse"), 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
    //     glUniform3fv(glGetUniformLocation(testShaders, "pointLights[3].diffuse"), 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));

    //     glUniform3fv(glGetUniformLocation(testShaders, "pointLights[0].specular"), 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
    //     glUniform3fv(glGetUniformLocation(testShaders, "pointLights[1].specular"), 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
    //     glUniform3fv(glGetUniformLocation(testShaders, "pointLights[2].specular"), 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
    //     glUniform3fv(glGetUniformLocation(testShaders, "pointLights[3].specular"), 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));

    //     glUniform3fv(glGetUniformLocation(testShaders, "spotLight.position"), 1, glm::value_ptr(camera.getPosition()));
    //     glUniform3fv(glGetUniformLocation(testShaders, "spotLight.direction"), 1, glm::value_ptr(camera.getViewDirection()));

    //     // GLint location = glGetUniformLocation(testShaders, "spotLight.direction");
    //     // if (location == -1) {
    //     //     std::cout << "Uniform 'spotLight.direction' not found or not active!" << std::endl;
    //     // }
    //     // std::cout << "View Direction : " << camera.getViewDirection().z << "\n";
    //     glUniform1f(glGetUniformLocation(testShaders, "spotLight.cutOff"), glm::cos(glm::radians(12.5f)));
    //     glUniform1f(glGetUniformLocation(testShaders, "spotLight.outerCutOff"), glm::cos(glm::radians(17.5f)));
    //     glUniform3fv(glGetUniformLocation(testShaders, "spotLight.ambient"), 1, glm::value_ptr(glm::vec3(0.2f, 0.2f, 0.2f)));
    //     glUniform3fv(glGetUniformLocation(testShaders, "spotLight.diffuse"), 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
    //     glUniform3fv(glGetUniformLocation(testShaders, "spotLight.specular"), 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
    //     glUniform1f(glGetUniformLocation(testShaders, "spotLight.constant"), 1.0f);
    //     glUniform1f(glGetUniformLocation(testShaders, "spotLight.linear"), 0.09f);
    //     glUniform1f(glGetUniformLocation(testShaders, "spotLight.quadratic"), 0.032f);

    //     glUniform3fv(glGetUniformLocation(testShaders, "viewPosition"), 1, glm::value_ptr(camera.getPosition()));

    //     glm::mat4 modelToWorldMatrix = camera.getProjectionMatrix() * camera.getWorldToViewMatrix() * object.objToWorldMatrix;
    //     glUniformMatrix4fv(glGetUniformLocation(testShaders, "modelToWorldProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(modelToWorldMatrix));
    //     glUniformMatrix4fv(glGetUniformLocation(testShaders, "modelToWorldTransformation"), 1, GL_FALSE, glm::value_ptr(object.objToWorldMatrix));
    //     glDrawElements(GL_TRIANGLES, object.indexCount, GL_UNSIGNED_INT, 0);
    // }

    glBindVertexArray(generateObject.getStaticVao());

    for (auto& object : generateObject.getStaticMeshes()) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, object.texture0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, object.texture1);

        glUniform1i(glGetUniformLocation(testShaders, "material.diffuse"), 0);
        glUniform1i(glGetUniformLocation(testShaders, "material.specular"), 1);

        glUniform3fv(glGetUniformLocation(testShaders, "dirLight.direction"), 1, glm::value_ptr(glm::vec3(0.0f, move_straight, 0.0f)));
        glUniform3fv(glGetUniformLocation(testShaders, "dirLight.ambient"), 1, glm::value_ptr(glm::vec3(0.1f, 0.1f, 0.1f)));
        glUniform3fv(glGetUniformLocation(testShaders, "dirLight.diffuse"), 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
        glUniform3fv(glGetUniformLocation(testShaders, "dirLight.specular"), 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));

        glUniform1f(glGetUniformLocation(testShaders, "material.shininess"), 32.0f);
        glUniform3fv(glGetUniformLocation(testShaders, "pointLights[0].position"), 1, glm::value_ptr(pointLightPositions[0]));
        glUniform3fv(glGetUniformLocation(testShaders, "pointLights[1].position"), 1, glm::value_ptr(pointLightPositions[1]));
        glUniform3fv(glGetUniformLocation(testShaders, "pointLights[2].position"), 1, glm::value_ptr(pointLightPositions[2]));
        glUniform3fv(glGetUniformLocation(testShaders, "pointLights[3].position"), 1, glm::value_ptr(pointLightPositions[3]));

        glUniform1f(glGetUniformLocation(testShaders, "pointLights[0].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(testShaders, "pointLights[1].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(testShaders, "pointLights[2].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(testShaders, "pointLights[3].constant"), 1.0f);

        glUniform1f(glGetUniformLocation(testShaders, "pointLights[0].linear"), 0.09f);
        glUniform1f(glGetUniformLocation(testShaders, "pointLights[1].linear"), 0.09f);
        glUniform1f(glGetUniformLocation(testShaders, "pointLights[2].linear"), 0.09f);
        glUniform1f(glGetUniformLocation(testShaders, "pointLights[3].linear"), 0.09f);

        glUniform1f(glGetUniformLocation(testShaders, "pointLights[0].quadratic"), 0.032f);
        glUniform1f(glGetUniformLocation(testShaders, "pointLights[1].quadratic"), 0.032f);
        glUniform1f(glGetUniformLocation(testShaders, "pointLights[2].quadratic"), 0.032f);
        glUniform1f(glGetUniformLocation(testShaders, "pointLights[3].quadratic"), 0.032f);

        glUniform3fv(glGetUniformLocation(testShaders, "pointLights[0].ambient"), 1, glm::value_ptr(glm::vec3(0.2f, 0.2f, 0.2f)));
        glUniform3fv(glGetUniformLocation(testShaders, "pointLights[1].ambient"), 1, glm::value_ptr(glm::vec3(0.2f, 0.2f, 0.2f)));
        glUniform3fv(glGetUniformLocation(testShaders, "pointLights[2].ambient"), 1, glm::value_ptr(glm::vec3(0.2f, 0.2f, 0.2f)));
        glUniform3fv(glGetUniformLocation(testShaders, "pointLights[3].ambient"), 1, glm::value_ptr(glm::vec3(0.2f, 0.2f, 0.2f)));

        glUniform3fv(glGetUniformLocation(testShaders, "pointLights[0].diffuse"), 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
        glUniform3fv(glGetUniformLocation(testShaders, "pointLights[1].diffuse"), 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
        glUniform3fv(glGetUniformLocation(testShaders, "pointLights[2].diffuse"), 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
        glUniform3fv(glGetUniformLocation(testShaders, "pointLights[3].diffuse"), 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));

        glUniform3fv(glGetUniformLocation(testShaders, "pointLights[0].specular"), 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
        glUniform3fv(glGetUniformLocation(testShaders, "pointLights[1].specular"), 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
        glUniform3fv(glGetUniformLocation(testShaders, "pointLights[2].specular"), 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
        glUniform3fv(glGetUniformLocation(testShaders, "pointLights[3].specular"), 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));

        glUniform3fv(glGetUniformLocation(testShaders, "spotLight.position"), 1, glm::value_ptr(camera.getPosition()));
        glUniform3fv(glGetUniformLocation(testShaders, "spotLight.direction"), 1, glm::value_ptr(camera.getViewDirection()));

        glUniform1f(glGetUniformLocation(testShaders, "spotLight.cutOff"), glm::cos(glm::radians(12.5f)));
        glUniform1f(glGetUniformLocation(testShaders, "spotLight.outerCutOff"), glm::cos(glm::radians(17.5f)));
        glUniform3fv(glGetUniformLocation(testShaders, "spotLight.ambient"), 1, glm::value_ptr(glm::vec3(0.2f, 0.2f, 0.2f)));
        glUniform3fv(glGetUniformLocation(testShaders, "spotLight.diffuse"), 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
        glUniform3fv(glGetUniformLocation(testShaders, "spotLight.specular"), 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
        glUniform1f(glGetUniformLocation(testShaders, "spotLight.constant"), 1.0f);
        glUniform1f(glGetUniformLocation(testShaders, "spotLight.linear"), 0.09f);
        glUniform1f(glGetUniformLocation(testShaders, "spotLight.quadratic"), 0.032f);

        glUniform3fv(glGetUniformLocation(testShaders, "viewPosition"), 1, glm::value_ptr(camera.getPosition()));

        glm::mat4 modelToWorldMatrix = camera.getProjectionMatrix() * camera.getWorldToViewMatrix() * object.objToWorldMatrix;
        glUniformMatrix4fv(glGetUniformLocation(testShaders, "modelToWorldProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(modelToWorldMatrix));
        glUniformMatrix4fv(glGetUniformLocation(testShaders, "modelToWorldTransformation"), 1, GL_FALSE, glm::value_ptr(object.objToWorldMatrix));
        glDrawElementsBaseVertex(GL_TRIANGLES, object.indexCount, GL_UNSIGNED_INT, (void*)(object.baseIndex * sizeof(GLuint)), object.baseVertex);
    }

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
