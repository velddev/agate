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

void main() 
{	
    vec3 diffuse  = diff * vec3(texture(material.diffuse, uv));

	FragColor = vec4(diffuse, 1);
}