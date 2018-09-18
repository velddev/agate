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

glm::vec3 clearColor = { 0.0f, 0.0f, 0.0f };

void RenderSystemWindow(RenderSystem *renderSystem)
{
	ImGui::Begin("rendersystem");

	float x = renderSystem->GetAmbientIntensity();
	ImGui::SliderFloat("ambient intensity", &x, 0.0f, 1.0f);
	renderSystem->SetAmbientIntensity(x);

	ImGui::ColorEdit3("background color", &clearColor[0]);

	ImGui::BeginChild("objects", { 0, 120 });

	for (int i = 0; i < renderSystem->GetRenderObjectCount(); i++)
	{
		RenderObject *ro = renderSystem->GetRenderObject(i);

		ImGui::LabelText((std::string("l") + std::to_string(i)).c_str(), "object %i", i);

		ImGui::ColorEdit3("material_ambt" + i, &ro->GetMaterial()->ambient[0]);
		ImGui::InputFloat("material_shin" + i, &ro->GetMaterial()->shininess);

		glm::vec3 pos = ro->GetTransform()->GetPosition();
		glm::vec3 rot = ro->GetTransform()->GetRotation();
		glm::vec3 scl = ro->GetTransform()->GetScale();
		ImGui::InputFloat3("transform_pos" + i, &pos[0]);
		ImGui::InputFloat3("transform_rot" + i, &rot[0]);
		ImGui::InputFloat3("transform_scl" + i, &scl[0]);
		ro->GetTransform()->SetPosition(pos);
		ro->GetTransform()->SetRotation(rot);
		ro->GetTransform()->SetScale(scl);

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

		float range = light->GetRange();
		ImGui::DragFloat("light_range" + i, &range, 0.0f, 100.0f);
		light->SetRange(range);

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

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

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

	icoObject->GetTransform()->SetPosition({ 0.0f, 0.0f, -100.f });


	printf("starting event loop...\n");

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(clearColor.x, clearColor.y, clearColor.z, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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