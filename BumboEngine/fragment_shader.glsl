#version 330 core 

in vec4 normal;

layout(location = 0) out vec4 FragColor; 

void main() 
{	
	FragColor = vec4(normal * 0.5 + 0.5); 
}