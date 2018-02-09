#pragma comment(lib, "opengl32.lib")

#include <string>

#include <glew/glew.h>
#include <glfw/glfw3.h>

#include <imgui/imgui.h>
#include "Editor/ImguiImplementation.h"

#include "Graphics/Shader.h"
#include "Graphics/Model.h"
#include "Graphics/RenderSystem.h"

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
	glfwSwapInterval(1);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplGlfwGL3_Init(window, true);

	ImGui::StyleColorsDark();


	AssetManager *assetManager = new AssetManager();
	RenderSystem *renderSystem = new RenderSystem();

	GLuint target = renderSystem->CreateRenderTarget();
	//renderSystem->UseRenderTarget(target, glm::vec2(640, 480));

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

	renderSystem->Add(model);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	printf("starting event loop...\n");

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderSystem->Render();

		model->transform->SetPosition(glm::vec3(0.0f, 0.0f, 8.0f));
		model->transform->Rotate(glm::vec3(0.001f, 0.0f, 0.0f));

		
		ImGui_ImplGlfwGL3_NewFrame();
		
		ImGui::Begin("window");

		ImGui::Button("Hi");

		ImGui::End();

		ImGui::Render();

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}