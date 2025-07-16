#version 460
#extension GL_ARB_bindless_texture : require

layout(std430, binding = 0) buffer TextureHandles {
    sampler2D globalTextures[];
};

uniform uint textureIndices[100];

out vec4 FragColor;
in vec2 textureCoords;
in float textureIndex;

vec2 flipped = vec2(textureCoords.x, 1.0 - textureCoords.y);

void main() {
    FragColor = texture(globalTextures[textureIndices[int(textureIndex)]], flipped);

    // FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
