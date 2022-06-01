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



}

void UiLayer::onDetach()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	// Cleanup
	ImGui::DestroyContext();
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
	
	
#if 0
	static bool opt_fullscreen = true;
	static bool opt_padding = false;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	ImGuiWindowFlags window_flags = /*ImGuiWindowFlags_MenuBar | */ImGuiWindowFlags_NoDocking;
	if (opt_fullscreen)
	{
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}
	else
	{
		dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
	}

	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;

	bool p_open = true ;
	if (!opt_padding)
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("Docking Space", &p_open, window_flags);
	if (!opt_padding)
		ImGui::PopStyleVar();

	if (opt_fullscreen)
		ImGui::PopStyleVar(2);

	ImGuiID dockspace_id = ImGui::GetID("Docking Space");
	ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

	ImGui::End();


	// viewport
	ImGui::Begin("Scene Window");

	//unsigned int fbo = RenderGlobal::get()._frameBuffer->handle();
	//glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	ImVec2 pos = ImGui::GetCursorScreenPos();

	ImGui::GetWindowDrawList()->AddImage(
		(void*)RenderGlobal::get()._fbo,
		ImVec2(ImGui::GetCursorScreenPos()),
		ImVec2(ImGui::GetCursorScreenPos().x + _width, ImGui::GetCursorScreenPos().y + _height ), ImVec2(0, 1), ImVec2(1, 0));

	ImGui::End();

#endif
	// View mode
	ViewmodeControl::draw();
#if 1

	DisplaySettings::draw();

	//MenuBar::draw();

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
#endif 
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
