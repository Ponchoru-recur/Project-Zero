#version 460
#extension GL_ARB_bindless_texture : require

layout(bindless_sampler) uniform sampler2D yourTexture[2];

out vec4 FragColor;
in vec2 textureCoords;
flat in int textureIndex;

vec2 flipped = vec2(textureCoords.x, 1.0 - textureCoords.y);

void main() {
    FragColor = texture(yourTexture[textureIndex], flipped);
}
