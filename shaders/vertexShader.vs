#version 460

layout(location = 0) in vec4 vertexPositionModel;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 vertexColor;

uniform mat4 modelToWorldProjectionMatrix;
uniform mat4 modelToWorldTransformMatrix;

out vec3 theColor;
out vec3 normalWorld;
out vec3 vertexPositionWorld;

void main() {
    gl_Position = modelToWorldProjectionMatrix * vertexPositionModel;

    theColor = vertexColor;
    vertexPositionWorld = vec3(modelToWorldTransformMatrix * vertexPositionModel);
    normalWorld = vec3(modelToWorldTransformMatrix * vec4(normal, 0.0f));
};
