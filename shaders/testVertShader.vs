#version 460

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 textureCoordinate;
layout(location = 3) in float textureFace;

uniform mat4 MVP;

out vec2 textureCoords;
out float textureIndex;

void main() {
    gl_Position = MVP * vec4(position, 1.0f);

    textureCoords = textureCoordinate;
    textureIndex = textureFace;
}
