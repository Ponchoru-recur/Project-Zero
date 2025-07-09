#version 460
#extension GL_ARB_bindless_texture : require

layout(bindless_sampler) uniform sampler2D yourTexture;

out vec4 FragColor;
in vec2 textureCoords;
flat in int textureIndex;

uniform sampler2D bindlessTexture[2];

vec2 flipped = vec2(textureCoords.x, 1.0 - textureCoords.y);

void main() {
    // if (textureIndex == 0) {
    //     FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    // } else {
    //     FragColor = vec4(0.0, 1.0, 0.0, 1.0);
    // }
    FragColor = texture(yourTexture, flipped);
    // FragColor = vec4(textureIndex, 1.0, 0.0, 1.0f);
}
