#pragma once
#include <glm/vec4.hpp>
#include <vector>

#include <Windows.h>
#include <gl/GL.h>

struct Vertex
{
	glm::vec4 position;
	glm::vec4 normal;
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

