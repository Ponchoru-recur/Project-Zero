#include "objectGenerator.hpp"

namespace objectProcess {
void processNode(aiNode* node, const aiScene* scene, std::vector<GLfloat>& vertices, std::vector<GLushort>& elements);
void processMesh(aiMesh* mesh, std::vector<GLfloat>& vertices, std::vector<GLushort>& elements);
};  // namespace objectProcess

void objectProcess::processNode(aiNode* node, const aiScene* scene, std::vector<GLfloat>& vertices, std::vector<GLushort>& elements) {
    for (unsigned short i = 0; i < node->mNumMeshes; i++) {
        unsigned int meshIndex = node->mMeshes[i];  // Takes the location of the Meshes
        aiMesh* mesh = scene->mMeshes[meshIndex];
        processMesh(mesh, vertices, elements);
    }

    for (unsigned short j = 0; j < node->mNumChildren; j++) {
        processNode(node->mChildren[j], scene, vertices, elements);
    }
}

void objectProcess::processMesh(aiMesh* mesh, std::vector<GLfloat>& vertices, std::vector<GLushort>& elements) {
    for (size_t i = 0; i < mesh->mNumVertices; i++) {
        // Position
        vertices.push_back(mesh->mVertices[i].x);
        vertices.push_back(mesh->mVertices[i].y);
        vertices.push_back(mesh->mVertices[i].z);

        // Colors
        if (mesh->HasVertexColors(0)) {
            vertices.push_back(mesh->mColors[0][i].r);
            vertices.push_back(mesh->mColors[0][i].g);
            vertices.push_back(mesh->mColors[0][i].b);
        } else {
            vertices.push_back(1.0f);
            vertices.push_back(1.0f);
            vertices.push_back(1.0f);
        }

        if (mesh->HasNormals()) {
            vertices.push_back(mesh->mNormals[i].x);
            vertices.push_back(mesh->mNormals[i].y);
            vertices.push_back(mesh->mNormals[i].z);
        }

        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
            const aiFace& face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++) {
                elements.push_back(face.mIndices[j]);
            }
        }
    }
}

void ObjectGenerator::uploadObj(std::string filepath) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_GenNormals | aiProcess_ValidateDataStructure);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "Assimp error : " << importer.GetErrorString() << "\n";
    }

    std::vector<GLfloat> verts;
    std::vector<GLushort> elems;

    objectProcess::processNode(scene->mRootNode, scene, verts, elems);

    Mesh m{};

    glGenVertexArrays(1, &m.VAO);
    glBindVertexArray(m.VAO);

    glGenBuffers(1, &m.VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m.VBO);
    glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(GLfloat), verts.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);  // Position
    glEnableVertexAttribArray(1);  // Color
    glEnableVertexAttribArray(2);  // Normals
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 9, 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 9, (void*)(sizeof(GLfloat) * 3));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 9, (void*)(sizeof(GLfloat) * 6));

    glGenBuffers(1, &m.EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elems.size() * sizeof(GLushort), elems.data(), GL_STATIC_DRAW);

    m.indexCount = static_cast<GLushort>(elems.size());
    std::cout << "Uploaded!\n";
}

std::vector<Mesh>& ObjectGenerator::getinfo() {
    return ObjectStorage;
}
