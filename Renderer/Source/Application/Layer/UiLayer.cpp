#include "stdafx.h"
#include "UiLayer.h"
#include "Application/Application.h"
#include "Renderer/RendererCore/Renderer.h"

UiLayer::UiLayer()
   // :_windowHandle(windowHandle)
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

	ImGui::Begin("Renderer");
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