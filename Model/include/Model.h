#pragma once


#include <vector>
#include <glm/glm.hpp>
#include "GLRenderData.h"

class Model {
public:
	void init();
	GLMesh getVertexData();
private:
	GLMesh mVertexData{};
};