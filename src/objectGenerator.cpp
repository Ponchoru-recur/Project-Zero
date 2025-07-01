#include "objectGenerator.hpp"

namespace objectProcess {
void processNode(aiNode* node, const aiScene* scene, std::vector<Vortex>& interleavedData, std::vector<GLuint>& indices);
void processMesh(aiMesh* mesh, std::vector<Vortex>& interleavedData, std::vector<GLuint>& indices);
};  // namespace objectProcess

void objectProcess::processNode(aiNode* node, const aiScene* scene, std::vector<Vortex>& interleavedData, std::vector<GLuint>& indices) {
    // Process all the node’s meshes
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        processMesh(mesh, interleavedData, indices);
    }

    // Recursively process children
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene, interleavedData, indices);
    }
}

void objectProcess::processMesh(aiMesh* mesh, std::vector<Vortex>& interleavedData, std::vector<GLuint>& indices) {
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vortex interleavedPass{};
        // Position
        interleavedPass.Positions.x = (mesh->mVertices[i].x);
        interleavedPass.Positions.y = (mesh->mVertices[i].y);
        interleavedPass.Positions.z = (mesh->mVertices[i].z);

        // Normals (optional)
        if (mesh->HasNormals()) {
            interleavedPass.Normals.x = (mesh->mNormals[i].x);
            interleavedPass.Normals.y = (mesh->mNormals[i].y);
            interleavedPass.Normals.z = (mesh->mNormals[i].z);
        } else {
            interleavedPass.Normals.x = (0.0f);  // Fallback normal
            interleavedPass.Normals.y = (0.0f);
            interleavedPass.Normals.z = (1.0f);
        }

        if (mesh->HasTextureCoords(0)) {
            interleavedPass.Textures.x = (mesh->mTextureCoords[0][i].x);
            interleavedPass.Textures.y = (mesh->mTextureCoords[0][i].y);

        } else {
            interleavedPass.Textures.x = (0.0f);
            interleavedPass.Textures.y = (0.0f);
        }
        interleavedData.push_back(interleavedPass);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }
}

glm::vec2 ObjectGenerator::uploadObj(std::string filepath, GLenum usage) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_GenNormals);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "Assimp error: " << importer.GetErrorString() << std::endl;
        return glm::vec2(0, 0);
    }

    // This vector holds all Positions, Normals, Textures.
    std::vector<Vortex> localInterleavedData;
    std::vector<GLuint> localIndices;

    objectProcess::processNode(scene->mRootNode, scene, localInterleavedData, localIndices);

    if (usage == GL_DYNAMIC_DRAW) {
        dynamicMesh m{};
        glGenVertexArrays(1, &m.VAO);
        glBindVertexArray(m.VAO);

        glGenBuffers(1, &m.VBO);
        glGenBuffers(1, &m.EBO);
        /* | VERTICES | NORMALS | TEXTURE | */
        glBindBuffer(GL_ARRAY_BUFFER, m.VBO);
        glBufferData(GL_ARRAY_BUFFER, localInterleavedData.size() * sizeof(Vortex), localInterleavedData.data(), GL_DYNAMIC_DRAW);

        glEnableVertexAttribArray(0);  // Positions
        glEnableVertexAttribArray(1);  // Normals
        glEnableVertexAttribArray(2);  // Textures
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vortex), (void*)(offsetof(Vortex, Positions)));
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vortex), (void*)(offsetof(Vortex, Normals)));
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vortex), (void*)(offsetof(Vortex, Textures)));
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m.EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (localIndices.size() * sizeof(GLuint)), localIndices.data(), GL_DYNAMIC_DRAW);
        glBindVertexArray(0);
        m.indexCount = static_cast<GLsizei>(localIndices.size());
        m.objToWorldMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        Meshes.push_back(m);

    } else {
        staticMesh obj;
        obj.baseVertex = currVertexSize;
        obj.baseIndex = currIndexSize;
        obj.indexCount = static_cast<GLsizei>(localIndices.size());

        globalInterleavedData.insert(globalInterleavedData.end(), localInterleavedData.begin(), localInterleavedData.end());
        globalIndices.insert(globalIndices.end(), localIndices.begin(), localIndices.end());

        obj.objToWorldMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        globalMeshes.push_back(obj);

        currVertexSize += static_cast<GLsizei>(localInterleavedData.size());
        currIndexSize += static_cast<GLsizei>(localIndices.size());
    }

    std::cout << "Uploaded to buffers!\n";
    return usage == GL_DYNAMIC_DRAW ? glm::vec2(Meshes.size() - 1, 1) : glm::vec2(globalMeshes.size() - 1, 2);
}

GLuint ObjectGenerator::uploadImg(const char* filepath) {
    GLuint texture;

    SDL_Surface* surface = IMG_Load(filepath);
    if (!surface) {
        SDL_Log("Couldn't load image Error : %s", SDL_GetError());
        SDL_DestroySurface(surface);
        return 0;
    }

    SDL_Surface* formatted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);
    SDL_DestroySurface(surface);

    if (!formatted) {
        SDL_Log("Couldn't load image Error : %s", SDL_GetError());
        SDL_DestroySurface(formatted);
        return 0;
    }

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, formatted->w, formatted->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, formatted->pixels);
    glGenerateMipmap(GL_TEXTURE_2D);

    SDL_DestroySurface(formatted);
    sampleImages.push_back(texture);
    return static_cast<GLuint>(sampleImages.size() - 1);
}

void ObjectGenerator::transform(glm::vec2& object_index, glm::vec3 translate, glm::vec3 rotate) {
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), translate) * glm::rotate(glm::mat4(1.0f), glm::radians(rotate.x), glm::vec3(1.0f, 0.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(rotate.y), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(rotate.z), glm::vec3(0.0f, 0.0f, 1.0f));

    if (static_cast<GLint>(object_index.y) == 1) {
        Meshes[static_cast<GLint>(object_index.x)].objToWorldMatrix = transform;

    } else {
        globalMeshes[static_cast<GLint>(object_index.x)].objToWorldMatrix = transform;
    }
}

void ObjectGenerator::attach(glm::vec2 obj_index, GLuint img_index, bool affectedBySpecular) {
    if (static_cast<int>(obj_index.y) == 1) {
        if (affectedBySpecular == true) {
            Meshes[static_cast<GLint>(obj_index.x)].texture1 = sampleImages[img_index];
        } else {
            Meshes[static_cast<GLint>(obj_index.x)].texture0 = sampleImages[img_index];
        }

    } else {
        if (affectedBySpecular == true) {
            globalMeshes[static_cast<GLint>(obj_index.x)].texture1 = sampleImages[img_index];
        } else {
            globalMeshes[static_cast<GLint>(obj_index.x)].texture0 = sampleImages[img_index];
        }
    }
}

void ObjectGenerator::process() {
    if (globalMeshes.size() < 1) {
        std::cout << "Unable to process static meshes without static_meshes. \n";
        return;
    }
    std::cout << "Starting Process...\n";
    glGenVertexArrays(1, &s_vao);
    glBindVertexArray(s_vao);

    glGenBuffers(1, &s_vbo);
    glGenBuffers(1, &s_ebo);

    glBindBuffer(GL_ARRAY_BUFFER, s_vbo);
    glBufferData(GL_ARRAY_BUFFER, globalInterleavedData.size() * sizeof(Vortex), globalInterleavedData.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);  // Positions
    glEnableVertexAttribArray(1);  // Normals
    glEnableVertexAttribArray(2);  // Textures
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vortex), (void*)(offsetof(Vortex, Positions)));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vortex), (void*)(offsetof(Vortex, Normals)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vortex), (void*)(offsetof(Vortex, Textures)));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, globalIndices.size() * sizeof(GLuint), globalIndices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
}

const std::vector<dynamicMesh>& ObjectGenerator::getDynamicMeshes() const {
    return Meshes;
}

const std::vector<staticMesh>& ObjectGenerator::getStaticMeshes() const {
    return globalMeshes;
}

GLuint ObjectGenerator::getStaticVao() {
    return s_vao;
}

void ObjectGenerator::cleanup() {
    for (auto& object : Meshes) {
        glDeleteVertexArrays(1, &object.VAO);
        glDeleteBuffers(1, &object.VBO);
        glDeleteBuffers(1, &object.EBO);
    }

    Meshes.clear();
    Meshes.shrink_to_fit();
    std::vector<dynamicMesh>().swap(Meshes);

    glDeleteVertexArrays(1, &s_vao);
    glDeleteBuffers(1, &s_vbo);
    glDeleteBuffers(1, &s_ebo);

    globalMeshes.clear();
    globalMeshes.shrink_to_fit();
    std::vector<staticMesh>().swap(globalMeshes);

    std::cout << "Object cleanup finished.\n";
}
