#include "objectGenerator.hpp"

// Declaring it outside so it creates storage for it
GLuint AssimpObject::imageIndexCounter;
std::unordered_map<std::string, size_t> AssimpObject::textureIndexMap;
std::vector<GLuint64> AssimpObject::textureHandles;

void AssimpObject::processNode(aiNode* node, const aiScene* scene, std::vector<Vertex>& interleavedData, std::vector<GLuint>& indices, GLuint& vertexBase) {
    // Process all the node’s meshes
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        processMesh(mesh, scene, interleavedData, indices, vertexBase);
    }

    // Recursively process children
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene, interleavedData, indices, vertexBase);
    }
}

void AssimpObject::processMesh(aiMesh* mesh, const aiScene* scene, std::vector<Vertex>& interleavedData, std::vector<GLuint>& indices, GLuint& vertexBase) {
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex interleavedPass{};
        // Position
        interleavedPass.position.x = (mesh->mVertices[i].x);
        interleavedPass.position.y = (mesh->mVertices[i].y);
        interleavedPass.position.z = (mesh->mVertices[i].z);

        // Normals
        if (mesh->HasNormals()) {
            interleavedPass.normal.x = (mesh->mNormals[i].x);
            interleavedPass.normal.y = (mesh->mNormals[i].y);
            interleavedPass.normal.z = (mesh->mNormals[i].z);
        } else {
            interleavedPass.normal.x = (0.0f);  // Fallback normal
            interleavedPass.normal.y = (0.0f);
            interleavedPass.normal.z = (1.0f);
        }

        if (mesh->HasTextureCoords(0)) {
            interleavedPass.textureCoord.x = (mesh->mTextureCoords[0][i].x);
            interleavedPass.textureCoord.y = (mesh->mTextureCoords[0][i].y);
        } else {
            interleavedPass.textureCoord.x = (0.0f);
            interleavedPass.textureCoord.y = (0.0f);
        }

        interleavedPass.textureFace = temp;
        interleavedData.push_back(interleavedPass);
    }

    if (mesh->mMaterialIndex < scene->mNumMaterials) {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        aiString str;
        if (material->GetTexture(aiTextureType_DIFFUSE, 0, &str) == AI_SUCCESS) {
            std::string texPath = str.C_Str();

            std::cout << "texture path : " << texPath << "\n";

            loadTextureIndex(str.C_Str());
        } else {
            std::cout << "texture path : None " << "\n";
        }
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        // std::cout << "Face " << i << ": ";
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            // std::cout << (face.mIndices[j] + vertexBase) << " ";
            indices.push_back(face.mIndices[j] + vertexBase);
        }
    }
    vertexBase += mesh->mNumVertices;
    temp++;
}

SDL_Surface* AssimpObject::createImage(const char* filepath) {
    SDL_Surface* surface = IMG_Load(filepath);

    // Guard
    if (!surface) {
        std::cerr << "Image load error : " << SDL_GetError() << "\n";
        return nullptr;
    }

    SDL_Surface* format = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);

    // Guard
    if (!format) {
        std::cerr << "Format load error : " << SDL_GetError() << "\n";
        return nullptr;
    }

    return format;
}

void AssimpObject::processToHandle(SDL_Surface* image_format) {
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_format->w, image_format->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_format->pixels);
    glGenerateMipmap(GL_TEXTURE_2D);

    if (texture) {
        textures.push_back(texture);
    } else {
        std::cerr << "Texture Error in processToHandle : broken texture" << "\n";
        return;
    }

    GLuint64 handle = glGetTextureHandleARB(texture);

    if (handle) {
        glMakeTextureHandleResidentARB(handle);
        textureHandles.push_back(handle);
    } else {
        std::cerr << "Cannot push handle to resident." << "\n";
    }

    SDL_DestroySurface(image_format);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void AssimpObject::loadTextureIndex(std::string path) {
    auto it = textureIndexMap.find(path);
    if (it != textureIndexMap.end()) {
        std::cout << "already exists.\n";
        imageIndices.push_back(static_cast<GLuint>(it->second));
        return;
    }

    SDL_Surface* format = createImage(path.c_str());
    processToHandle(format);

    imageIndices.push_back(imageIndexCounter++);
    return;
}

AssimpObject::AssimpObject(std::string filepath) {
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "Assimp error : " << importer.GetErrorString() << "\n";
        return;
    }

    GLuint vertexBase = 0;
    processNode(scene->mRootNode, scene, globalInterleavedData, globalIndices, vertexBase);

    // std::cout << "globalInterleavedData.size() : " << globalInterleavedData.size() << "\n";
    // std::cout << "globalIndices.size() : " << globalIndices.size() << "\n";
    // std::cout << "textureHandles.size() : " << textureHandles.size() << "\n";

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * globalInterleavedData.size(), globalInterleavedData.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);  // Position
    glEnableVertexAttribArray(1);  // Normal
    glEnableVertexAttribArray(2);  // Texure coordinates
    glEnableVertexAttribArray(3);  // texture face

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, position)));      // Position
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, normal)));        // Normal
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, textureCoord)));  // Texture coords
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, textureFace)));   // Texture face

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * globalIndices.size(), globalIndices.data(), GL_STATIC_DRAW);
}

AssimpObject::~AssimpObject() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    std::vector<Vertex>().swap(globalInterleavedData);
    std::vector<GLuint>().swap(globalIndices);
    std::cout << "successfully deleted object." << "\n";
}
