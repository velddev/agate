#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <vector>

#include <Windows.h>
#include <gl/GL.h>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uv;
};

class Mesh
{
public:
	Mesh();
	~Mesh();

	void Draw();

	void Setup();

	std::vector<Vertex> vertices;
	std::vector<std::uint32_t> indices;
	std::uint32_t materialId;

	GLuint vertexArrayObject;
	GLuint vertexBuffer;
	GLuint elementBuffer;
};

