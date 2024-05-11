#include "Camera.h"


void Camera::init(int _w, int _h, glm::vec3 _position)
{
	camW = _w;
	camH = _h;
	firstClick = true;
	mWorldPos = _position;
}

void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform)
{
	glm::mat4 view = glm::mat4(1.f);
	glm::mat4 projection = glm::mat4(1.f);

	view = glm::lookAt(mWorldPos, mWorldPos + mViewDirection, mWorldUpVector);
	projection = glm::perspective(glm::radians(FOVdeg), static_cast<float>(camW) / camH, nearPlane, farPlane);
	glUniformMatrix4fv(glGetUniformLocation(shader.getShaderProgramID(), uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
}

void Camera::Inputs(GLFWwindow* window)
{
	// Handles key inputs
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		mWorldPos += camSpeed * mViewDirection;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		mWorldPos += camSpeed * -glm::normalize(glm::cross(mViewDirection, mWorldUpVector));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		mWorldPos += camSpeed * -mViewDirection;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		mWorldPos += camSpeed * glm::normalize(glm::cross(mViewDirection, mWorldUpVector));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		mWorldPos += camSpeed * mWorldUpVector;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		mWorldPos += camSpeed * -mWorldUpVector;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		camSpeed = 0.4f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		camSpeed = 0.1f;
	}

	// Handles mouse inputs
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		// Hides mouse cursor
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		// Prevents camera from jumping on the first click
		if (firstClick)
		{
			glfwSetCursorPos(window, (camW / 2), (camH / 2));
			firstClick = false;
		}

		// Stores the coordinates of the cursor
		double mouseX;
		double mouseY;
		// Fetches the coordinates of the cursor
		glfwGetCursorPos(window, &mouseX, &mouseY);

		// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
		// and then "transforms" them into degrees
		float rotX = camSens * (float)(mouseY - (camH / 2)) / camH;
		float rotY = camSens * (float)(mouseX - (camW / 2)) / camW;

		// Calculates upcoming vertical change in the Orientation
		glm::vec3 newOrientation = glm::rotate(mViewDirection, glm::radians(-rotX), glm::normalize(glm::cross(mViewDirection, mWorldUpVector)));

		// Decides whether or not the next vertical Orientation is legal or not
		if (abs(glm::angle(newOrientation, mWorldUpVector) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			mViewDirection = newOrientation;
		}

		// Rotates the Orientation left and right
		mViewDirection = glm::rotate(mViewDirection, glm::radians(-rotY), mWorldUpVector);

		// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
		glfwSetCursorPos(window, (camW / 2), (camH / 2));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		// Unhides cursor since camera is not looking around anymore
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		// Makes sure the next time the camera looks around it doesn't jump
		firstClick = true;
	}
}

glm::mat4 Camera::getViewMatrix(GLRenderData& renderData)
{
	float azimRad = glm::radians(renderData.rdViewAzimuth);
	float elevRad = glm::radians(renderData.rdViewElevation);
	float sinAzim = glm::sin(azimRad);
	float cosAzim = glm::cos(azimRad);
	float sinElev = glm::sin(elevRad);
	float cosElev = glm::cos(elevRad);
	mViewDirection = glm::normalize(glm::vec3(sinAzim * cosElev, sinElev, -cosAzim * cosElev));

	return glm::lookAt(mWorldPos, mWorldPos + mViewDirection, mWorldUpVector);
}
