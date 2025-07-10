#version 460
#extension GL_ARB_bindless_texture : require

layout(bindless_sampler) uniform sampler2D yourTexture[6];

out vec4 FragColor;
in vec2 textureCoords;
in float textureIndex;

vec2 flipped = vec2(textureCoords.x, 1.0 - textureCoords.y);

void main() {
    FragColor = texture(yourTexture[int(textureIndex)], flipped);

    // FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
