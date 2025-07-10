#include "../headers/objectGenerator.hpp"
#include "../headers/shaders.hpp"
#include <iostream>

int main() {
    // Create an AssimpObject instance
    AssimpObject object;

    // Load a 3D model (example with one of the existing models)
    std::string modelPath = "../assets/objects/cube.obj";

    if (object.loadObject(modelPath)) {
        std::cout << "Model loaded successfully!" << std::endl;
        std::cout << "File path: " << object.getFilePath() << std::endl;

        const ObjectData& data = object.getObjectData();
        std::cout << "Model statistics:" << std::endl;
        std::cout << "- Vertices: " << data.vertices.size() << std::endl;
        std::cout << "- Indices: " << data.indices.size() << std::endl;
        std::cout << "- SubMeshes: " << data.subMeshes.size() << std::endl;
        std::cout << "- Textures: " << data.textures.size() << std::endl;

        // Example of how to use in a rendering loop:
        // GLuint shaderProgram = /* your shader program */;
        // glm::mat4 modelMatrix = glm::mat4(1.0f); // Identity matrix
        // object.render(shaderProgram, modelMatrix);

    } else {
        std::cerr << "Failed to load model: " << modelPath << std::endl;
        return -1;
    }

    return 0;
}
