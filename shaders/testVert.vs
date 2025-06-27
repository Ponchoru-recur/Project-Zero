#version 460

layout(location = 0) in vec4 vertexPositionModel;
layout(location = 1) in vec3 normals;
layout(location = 2) in vec2 texCoordinate;

uniform mat4 modelToWorldProjectionMatrix;
uniform mat4 modelToWorldTransformation;

out vec2 texCoords;

out vec3 vertexPositionWorld;
out vec3 normalWorld;

void main() {
    gl_Position = modelToWorldProjectionMatrix * vertexPositionModel;

    texCoords = texCoordinate;

    vertexPositionWorld = vec3(modelToWorldTransformation * vertexPositionModel);
    normalWorld = mat3(transpose(inverse(modelToWorldTransformation))) * normals;
}
