#version 460

out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct SpotLight {
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

struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec2 texCoords;            // Texture Coordinates
in vec3 vertexPositionWorld;  // Position of the object with transform
in vec3 normalWorld;          // Normals of the object with transform
uniform vec3 viewPosition;    // Camera Position

uniform Material material;
uniform DirLight dirLight;
uniform SpotLight spotLight;

#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

// TODO: DONT FORGET TO ADD VALUES TO THE LIGHTS AND CHANGE LightColor
vec2 flipped = vec2(texCoords.x, 1.0 - texCoords.y);

void main() {
    vec3 norm = normalize(normalWorld);
    vec3 viewDir = normalize(viewPosition - vertexPositionWorld);
    // Directional Light(THE SUNNNN)
    vec3 result;

    result += CalcDirLight(dirLight, norm, viewDir);
    // Point Lights
    for (int i = 0; i < NR_POINT_LIGHTS; i++) {
        result += CalcPointLight(pointLights[i], norm, vertexPositionWorld, viewDir);
    }
    // Spot Light | Flash Light
    result += CalcSpotLight(spotLight, norm, vertexPositionWorld, viewDir);

    FragColor = vec4(result, 1.0);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular
    vec3 reflectorDir = reflect(-lightDir, normal);

    float spec = pow(max(dot(viewDir, reflectorDir), 0.0), material.shininess);

    vec3 ambient = light.ambient * vec3(texture(material.diffuse, flipped));
    vec3 diffuse = light.diffuse * vec3(texture(material.diffuse, flipped));
    vec3 specular = light.specular * vec3(texture(material.specular, flipped));
    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);
    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // Attenuation - Basically a distance math wizardy so it doesnt light up something far away
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // Combine everything
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, flipped));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, flipped));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, flipped));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // Ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, flipped));
    ambient *= attenuation;  // Attenuate ambient

    // Diffuse
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, flipped));

    // Specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, flipped));

    // Spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction));  // Angle check
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    // Apply attenuation AND intensity to diffuse/specular
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return (ambient + diffuse + specular);
}
