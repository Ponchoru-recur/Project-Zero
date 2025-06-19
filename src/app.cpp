#include "app.hpp"

const int VERTEX_BYTE_SIZE = 9;
/*
    BUFFER OVERVIEW GL_ARRAY_BUFFER : CUBEBUFFERSIZE | ARROWBUFFERSIZE
    BUFFER OVERVIEW GL_ELEMENT_ARRAY_BUFFER : CUBEINDICESIZE | ARROWINDICESIZE
*/

ObjectGenerator generateObject;

void App::processMesh(aiMesh* mesh) {
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        // Position
        vertices.push_back(mesh->mVertices[i].x);
        vertices.push_back(mesh->mVertices[i].y);
        vertices.push_back(mesh->mVertices[i].z);

        // Normals (optional)
        if (mesh->HasNormals()) {
            vertices.push_back(mesh->mNormals[i].x);
            vertices.push_back(mesh->mNormals[i].y);
            vertices.push_back(mesh->mNormals[i].z);
        } else {
            vertices.push_back(0.0f);  // Fallback normal
            vertices.push_back(0.0f);
            vertices.push_back(1.0f);
        }

        // Vertex Colors (optional)
        if (mesh->HasVertexColors(0)) {
            vertices.push_back(mesh->mColors[0][i].r);
            vertices.push_back(mesh->mColors[0][i].g);
            vertices.push_back(mesh->mColors[0][i].b);
            // Optional alpha
            // vertices.push_back(mesh->mColors[0][i].a);
        } else {
            vertices.push_back(1.0f);  // Fallback white
            vertices.push_back(1.0f);
            vertices.push_back(1.0f);
        }
    }
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }
}

void App::processNode(aiNode* node, const aiScene* scene) {
    // Process all the node’s meshes
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        processMesh(mesh);
    }

    // Recursively process children
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}

void App::init() {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile("../assets/objects/platform.obj", aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_GenNormals);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "Assimp error: " << importer.GetErrorString() << std::endl;
    }

    processNode(scene->mRootNode, scene);

    generateObject.uploadObj("../assets/objects/kan.obj");
    // generateObject.uploadObj("../assets/objects/platform.obj");

    // Important! Init the shaders first!
    std::string vertexShaderSource = Shader::LoadShaderFileSource("../shaders/vertexShader.vs");
    std::string fragmentShaderSource = Shader::LoadShaderFileSource("../shaders/fragmentShader.fs");
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
    glGenVertexArrays(1, &SceneVertexArrayID);
    glBindVertexArray(SceneVertexArrayID);

    glGenBuffers(1, &SceneVertexBufferID);
    glGenBuffers(1, &SceneElementBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, SceneVertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, (vertices.size() * sizeof(GLfloat)), vertices.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 9, 0);                             // Position
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 9, (void*)(sizeof(GLfloat) * 6));  // Color
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 9, (void*)(sizeof(GLfloat) * 3));  // Normals
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, SceneElementBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (indices.size() * sizeof(GLuint)), indices.data(), GL_STATIC_DRAW);
    // END

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

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
    glm::vec3 lightPosition(0.0f, 2.0f, move_straight);
    glUniform3fv(getLightPositionUniformLocation, 1, glm::value_ptr(lightPosition));

    GLuint getEyePositionWorldLocation = glGetUniformLocation(shaderProgram, "eyePositionWorld");
    glUniform3fv(getEyePositionWorldLocation, 1, glm::value_ptr(camera.getPosition()));

    GLuint getscaleTheModelLocation = glGetUniformLocation(shaderProgram, "scaleTheModel");
    glUniform1f(getscaleTheModelLocation, 1);
}

void App::render() {
    GLuint getModelToWorldProjectionMatrix = glGetUniformLocation(shaderProgram, "modelToWorldProjectionMatrix");
    GLuint getmodelToWorldTransformationMatrix = glGetUniformLocation(shaderProgram, "modelToWorldTransformMatrix");

    // Cube
    glBindVertexArray(cubeVertexArrayID);
    glm::mat4 cubeToWorldMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(3.5f, +0.0f, -2.0f));
    glm::mat4 MatrixGangUwu = projectionMatrix * camera.getWorldToViewMatrix() * cubeToWorldMatrix;
    glUniformMatrix4fv(getModelToWorldProjectionMatrix, 1, GL_FALSE, glm::value_ptr(MatrixGangUwu));
    glUniformMatrix4fv(getmodelToWorldTransformationMatrix, 1, GL_FALSE, glm::value_ptr(cubeToWorldMatrix));
    glDrawElements(GL_TRIANGLES, CubeShape.num_indices, GL_UNSIGNED_SHORT, 0);

    glBindVertexArray(cubeVertexArrayID);
    cubeToWorldMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-3.5f, +0.0f, -2.0f));
    MatrixGangUwu = projectionMatrix * camera.getWorldToViewMatrix() * cubeToWorldMatrix;
    glUniformMatrix4fv(getModelToWorldProjectionMatrix, 1, GL_FALSE, glm::value_ptr(MatrixGangUwu));
    glUniformMatrix4fv(getmodelToWorldTransformationMatrix, 1, GL_FALSE, glm::value_ptr(cubeToWorldMatrix));
    glDrawElements(GL_TRIANGLES, CubeShape.num_indices, GL_UNSIGNED_SHORT, 0);

    // Arrow
    glBindVertexArray(arrowVertexArrayID);
    glm::mat4 arrowToWorldMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-6.5f, +0.0f, -2.0f));
    MatrixGangUwu = projectionMatrix * camera.getWorldToViewMatrix() * arrowToWorldMatrix;
    glUniformMatrix4fv(getModelToWorldProjectionMatrix, 1, GL_FALSE, glm::value_ptr(MatrixGangUwu));
    glUniformMatrix4fv(getmodelToWorldTransformationMatrix, 1, GL_FALSE, glm::value_ptr(arrowToWorldMatrix));
    glDrawElements(GL_TRIANGLES, ArrowShape.num_indices, GL_UNSIGNED_SHORT, (void*)(CubeShape.getIndiceBufferSize()));

    glBindVertexArray(SceneVertexArrayID);
    glm::mat4 sceneToWorldMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(+0.0f, -5.0f, +0.0f));
    MatrixGangUwu = projectionMatrix * camera.getWorldToViewMatrix() * sceneToWorldMatrix;
    glUniformMatrix4fv(getModelToWorldProjectionMatrix, 1, GL_FALSE, glm::value_ptr(MatrixGangUwu));
    glUniformMatrix4fv(getmodelToWorldTransformationMatrix, 1, GL_FALSE, glm::value_ptr(sceneToWorldMatrix));
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    for (const auto& object : generateObject.getinfo()) {
        glBindVertexArray(object.VAO);
        glm::mat4 objectToWorldMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(+0.0f, +2.0f, +0.0f));
        MatrixGangUwu = projectionMatrix * camera.getWorldToViewMatrix() * objectToWorldMatrix;
        glUniformMatrix4fv(getModelToWorldProjectionMatrix, 1, GL_FALSE, glm::value_ptr(MatrixGangUwu));
        glUniformMatrix4fv(getmodelToWorldTransformationMatrix, 1, GL_FALSE, glm::value_ptr(objectToWorldMatrix));
        glDrawElements(GL_TRIANGLES, object.indexCount, GL_UNSIGNED_INT, 0);
    }

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
