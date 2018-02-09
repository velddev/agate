#pragma comment(lib, "opengl32.lib")

#include <string>

#include <glew/glew.h>
#include <glfw/glfw3.h>

#include "Graphics/Shader.h"
#include "Graphics/Model.h"

#include "Engine/Resources/AssetManager.h"

#include <iostream>

int main()
{
	GLFWwindow* window;

	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	AssetManager *assetManager = new AssetManager();
	Asset *ico = assetManager->Load<Model>("./assets/ico.obj");

	std::cout << "items in cache: " << assetManager->GetCacheSize() << std::endl;

	Model *model = ico->Get<Model>();
	Shader *shader = new Shader();

	GLint fragmentShader = Shader::FromFile("fragment_shader.glsl", GL_FRAGMENT_SHADER);
	shader->SetFragmentShader(fragmentShader);

	GLint vertexShader = Shader::FromFile("vertex_shader.glsl", GL_VERTEX_SHADER);
	shader->SetVertexShader(vertexShader);

	shader->Compile();

	model->SetShader(shader);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	printf("starting event loop...\n");

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		model->Draw();

		model->transform->SetPosition(glm::vec3(0.0f, 0.0f, 8.0f));
		model->transform->Rotate(glm::vec3(0.001f, 0.0f, 0.0f));

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}