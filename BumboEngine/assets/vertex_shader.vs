#version 330 core 

layout(location = 0) in vec3 position; 
layout(location = 1) in vec3 normals;
layout(location = 2) in vec2 uvs;

uniform mat4 MVP;
uniform mat4 model;

out vec3 fragPos;
out vec3 normal;
out vec2 uv;


void main() 
{ 
	gl_Position = MVP * vec4(position, 1);

	fragPos = (model * vec4(position, 1)).xyz;
	normal = normals;
	uv = uvs;
}