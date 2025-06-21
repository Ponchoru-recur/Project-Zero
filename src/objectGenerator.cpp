#include "objectGenerator.hpp"

namespace objectProcess {
void processNode(aiNode* node, const aiScene* scene, std::vector<GLfloat>& vertsNorms, std::vector<GLuint>& indices, std::vector<GLfloat>& colors);
void processMesh(aiMesh* mesh, std::vector<GLfloat>& vertsNorms, std::vector<GLuint>& indices, std::vector<GLfloat>& colors);
};  // namespace objectProcess

void objectProcess::processNode(aiNode* node, const aiScene* scene, std::vector<GLfloat>& vertsNorms, std::vector<GLuint>& indices, std::vector<GLfloat>& colors) {
    // Process all the node’s meshes
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        processMesh(mesh, vertsNorms, indices, colors);
    }

    // Recursively process children
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene, vertsNorms, indices, colors);
    }
}

void objectProcess::processMesh(aiMesh* mesh, std::vector<GLfloat>& vertsNorms, std::vector<GLuint>& indices, std::vector<GLfloat>& colors) {
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        // Position
        vertsNorms.push_back(mesh->mVertices[i].x);
        vertsNorms.push_back(mesh->mVertices[i].y);
        vertsNorms.push_back(mesh->mVertices[i].z);

        // Normals (optional)
        if (mesh->HasNormals()) {
            vertsNorms.push_back(mesh->mNormals[i].x);
            vertsNorms.push_back(mesh->mNormals[i].y);
            vertsNorms.push_back(mesh->mNormals[i].z);
        } else {
            vertsNorms.push_back(0.0f);  // Fallback normal
            vertsNorms.push_back(0.0f);
            vertsNorms.push_back(1.0f);
        }

        // Vertex Colors (optional)
        if (mesh->HasVertexColors(0)) {
            colors.push_back(mesh->mColors[0][i].r);
            colors.push_back(mesh->mColors[0][i].g);
            colors.push_back(mesh->mColors[0][i].b);
            // Optional alpha
            // vertices.push_back(mesh->mColors[0][i].a);
        } else {
            colors.push_back(1.0f);  // Fallback white
            colors.push_back(1.0f);
            colors.push_back(1.0f);
        }
    }
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }
}

void ObjectGenerator::uploadObj(std::string filepath, GLenum usage) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_GenNormals);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "Assimp error: " << importer.GetErrorString() << std::endl;
    }

    std::vector<GLfloat> localVertsNormals;
    std::vector<GLfloat> localColors;
    std::vector<GLuint> localIndices;

    objectProcess::processNode(scene->mRootNode, scene, localVertsNormals, localIndices, localColors);

    if (usage == GL_DYNAMIC_DRAW) {
        Mesh m{};
        glGenVertexArrays(1, &m.VAO);
        glBindVertexArray(m.VAO);

        glGenBuffers(1, &m.VBO);
        glGenBuffers(1, &m.EBO);

        glBindBuffer(GL_ARRAY_BUFFER, m.VBO);
        glBufferData(GL_ARRAY_BUFFER, (localVertsNormals.size() + localColors.size()) * sizeof(GLfloat), 0, GL_DYNAMIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, localVertsNormals.size() * sizeof(GLfloat), localVertsNormals.data());
        glBufferSubData(GL_ARRAY_BUFFER, localVertsNormals.size() * sizeof(GLfloat), localColors.size() * sizeof(GLfloat), localColors.data());
        glEnableVertexAttribArray(0);  // Position
        glEnableVertexAttribArray(1);  // Normals
        glEnableVertexAttribArray(2);  // Color
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, 0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (void*)(sizeof(GLfloat) * 3));
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(GLfloat) * localVertsNormals.size()));
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m.EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (localIndices.size() * sizeof(GLuint)), localIndices.data(), GL_DYNAMIC_DRAW);
        glBindVertexArray(0);
        m.indexCount = localIndices.size();
        m.transform_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        Meshes.push_back(m);
        std::cout << "Sent to DYNAMIC_STORAGE" << "\n";
    } else {
        StaticMeshInfo obj;
        obj.baseVertex = currVertexSize;
        obj.baseIndex = currIndexSize;
        obj.indexCount = localIndices.size();

        s_color.insert(s_color.end(), localColors.begin(), localColors.end());
        s_verticesAndNormals.insert(s_verticesAndNormals.end(), localVertsNormals.begin(), localVertsNormals.end());
        s_indices.insert(s_indices.end(), localIndices.begin(), localIndices.end());
        s_meshes.push_back(obj);

        currIndexSize += localIndices.size();
        currVertexSize += localVertsNormals.size() / 6;
        std::cout << "Sent to STATIC_STORAGE" << "\n";
        std::cout << "mesh has "
                  << localVertsNormals.size() / 6 << " verts, "
                  << localIndices.size() << " indices, "
                  << " baseVertex=" << obj.baseVertex
                  << " baseIndex=" << obj.baseIndex << "\n";
    }

    std::cout << "Uploaded to buffers!\n";
}

void ObjectGenerator::transform(short index, glm::vec3 translate, glm::vec3 rotate) {
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), translate) * glm::rotate(glm::mat4(1.0f), glm::radians(rotate.x), glm::vec3(1.0f, 0.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(rotate.y), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(rotate.z), glm::vec3(0.0f, 0.0f, 1.0f));
    Meshes[index].transform_matrix = transform;
}

void ObjectGenerator::process() {
    std::cout << "Starting Process...\n";
    glGenVertexArrays(1, &s_vao);
    glBindVertexArray(s_vao);

    glGenBuffers(1, &s_vbo);
    glGenBuffers(1, &s_ebo);

    glBindBuffer(GL_ARRAY_BUFFER, s_vbo);
    glBufferData(GL_ARRAY_BUFFER, (s_verticesAndNormals.size() + s_color.size()) * sizeof(GLfloat), 0, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, s_verticesAndNormals.size() * sizeof(GLfloat), s_verticesAndNormals.data());
    glBufferSubData(GL_ARRAY_BUFFER, s_verticesAndNormals.size() * sizeof(GLfloat), s_color.size() * sizeof(GLfloat), s_color.data());

    // Reminder that YOU put the vertices and normals in one vector and separated the color (because i might remove the color and replace it with texture sooner or later.)
    glEnableVertexAttribArray(0);  // Positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (void*)0);

    glEnableVertexAttribArray(1);  // Normals
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (void*)(sizeof(GLfloat) * 3));

    glEnableVertexAttribArray(2);  // Colors (will be removed soon)
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 0, (void*)(s_verticesAndNormals.size() * sizeof(GLfloat)));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, s_indices.size() * sizeof(GLuint), s_indices.data(), GL_STATIC_DRAW);
    glBindVertexArray(0);

    for (auto& object : s_meshes) {
        std::cout << "indexCount : " << object.indexCount << "\n"
                  << "baseIndex : " << object.baseIndex << "\n"
                  << "baseVertex : " << object.baseVertex << "\n";
    }
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
    std::cout << "Object cleanup finished.\n";
}

// for (auto& object : Meshes) {
//     std::cout << "VAO : " << object.VAO << "\n"
//               << "VBO : " << object.VBO << "\n"
//               << "EBO : " << object.EBO << "\n"
//               << "indexCount : " << object.indexCount << "\n";
// }
