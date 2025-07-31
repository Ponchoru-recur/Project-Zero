#version 460
layout(location = 0) in vec3 aPos;

uniform mat4 MVP;

void main() {
    gl_Position = MVP * vec4(aPos, 1.0);
}

// TODO: Watch the anime on your screenshots the chinese one with the name saying "Slow knight"
