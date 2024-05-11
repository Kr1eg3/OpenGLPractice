// KlubnichniyEngine.cpp : Defines the entry point for the application.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <memory>
#include <Window.h>
#include <Logger.h>


int main(int argc, char* argv[])
{
	std::unique_ptr<Window> mainWindow = std::make_unique<Window>();
	if (!mainWindow->init(1280, 720, "Test Window")) {
		Logger::log(1, "%s error: Window init error\n",
			__FUNCTION__);
		return -1;
	}

	mainWindow->mainLoop();
	mainWindow->cleanup();
	return 0;
}