#pragma once

#include <memory>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "GLRender.h"
#include "Model.h"

class Window {
public:
	bool init(unsigned int width, unsigned int height, std::string title);
	void mainLoop();
	void cleanup();
	void handleKeyEvents(int key, int scancode, int action, int mods);
	void framebuffer_size_callback(GLFWwindow* window, int width, int height); // remove GLFWwindow* window from func args


private:
	void handleMouseButtonEvents(int button, int action, int mods);



	GLFWwindow* mWindow = nullptr;
	std::unique_ptr<GLRenderer> mRenderer;
	std::unique_ptr<Model> mModel;
};