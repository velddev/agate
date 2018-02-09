#pragma comment(lib, "opengl32.lib")
#define STB_IMAGE_IMPLEMENTATION

#include <string>

#include <glew/glew.h>
#include <glfw/glfw3.h>

#include <imgui/imgui.h>
#include "Editor/ImguiImplementation.h"

#include "Graphics/Shader.h"
#include "Graphics/Model.h"
#include "Graphics/RenderSystem.h"
#include "Graphics/RenderObject.h"
#include "Graphics/Texture.h"

#include "Engine/Resources/AssetManager.h"

#include <iostream>

const char *previewValue = "yo";
char userField[128] = "username";
char passField[128] = "password";

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
	renderSystem->SetAmbientColor({ 1.0f, 1.0f, 1.0f });

	Asset *ico = assetManager->Load<Model>("./assets/ico.fbx");
	Asset *bumbo = assetManager->Load<Texture>("./assets/bumbo.png");
	Asset *shaderAsset = assetManager->AddNew<Shader>(new Shader());

	std::cout << "items in cache: " << assetManager->GetCacheSize() << std::endl;

	Model *model = ico->Get<Model>();
	Shader *shader = shaderAsset->Get<Shader>();

	shader->SetTexture(bumbo->Get<Texture>()->GetHandle());

	GLint vertexShader = Shader::FromFile("./assets/vertex_shader.vs");
	shader->SetVertexShader(vertexShader);

	GLint fragmentShader = Shader::FromFile("./assets/fragment_shader.fs");
	shader->SetFragmentShader(fragmentShader);

	shader->Compile();

	model->SetShader(shader);

	RenderObject *icoObject = renderSystem->AddModel(model);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	printf("starting event loop...\n");

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderSystem->Render();

		ImGui_ImplGlfwGL3_NewFrame();

		ImGui::Begin("bumbo bee");
		ImGui::Image((void*)bumbo->Get<Texture>()->GetHandle(), 
		{ 
			(float)bumbo->Get<Texture>()->GetSize().x, 
			(float)bumbo->Get<Texture>()->GetSize().y 
		});
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