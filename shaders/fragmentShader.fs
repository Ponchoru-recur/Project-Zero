#version 460

out vec4 FragColor;
in vec3 theColor;

uniform vec4 ambientLight;
uniform vec3 lightPosition;
uniform vec3 eyePositionWorld;

in vec3 vertexPositionWorld;
in vec3 normalWorld;

void main() {
    // Diffuse Light
    vec3 lightVectorWorld = normalize(lightPosition - vertexPositionWorld);
    float Brightness = max(dot(lightVectorWorld, normalize(normalWorld)), 0.0);
    vec4 diffuseLight = vec4(vec3(Brightness, Brightness, Brightness), 1.0);

    // Specular Light
    vec3 reflectedLightVectorWorld = reflect(-lightVectorWorld, normalWorld);
    vec3 eyeVectorWorld = normalize(eyePositionWorld - vertexPositionWorld);
    float s = clamp(dot(reflectedLightVectorWorld, eyeVectorWorld), 0, 1);
    s = pow(s, 60.0);
    vec4 specularLight = vec4(s, s, s, 1.0);

    // Final Color
    FragColor = ambientLight + vec4(theColor, 1.0) * clamp(diffuseLight, 0.1, 1.0) + clamp(specularLight, 0.1, 1.0);
}
