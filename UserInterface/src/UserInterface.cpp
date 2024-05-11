#include <string>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "UserInterface.h"


void UserInterface::init(GLRenderData& renderData)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(renderData.rdWindow, true);
	const char* glslVersion = "#version 330 core";
	ImGui_ImplOpenGL3_Init(glslVersion);
}

void UserInterface::cleanup()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void UserInterface::createFrame(GLRenderData& renderData)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGuiWindowFlags imguiWindowFlags = 0;
	ImGui::SetNextWindowBgAlpha(0.8f);
	ImGui::Begin("Control", nullptr, imguiWindowFlags);

	// FPS counter
	static float newFps = 0.0f;
	if (renderData.rdFrameTime > 0.0) {
		newFps = 1.0f / renderData.rdFrameTime;
	}
	framesPerSecond = (averagingAlpha * framesPerSecond) + (1.0f - averagingAlpha) * newFps;
	ImGui::Text("FPS:");
	ImGui::SameLine();
	ImGui::Text(std::to_string(framesPerSecond).c_str());
	ImGui::Separator();

	// UI Generation Time counter
	ImGui::Text("UI Generation Time:");
	ImGui::SameLine();
	ImGui::Text(std::to_string(renderData.rdUIGenerateTime).c_str());
	ImGui::SameLine();
	ImGui::Text("ms");
	ImGui::Separator();

	// Triangles counter
	ImGui::Text("Triangles:");
	ImGui::SameLine();
	ImGui::Text(std::to_string(renderData.rdTriangleCount).c_str());
	std::string windowDims = std::to_string(renderData.rdWidth) + "x" + std::to_string(renderData.rdHeight);

	// Window size
	ImGui::Text("Window Dimensions:");
	ImGui::SameLine();
	ImGui::Text(windowDims.c_str());
	std::string imgWindowPos =
		std::to_string(static_cast<int>(
			ImGui::GetWindowPos().x)) + "/" +
		std::to_string(static_cast<int>(
			ImGui::GetWindowPos().y));

	// ImGUI position
	ImGui::Text("ImGui Window Position:");
	ImGui::SameLine();
	ImGui::Text(imgWindowPos.c_str());
	ImGui::End();
}

void UserInterface::render()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}