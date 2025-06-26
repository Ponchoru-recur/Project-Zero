#include "shaders.hpp"

std::string Shader::LoadShaderFileSource(const std::string& filepath) {
    std::ifstream file(filepath);

    if (!file.is_open()) {
        std::cerr << "Failed to open shader file : " << filepath << "\n";
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

GLuint Shader::compileShader(std::string& source, GLenum type) {
    const char* convertSource = source.c_str();
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &convertSource, NULL);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cout << "Shader Compilation Error (" << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") << "):\n"
                  << infoLog << '\n';
    }

    return shader;
}

GLuint Shader::linkProgram(GLuint vertexShader, GLuint fragmentShader) {
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cerr << "Program linking Error : " << infoLog << "\n";
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

// Unused, no use yet.
GLuint Shader::loadShaderProgram(std::string& vertSource, std::string& fragSource) {
    GLuint vs = compileShader(vertSource, GL_VERTEX_SHADER);    // Compile vertex shader
    GLuint fs = compileShader(fragSource, GL_FRAGMENT_SHADER);  // Compile fragment shader
    return linkProgram(vs, fs);                                 // Link both into a program
}
