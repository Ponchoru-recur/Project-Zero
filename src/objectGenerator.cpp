#include "objectGenerator.hpp"

namespace objectProcess {
void processNode(aiNode* node, const aiScene* scene, std::vector<GLfloat>& vertices, std::vector<GLuint>& elements);
void processMesh(aiMesh* mesh, std::vector<GLfloat>& vertices, std::vector<GLuint>& elements);
};  // namespace objectProcess

void objectProcess::processNode(aiNode* node, const aiScene* scene, std::vector<GLfloat>& vertices, std::vector<GLuint>& elements) {
    // Process all the node’s meshes
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        processMesh(mesh, vertices, elements);
    }

    // Recursively process children
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene, vertices, elements);
    }
}

void objectProcess::processMesh(aiMesh* mesh, std::vector<GLfloat>& vertices, std::vector<GLuint>& elements) {
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
            elements.push_back(face.mIndices[j]);
        }
    }
}

void ObjectGenerator::uploadObj(std::string filepath) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_GenNormals);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "Assimp error: " << importer.GetErrorString() << std::endl;
    }

    std::vector<GLfloat> verts;
    std::vector<GLuint> elems;

    objectProcess::processNode(scene->mRootNode, scene, verts, elems);

    Mesh m{};

    glGenVertexArrays(1, &m.VAO);
    glBindVertexArray(m.VAO);

    glGenBuffers(1, &m.VBO);
    glGenBuffers(1, &m.EBO);

    glBindBuffer(GL_ARRAY_BUFFER, m.VBO);
    glBufferData(GL_ARRAY_BUFFER, (verts.size() * sizeof(GLfloat)), verts.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 9, 0);                             // Position
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 9, (void*)(sizeof(GLfloat) * 6));  // Color
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 9, (void*)(sizeof(GLfloat) * 3));  // Normals
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (elems.size() * sizeof(GLuint)), elems.data(), GL_STATIC_DRAW);
    glBindVertexArray(0);

    m.indexCount = elems.size();

    ObjectStorage.push_back(m);

    std::cout << "VAO   " << m.VAO << '\n'
              << "VBO   " << m.VBO << '\n'
              << "EBO   " << m.EBO << '\n'
              << "verts " << verts.size() << '\n'
              << "idx   " << elems.size() << "\n"
              << "vertexCount  = " << verts.size() / 9 << '\n'
              << "indexCount   = " << elems.size() << '\n';

    std::cout << "Uploaded!\n\n";
}

std::vector<Mesh>& ObjectGenerator::getinfo() {
    return ObjectStorage;
}
