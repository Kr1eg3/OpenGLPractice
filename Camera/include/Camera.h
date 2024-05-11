#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "Shader.h"
#include "GLRenderData.h"

class Camera
{
public:
	void init(int w, int h, glm::vec3 position);
	void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform);
	void Inputs(GLFWwindow* window);

	glm::mat4 getViewMatrix(GLRenderData& renderData);

	int camW;
	int camH;
	bool firstClick;
	float camSpeed = .1f;
	float camSens = 100.f;

private:
	glm::vec3 mWorldPos = glm::vec3(0.5f, 0.25f, 1.0f);
	glm::vec3 mViewDirection = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 mWorldUpVector = glm::vec3(0.0f, 1.0f, 0.0f);
};