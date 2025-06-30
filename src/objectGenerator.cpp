#include "objectGenerator.hpp"

namespace objectProcess {
void processNode(aiNode* node, const aiScene* scene, std::vector<GLfloat>& verticesAndNormals, std::vector<GLfloat>& textureCoordinates, std::vector<GLuint>& indices);
void processMesh(aiMesh* mesh, std::vector<GLfloat>& verticesAndNormals, std::vector<GLfloat>& textureCoordinates, std::vector<GLuint>& indices);
};  // namespace objectProcess

void objectProcess::processNode(aiNode* node, const aiScene* scene, std::vector<GLfloat>& verticesAndNormals, std::vector<GLfloat>& textureCoordinates, std::vector<GLuint>& indices) {
    // Process all the node’s meshes
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        processMesh(mesh, verticesAndNormals, textureCoordinates, indices);
    }

    // Recursively process children
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene, verticesAndNormals, textureCoordinates, indices);
    }
}

void objectProcess::processMesh(aiMesh* mesh, std::vector<GLfloat>& verticesAndNormals, std::vector<GLfloat>& textureCoordinates, std::vector<GLuint>& indices) {
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        // Position
        verticesAndNormals.push_back(mesh->mVertices[i].x);
        verticesAndNormals.push_back(mesh->mVertices[i].y);
        verticesAndNormals.push_back(mesh->mVertices[i].z);

        // Normals (optional)
        if (mesh->HasNormals()) {
            verticesAndNormals.push_back(mesh->mNormals[i].x);
            verticesAndNormals.push_back(mesh->mNormals[i].y);
            verticesAndNormals.push_back(mesh->mNormals[i].z);
        } else {
            verticesAndNormals.push_back(0.0f);  // Fallback normal
            verticesAndNormals.push_back(0.0f);
            verticesAndNormals.push_back(1.0f);
        }

        if (mesh->HasTextureCoords(0)) {
            textureCoordinates.push_back(mesh->mTextureCoords[0][i].x);
            textureCoordinates.push_back(mesh->mTextureCoords[0][i].y);

        } else {
            textureCoordinates.push_back(0.0f);
            textureCoordinates.push_back(0.0f);
        }
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

    std::vector<GLfloat> localVerticesAndNormals;
    std::vector<GLfloat> localtextureCoordinates;
    std::vector<GLuint> localIndices;

    objectProcess::processNode(scene->mRootNode, scene, localVerticesAndNormals, localtextureCoordinates, localIndices);

    if (usage == GL_DYNAMIC_DRAW) {
        Mesh m{};
        glGenVertexArrays(1, &m.VAO);
        glBindVertexArray(m.VAO);

        glGenBuffers(1, &m.VBO);
        glGenBuffers(1, &m.EBO);
        /* | VERTICES | NORMALS | TEXTURE | COLORS | */
        glBindBuffer(GL_ARRAY_BUFFER, m.VBO);
        glBufferData(GL_ARRAY_BUFFER, (localVerticesAndNormals.size() + localtextureCoordinates.size()) * sizeof(GLfloat), 0, GL_DYNAMIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, localVerticesAndNormals.size() * sizeof(GLfloat), localVerticesAndNormals.data());
        glBufferSubData(GL_ARRAY_BUFFER, localVerticesAndNormals.size() * sizeof(GLfloat), localtextureCoordinates.size() * sizeof(GLfloat), localtextureCoordinates.data());

        glEnableVertexAttribArray(0);  // Positions
        glEnableVertexAttribArray(1);  // Normals
        glEnableVertexAttribArray(2);  // Texture
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, 0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (void*)(sizeof(GLfloat) * 3));
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat) * (localVerticesAndNormals.size())));
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m.EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (localIndices.size() * sizeof(GLuint)), localIndices.data(), GL_DYNAMIC_DRAW);
        glBindVertexArray(0);
        m.indexCount = localIndices.size();
        m.objToWorldMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        Meshes.push_back(m);
        std::cout << "Sending to DYNAMIC_STORAGE" << "\n"
                  << "Vertice count : " << localVerticesAndNormals.size() / 6 << "\n"
                  << "Normal count : " << localVerticesAndNormals.size() / 6 << "\n"
                  << "Texture count : " << localtextureCoordinates.size() << "\n"
                  << "Indice count : " << localIndices.size() << "\n";

    } else {
        StaticMeshInfo obj;
        obj.baseVertex = currVertexSize;
        obj.baseIndex = currIndexSize;
        obj.indexCount = localIndices.size();

        s_verticesAndNormals.insert(s_verticesAndNormals.end(), localVerticesAndNormals.begin(), localVerticesAndNormals.end());
        s_textureCoordinates.insert(s_textureCoordinates.end(), localtextureCoordinates.begin(), localtextureCoordinates.end());
        s_indices.insert(s_indices.end(), localIndices.begin(), localIndices.end());

        obj.objToWorldMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        s_meshes.push_back(obj);
        std::cout << "Sending to STATIC_STORAGE" << "\n"
                  << "Vertice count : " << s_verticesAndNormals.size() / 6 << "\n"
                  << "Normal count : " << s_verticesAndNormals.size() / 6 << "\n"
                  << "Texture count : " << s_textureCoordinates.size() << "\n"
                  << "Indice count : " << s_indices.size() << "\n"
                  << "BaseVertex : " << obj.baseVertex << "\n"
                  << "BaseIndex : " << obj.baseIndex << "\n";

        currVertexSize += localVerticesAndNormals.size() / 6;
        currIndexSize += localIndices.size();
    }

    std::cout << "Uploaded to buffers!\n";
    return usage == GL_DYNAMIC_DRAW ? glm::vec2(Meshes.size() - 1, 1) : glm::vec2(s_meshes.size() - 1, 2);
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
    return sampleImages.size() - 1;
}

void ObjectGenerator::transform(glm::vec2& object_index, glm::vec3 translate, glm::vec3 rotate) {
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), translate) * glm::rotate(glm::mat4(1.0f), glm::radians(rotate.x), glm::vec3(1.0f, 0.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(rotate.y), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(rotate.z), glm::vec3(0.0f, 0.0f, 1.0f));
    if (static_cast<int>(object_index.y) == 1) {
        Meshes[object_index.x].objToWorldMatrix = transform;
    } else {
        s_meshes[object_index.x].objToWorldMatrix = transform;
    }
}

void ObjectGenerator::attach(glm::vec2 obj_index, GLuint img_index, bool affectedBySpecular) {
    if (static_cast<int>(obj_index.y) == 1) {
        if (affectedBySpecular == true) {
            Meshes[obj_index.x].texture1 = sampleImages[img_index];
        } else {
            Meshes[obj_index.x].texture0 = sampleImages[img_index];
        }

    } else {
        if (affectedBySpecular == true) {
            s_meshes[obj_index.x].texture1 = sampleImages[img_index];
        } else {
            s_meshes[obj_index.x].texture0 = sampleImages[img_index];
        }
    }
}

void ObjectGenerator::process() {
    if (s_meshes.size() < 1) {
        std::cout << "Unable to process static meshes without static_meshes. \n";
        return;
    }
    std::cout << "Starting Process...\n";
    glGenVertexArrays(1, &s_vao);
    glBindVertexArray(s_vao);

    glGenBuffers(1, &s_vbo);
    glGenBuffers(1, &s_ebo);

    glBindBuffer(GL_ARRAY_BUFFER, s_vbo);
    glBufferData(GL_ARRAY_BUFFER, (s_verticesAndNormals.size() + s_textureCoordinates.size()) * sizeof(GLfloat), 0, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, s_verticesAndNormals.size() * sizeof(GLfloat), s_verticesAndNormals.data());
    glBufferSubData(GL_ARRAY_BUFFER, s_verticesAndNormals.size() * sizeof(GLfloat), s_textureCoordinates.size() * sizeof(GLfloat), s_textureCoordinates.data());

    glEnableVertexAttribArray(0);  // Positions
    glEnableVertexAttribArray(1);  // Normals
    glEnableVertexAttribArray(2);  // Textures

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (void*)(sizeof(GLfloat) * 3));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat) * (s_verticesAndNormals.size())));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, s_indices.size() * sizeof(GLuint), s_indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
}

const std::vector<Mesh>& ObjectGenerator::getDynamicMeshes() const {
    return Meshes;
}

const std::vector<StaticMeshInfo>& ObjectGenerator::getStaticMeshes() const {
    return s_meshes;
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
    std::vector<Mesh>().swap(Meshes);

    glDeleteVertexArrays(1, &s_vao);
    glDeleteBuffers(1, &s_vbo);
    glDeleteBuffers(1, &s_ebo);

    s_meshes.clear();
    s_meshes.shrink_to_fit();
    std::vector<StaticMeshInfo>().swap(s_meshes);

    std::cout << "Object cleanup finished.\n";
}
