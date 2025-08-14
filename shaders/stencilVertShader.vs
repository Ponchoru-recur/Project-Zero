#version 460
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 texturePosition;

out vec2 UV;

void main() {
    gl_Position = vec4(aPos, 1.0);
    UV = texturePosition;
}

// TODO: Watch the anime on your screenshots the chinese one with the name saying "Slow knight"
