#pragma once

#include <memory>
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui_impl_opengl3.h>

#include "Timer.h"
#include "UserInterface.h"
#include "Framebuffer.h"
#include "VertexBuffer.h"
#include "Texture.h"
#include "Shader.h"
#include "Camera.h"
#include "GLRenderData.h"

class GLRenderer {
public:
	bool init(GLFWwindow* window, unsigned int width, unsigned int height);
	void setSize(unsigned int width, unsigned int height);
	void cleanup();
	void uploadData(GLMesh vertexData);
	void draw();

	void handleMouseButtonEvents(int button, int action, int mods);
	void handleMousePositionEvents(double xPos, double yPos);


private:
	GLRenderData mRenderData{};
	UserInterface mUserInterface{};
	Timer mUIGenerateTimer{};

	Shader mShader{};
	FrameBuffer mFrameBuffer{};
	VertexBuffer mVertexBuffer{};
	Texture mTex{};

	std::unique_ptr<Camera> mCamera;
	bool mMouseLock = false;
	int mMouseXPos = 0;
	int mMouseYPos = 0;
};