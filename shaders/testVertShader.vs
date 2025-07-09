#version 460

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 textureCoordinates;
layout(location = 2) in int theIndex;

uniform mat4 modelToWorldProjectionMatrix;

out vec2 textureCoords;
flat out int textureIndex;

void main() {
    gl_Position = modelToWorldProjectionMatrix * vec4(position, 1.0f);

    textureCoords = textureCoordinates;
    textureIndex = theIndex;
}
