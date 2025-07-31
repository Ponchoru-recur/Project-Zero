#pragma once

#include <glad/gl.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>

namespace Shader {
std::string LoadShaderFileSource(const std::string& filepath);
GLuint compileShader(std::string& source, GLenum type);
GLuint linkProgram(GLuint vertexShader, GLuint fragmentShader);
GLuint loadShaderProgram(std::string& vertSource, std::string& fragSource);
}  // namespace Shader
