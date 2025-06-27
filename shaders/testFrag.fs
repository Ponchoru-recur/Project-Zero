#version 460

out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

in vec2 texCoords;

in vec3 vertexPositionWorld;  // Position of the object with transform
in vec3 normalWorld;          // Normals of the object with transform
uniform vec3 viewPosition;    // Camera Position

uniform Material material;
uniform Light light;

uniform sampler2D emissionMap;

// TODO: DONT FORGET TO ADD VALUES TO THE LIGHTS AND CHANGE LightColor

void main() {
    // Distance
    float distance = length(light.position - vertexPositionWorld);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // Texture
    vec2 flipped = vec2(texCoords.x, 1.0 - texCoords.y);
    // Emission that i dont even use yet
    vec3 emission = texture(emissionMap, flipped).rgb * 1.0;
    // Ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, flipped));

    vec3 norm = normalize(normalWorld);
    // vector that points toward the light
    // FIXME: normalize(-light.direction);
    vec3 lightDir = normalize(light.position - vertexPositionWorld);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, flipped));

    // Specular
    vec3 viewDir = normalize(viewPosition - vertexPositionWorld);
    vec3 reflectorDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectorDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, flipped));

    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    ambient *= attenuation;
    diffuse *= intensity;
    specular *= intensity;

    // ambient + diffuse * texture
    vec3 result = (ambient + diffuse + specular);
    FragColor = vec4(result, 1.0);
}
