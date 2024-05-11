#include "VertexBuffer.h"

void VertexBuffer::init()
{
	glGenVertexArrays(1, &mVAO);
	glGenBuffers(1, &mVertexVBO);
	glBindVertexArray(mVAO);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
		sizeof(GLVertex),
		(void*)offsetof(GLVertex, position));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
		sizeof(GLVertex),
		(void*)offsetof(GLVertex, color));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
		sizeof(GLVertex),
		(void*)offsetof(GLVertex, uv));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void VertexBuffer::cleanup()
{
	glDeleteBuffers(1, &mVertexVBO);
	glDeleteVertexArrays(1, &mVAO);
}

void VertexBuffer::uploadData(GLMesh vertexData)
{
	glBindVertexArray(mVAO);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexVBO);
	glBufferData(GL_ARRAY_BUFFER, vertexData.vertices.size()
		* sizeof(GLVertex), &vertexData.vertices.at(0),
		GL_DYNAMIC_DRAW);
	glBindVertexArray(0);
}

void VertexBuffer::bind()
{
	glBindVertexArray(mVAO);
}

void VertexBuffer::unbind()
{
	glBindVertexArray(0);
}

void VertexBuffer::draw(GLuint mode, unsigned int start, unsigned int num)
{
	glDrawArrays(mode, start, num);
}