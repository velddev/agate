#version 330 core 

in vec3 fragPos;
in vec3 normal;
in vec2 uv;

layout(location = 0) out vec4 FragColor; 

uniform sampler2D image;

uniform vec3 ambientColor;


void main() 
{	
	float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * ambientColor;

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(vec3(0, 0, 0) - fragPos); 

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * vec3(1, 1, 1);

	FragColor = vec4(ambient, 1) * vec4(texture(image, uv).rgb, 1);
}