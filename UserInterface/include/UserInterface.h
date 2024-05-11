#pragma once


#include "GLRenderData.h"

class UserInterface {
public:
	void init(GLRenderData& renderData);
	void createFrame(GLRenderData& renderData);
	void render();
	void cleanup();

private:
	float framesPerSecond = 0.0f;
	float averagingAlpha = 0.96f;
};