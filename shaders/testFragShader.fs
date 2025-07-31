#version 460
#extension GL_ARB_bindless_texture : require

layout(std430, binding = 0) buffer TextureHandles {
    sampler2D globalTextures[];
};

uniform uint textureIndices[100];
in vec2 textureCoords;
in float textureIndex;

out vec4 FragColor;

vec2 flipped = vec2(textureCoords.x, 1.0 - textureCoords.y);

void main() {
    FragColor = texture(globalTextures[textureIndices[int(textureIndex)]], flipped);
    // FragColor = vec4(vec3(gl_FragCoord.z), 1.0);
}
