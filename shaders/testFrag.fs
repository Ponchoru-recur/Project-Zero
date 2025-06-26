#version 460

out vec4 FragColor;

in vec2 texCoords;
in vec3 objColor;

in vec3 vertexPositionWorld;
in vec3 normalWorld;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPosition;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {
    // Texture
    vec2 flipped = vec2(texCoords.x, 1.0 - texCoords.y);

    // Ambient
    float ambientStrength = 0.5;
    vec3 ambient = ambientStrength * vec3(1.0, 1.0, 1.0);

    vec3 norm = normalize(normalWorld);
    // vector that points toward the light
    vec3 lightDir = normalize(lightPos - vertexPositionWorld);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPosition - vertexPositionWorld);
    vec3 reflectorDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectorDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    // ambient + diffuse * texture
    vec3 result = (ambient + diffuse + specular) ;
    FragColor = vec4(result, 1.0) * texture(texture1, flipped);
}
