#include "stdafx.h"
#include "UiLayer.h"
#include "Application/Application.h"
#include "Renderer/RendererCore/Renderer.h"
#include "Renderer/Scene/Scene.h"
#include "Application/UI/ViewModeControl.h"

UiLayer::UiLayer()
{
	_windowHandle = Application::getPtr()->windowHandle();
}

void UiLayer::onAttach()
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); 
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	// io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
	//io.ConfigViewportsNoAutoMerge = true;
	//io.ConfigViewportsNoTaskBarIcon = true;

	// Setup Dear ImGui style
	// ImGui::StyleColorsDark();
	
	ImGui::StyleColorsClassic();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(_windowHandle, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	_width = Application::get().window()->width();
	_height = Application::get().window()->height();

	_buf = new char[_width * _height * 3];
}

void UiLayer::onDetach()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	// Cleanup
	ImGui::DestroyContext();

	if (_buf)
	{
		delete _buf;
		_buf = nullptr;
	}
}

void UiLayer::begin()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

const float toolbarSize = 250;
const float menuBarHeight = 200;


void UiLayer::onUpdate(double deltaTime)
{
	UNUSED(deltaTime);

	// glClear(GL_COLOR_BUFFER_BIT);



	// viewport
#if 1
	ImGui::Begin("Scene Window");

	unsigned int& fbo = RenderGlobal::get()._fbo;

	//glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	ImVec2 pos = ImGui::GetCursorScreenPos();

	ImGui::GetWindowDrawList()->AddImage(
		(void*)fbo,
		ImVec2(ImGui::GetCursorScreenPos()),
		ImVec2(ImGui::GetCursorScreenPos().x + _width, ImGui::GetCursorScreenPos().y + _height ), ImVec2(0, 1), ImVec2(1, 0));

	ImGui::End();
#endif

	UNUSED(deltaTime);

	// View mode
	ViewmodeControl::draw();

	DisplaySettings::draw();

	MenuBar::draw();

	// Light position
	{
	    ImGui::Begin("Default light");
	    glm::vec3& pos = Scene::get().defaultLight()->position();
	    float& lightPower = Scene::get().defaultLight()->lightPower();
	    ImGui::SliderFloat3("Position", glm::value_ptr(pos), -10.0f, 10.f);
	    ImGui::SliderFloat("Light power", &lightPower, 0.f, 1000.f);
	    ImGui::End();
	}

	// Material
	auto currentEntity = RenderGlobal::get()._currentEntity;
	auto materials = Scene::get().getComponent<MeshComponent>(currentEntity).materials();
	Ref<Material> material = materials[0];

	float f32_one = 0.1f;
	ImGui::Begin("Material editor");
	ImGui::ColorEdit3("Ambient Color", glm::value_ptr(material->_ambientColor));
	ImGui::ColorEdit3("Diffuse Color", glm::value_ptr(material->_diffuseColor));
	ImGui::ColorEdit3("Specular Color", glm::value_ptr(material->_specularColor));
	ImGui::InputScalar("Ambient Level", ImGuiDataType_Float, &(material->_ambientLevel), &f32_one);
	ImGui::InputScalar("Glossness", ImGuiDataType_Float, &(material->_glossiness), &f32_one);
	ImGui::InputScalar("Specular Level", ImGuiDataType_Float, &(material->_specularLevel), &f32_one);
	ImGui::End();

	// Information
	ImGui::Begin("Information");
	ImGui::Text("Vendor: %s\nRenderer: %s\nVersion: %s\nFps: %f",
		Renderer::vender(),
		Renderer::rendererName(),
		Renderer::releaseVersion(),
		Application::get().fps());
	ImGui::End();
}

void UiLayer::end()
{

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	ImGui::Render();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	ImGuiIO& io = ImGui::GetIO();

	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}

}

void UiLayer::onEvent(Event& event)
{

}
