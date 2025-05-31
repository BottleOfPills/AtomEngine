#pragma once

#include "common.h"
#include "RenderUtils.h"
#include <vector>

class Transform
{
public:
	Transform() : position(0), rotation(0), scale(0) {}

	void Move(float x, float y)
	{
		position.x += x;
		position.y += y;
	}

	void SetPosition(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	glm::mat4 GetMatrix()
	{
		return glm::translate(glm::mat4(1), position);
	}

	glm::vec3 GetPosition()
	{
		return position;
	}

private:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};
