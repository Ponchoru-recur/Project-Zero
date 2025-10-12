#version 460
out vec4 FragColor;

uniform sampler2D screenTex;

in vec2 UV;

void main() {
    vec3 col = texture(screenTex, UV).rgb;
    float grey = dot(col, vec3(0.299, 0.587, 0.114));
    FragColor = vec4(vec3(1.0 - texture(screenTex, UV)), 1.0);
}
