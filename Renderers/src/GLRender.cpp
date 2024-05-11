#include "GLRender.h"
#include <Logger.h>
#include <imgui_impl_glfw.h>


bool GLRenderer::init(GLFWwindow* window, unsigned int width, unsigned int height)
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return false;
	}

	if (!GLAD_GL_VERSION_3_3) {
		Logger::log(1, "%s error: Incorrect GLAD version, needed 3.3!\n",
			__FUNCTION__);
		return false;
	}

	if (!mFrameBuffer.init(width, height)) {
		Logger::log(1, "%s error: FrameBuffer init error!\n",
			__FUNCTION__);
		return false;
	}

	if (!mTex.loadTexture("D:/CPP/KlubnichniyEngine/Textures/brick.png")) {
		Logger::log(1, "%s error: Cannot load proper texture!\n",
			__FUNCTION__);
		return false;
	}

	mVertexBuffer.init();
	if (!mShader.loadShaders("D:/CPP/KlubnichniyEngine/Shaders/default.vert",
		"D:/CPP/KlubnichniyEngine/Shaders/default.frag")) {
		Logger::log(1, "%s error: Cannot load proper shaders!\n",
			__FUNCTION__);
		return false;
	}

	mCamera = std::make_unique<Camera>();
	mCamera->init(width, height, glm::vec3(.0f, .0f, 2.f));
	mRenderData.rdWindow = window;
	mRenderData.rdHeight = height;
	mRenderData.rdWidth = width;

	mUserInterface.init(mRenderData);

	return true;
}

void GLRenderer::setSize(unsigned int width, unsigned int height)
{
	mFrameBuffer.resize(width, height);
	glViewport(0, 0, width, height);
}

void GLRenderer::uploadData(GLMesh vertexData)
{
	mRenderData.rdTriangleCount = vertexData.vertices.size();
	mVertexBuffer.uploadData(vertexData);
}

void GLRenderer::draw()
{
	if (!mRenderData.rdWindow) {
		Logger::log(1, "%s error: Window == NULL, renderer cannot draw anything!\n",
			__FUNCTION__);
		return;
	}

	static float prevFrameStartTime = 0.0;
	float frameStartTime = glfwGetTime();

	ImGuiIO& io = ImGui::GetIO();
	if (!io.WantCaptureMouse)
	{
		mCamera->Inputs(mRenderData.rdWindow);
	}

	mFrameBuffer.bind();
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_CULL_FACE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	mShader.use();
	mCamera->Matrix(45.f, .1f, 100.f, mShader, "camMatrix");
	mVertexBuffer.bind();
	mTex.bind();
	mVertexBuffer.draw(GL_TRIANGLES, 0, mRenderData.rdTriangleCount);
	mVertexBuffer.unbind();
	mTex.unbind();
	mFrameBuffer.unbind();
	mFrameBuffer.drawToScreen();

	mUIGenerateTimer.start();
	mUserInterface.createFrame(mRenderData);
	mRenderData.rdUIGenerateTime = mUIGenerateTimer.stop();
	mUserInterface.render();

	mRenderData.rdFrameTime = frameStartTime - prevFrameStartTime;
	prevFrameStartTime = frameStartTime;
}

void GLRenderer::handleMouseButtonEvents(int button, int action, int mods)
{
	ImGuiIO& io = ImGui::GetIO();
	if (button >= 0 && button < ImGuiMouseButton_COUNT) {
		io.AddMouseButtonEvent(button, action == GLFW_PRESS);
	}
	if (io.WantCaptureMouse) {
		return;
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
		mMouseLock = !mMouseLock;
		if (mMouseLock) {
			glfwSetInputMode(mRenderData.rdWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			if (glfwRawMouseMotionSupported()) {
				glfwSetInputMode(mRenderData.rdWindow, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
			}
		}
		else {
			glfwSetInputMode(mRenderData.rdWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}
}

void GLRenderer::handleMousePositionEvents(double xPos, double yPos)
{
	ImGuiIO& io = ImGui::GetIO();
	io.AddMousePosEvent((float)xPos, (float)yPos);
	if (io.WantCaptureMouse) {
		return;
	}
	int mouseMoveRelX = static_cast<int>(xPos) - mMouseXPos;
	int mouseMoveRelY = static_cast<int>(yPos) - mMouseYPos;
	if (mMouseLock) {
		mRenderData.rdViewAzimuth += mouseMoveRelX / 10.0;
		if (mRenderData.rdViewAzimuth < 0.0) {
			mRenderData.rdViewAzimuth += 360.0;
		}
		if (mRenderData.rdViewAzimuth >= 360.0) {
			mRenderData.rdViewAzimuth -= 360.0;
		}
		mRenderData.rdViewElevation -= mouseMoveRelY / 10.0;
		if (mRenderData.rdViewElevation > 89.0) {
			mRenderData.rdViewElevation = 89.0;
		}
		if (mRenderData.rdViewElevation < -89.0) {
			mRenderData.rdViewElevation = -89.0;
		}
	}
	mMouseXPos = static_cast<int>(xPos);
	mMouseYPos = static_cast<int>(yPos);
}

void GLRenderer::cleanup() {
	mUserInterface.cleanup();
	mShader.cleanup();
	//mTex.cleanup();
	mVertexBuffer.cleanup();
	mFrameBuffer.cleanup();
}