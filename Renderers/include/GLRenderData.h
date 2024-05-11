#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

struct GLVertex {
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 uv;
};
struct GLMesh {
	std::vector<GLVertex> vertices;
};

struct GLRenderData {
	GLFWwindow* rdWindow = nullptr;
	unsigned int rdWidth = 0;
	unsigned int rdHeight = 0;
	unsigned int rdTriangleCount = 0;
	float rdFrameTime = 0.0f;
	float rdUIGenerateTime = 0.0f;
	float rdViewAzimuth = 320.0f;
	float rdViewElevation = -15.0f;
};