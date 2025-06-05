#pragma once

#include <glad/glad.h>
#include <iostream>

inline const char *vertexShaderSource = R"(
    #version 460
    layout (location = 0) in vec3 pos;
    layout (location = 1) in vec3 vertexColor;
    layout (location = 2) in mat4 fullMat;

    out vec3 theColor;

    void main() {

       gl_Position = fullMat * vec4(pos, 1.0f);
       theColor = vertexColor;
    };
)";

inline const char *fragmentShaderSource = R"(
    #version 460

    out vec4 FragColor;
    in vec3 theColor;

    void main(){

       FragColor = vec4(theColor, 0.5f);
    };
)";

namespace Shader {
GLuint compileShader(const char *source, GLenum type);
GLuint linkProgram(GLuint vertexShader, GLuint fragmentShader);
GLuint loadShaderProgram(const char *vertSource, const char *fragSource);
}  // namespace Shader
