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

struct Light
{
	vec3 position;
	vec3 color;
};

in vec3 fragPos;
in vec3 normal;
in vec2 uv;

layout(location = 0) out vec4 FragColor; 

uniform vec3 viewPos;

uniform RenderSystemSettings renderSystem;
uniform Material material;
uniform Light light;

void main() 
{	
	// ambient
    vec3 ambient = renderSystem.ambientIntensity * material.ambient * vec3(texture(material.diffuse, uv));

	// diffuse
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(light.position - fragPos); 
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.color * (diff * vec3(texture(material.diffuse, uv)));

	// specular
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.color * (spec * vec3(texture(material.specular, uv)));  

	vec3 result = (ambient + diffuse + specular);
	FragColor = vec4(result, 1);
}