#version 330 core 

struct RenderSystemSettings
{
	float ambientIntensity;
};

struct Material 
{
	vec3 ambient;
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct DirectionalLight
{
	vec3 direction;
	vec3 diffuse;

	float intensity;
};

struct PointLight 
{    
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;  

    vec3 diffuse;
};  

in vec3 fragPos;
in vec3 normal;
in vec2 uv;

layout(location = 0) out vec4 FragColor; 

uniform vec3 viewPos;
uniform int pointLightCount;

uniform RenderSystemSettings renderSystem;
uniform Material material;

uniform DirectionalLight dirLight;
uniform PointLight pointLights[16];

// -- methods

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 ambient  = material.ambient * renderSystem.ambientIntensity * light.intensity  * vec3(texture(material.diffuse, uv));
    vec3 diffuse  = light.diffuse * light.intensity  * diff * vec3(texture(material.diffuse, uv));
    vec3 specular = light.diffuse * light.intensity  * spec * vec3(texture(material.specular, uv));

    return (ambient + diffuse + specular);
}  

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    float diff = max(dot(normal, lightDir), 0.0);
 
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

    vec3 ambient  = material.ambient * renderSystem.ambientIntensity * vec3(texture(material.diffuse, uv));
    vec3 diffuse  = light.diffuse * diff * vec3(texture(material.diffuse, uv));
    vec3 specular = light.diffuse * spec * vec3(texture(material.specular, uv));

    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}

void main() 
{	
	vec3 norm = normalize(normal);
	vec3 viewDir = normalize(viewPos - fragPos);

	vec3 result = vec3(0.0);

	result += CalculateDirectionalLight(dirLight, norm, viewDir); 

	for(int i = 0; i < pointLightCount; i++)
		result += CalculatePointLight(pointLights[i], norm, fragPos, viewDir);

	FragColor = vec4(result, 1);
}