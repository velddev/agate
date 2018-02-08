#version 330 core 

layout(location = 0) in vec4 aPos; 
layout(location = 1) in vec4 aNormal;

uniform mat4 MVP;

out vec4 normal;

void main() 
{ 
	gl_Position = MVP * aPos;
	normal = aNormal;
}