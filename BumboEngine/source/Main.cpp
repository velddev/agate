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

void RenderSystemWindow(RenderSystem *renderSystem)
{
	ImGui::Begin("rendersystem");

	float x = renderSystem->GetAmbientIntensity();
	ImGui::SliderFloat("ambient intensity", &x, 0.0f, 1.0f);
	renderSystem->SetAmbientIntensity(x);

	glm::vec3 y = renderSystem->GetAmbientColor();
	ImGui::ColorEdit3("ambient color", &y[0]);
	renderSystem->SetAmbientColor(y);

	ImGui::BeginChild("objects", { 0, 120 });

	for (int i = 0; i < renderSystem->GetRenderObjectCount(); i++)
	{
		RenderObject *ro = renderSystem->GetRenderObject(i);

		ImGui::LabelText((std::string("l") + std::to_string(i)).c_str(), "object %i", i);

		ImGui::ColorEdit3("material_ambt" + i, &ro->GetMaterial()->ambient[0]);
//		ImGui::ImageButton((void*)ro->GetMaterial()->diffuse->GetHandle(), {100, 100});
//		ImGui::ImageButton((void*)ro->GetMaterial()->specular->GetHandle(), { 100, 100 });
		ImGui::InputFloat("material_shin" + i, &ro->GetMaterial()->shininess);

		ImGui::Spacing();
	}

	ImGui::EndChild();

	ImGui::BeginChild("lghts", { 0, 120 });

	for (int i = 0; i < renderSystem->GetLightCount(); i++)
	{
		PointLight *light = renderSystem->GetLight(i);

		ImGui::LabelText((std::string("l") + std::to_string(i)).c_str(), "light %i", i);

		glm::vec3 pos = light->GetTransform()->GetPosition();
		ImGui::SliderFloat3("light_pos" + i, &pos[0], -100.0f, 100.0f);
		light->GetTransform()->SetPosition(pos);

		glm::vec3 col = light->GetColor();
		ImGui::ColorEdit3("light_col" + i, &col[0]);
		light->SetColor(col);

		float intensity = light->GetIntensity();
		ImGui::DragFloat("light_int" + i, &intensity, 0.0f, 1.0f);
		light->SetIntensity(intensity);

		ImGui::Spacing();
	}

	ImGui::EndChild();

	ImGui::LabelText("", "total lights: %i", renderSystem->GetLightCount());
	ImGui::SameLine();
	if (ImGui::Button("new light"))
	{
		renderSystem->AddLight(new PointLight());
	}

	ImGui::End();
}

int main()
{
	GLFWwindow* window;

	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(640, 480, "Bumbo engine", NULL, NULL);
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
	Asset *bumbo = assetManager->Load<Texture>("./assets/container2.png");
	Asset *specularMap = assetManager->Load<Texture>("./assets/container2_specular.png");
	Asset *shaderAsset = assetManager->AddNew<Shader>(new Shader());

	std::cout << "items in cache: " << assetManager->GetCacheSize() << std::endl;

	Model *model = ico->Get<Model>();
	Shader *shader = shaderAsset->Get<Shader>();

	shader->SetTexture(bumbo->Get<Texture>()->GetHandle(), 0);
	shader->SetTexture(specularMap->Get<Texture>()->GetHandle(), 1);

	GLint vertexShader = Shader::FromFile("./assets/vertex_shader.vert");
	shader->SetVertexShader(vertexShader);

	GLint fragmentShader = Shader::FromFile("./assets/fragment_shader.frag");
	shader->SetFragmentShader(fragmentShader);

	shader->Compile();

	model->SetShader(shader);

	RenderObject *icoObject = renderSystem->Add(model);

	icoObject->GetTransform()->SetPosition({ 0.0f, 0.0f, -75.f });

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	printf("starting event loop...\n");

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		icoObject->GetTransform()->Rotate({ 0.005f, 0.0f, 0.0f });

		renderSystem->Render();

		ImGui_ImplGlfwGL3_NewFrame();

		RenderSystemWindow(renderSystem);
	
		ImGui::Render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}