#pragma once

#include "common.h"
#include "RenderUtils.h"
#include "Transform.h"

class Renderable
{
public:
	Renderable(Mesh* m, Shader* s) : mesh(m), shader(s) {}

	virtual void Render()
	{
		shader->Use();
		shader->SetMatrix("transform", transform.GetMatrix());
		mesh->Draw();
	}

	Transform& GetTransform()
	{
		return transform;
	}

protected:
	Mesh* mesh;
	Shader* shader;
	Transform transform;
};

class Entity : public Renderable
{
public:
	Entity(Mesh* m, Shader* s) : Renderable(m, s) {}

	void HandleInput(OpenGLWindow& window, const std::array<int, 4>& customInput = { GLFW_KEY_A, GLFW_KEY_D, GLFW_KEY_W, GLFW_KEY_S })
	{
		std::array<int, 4> keys = customInput.empty() ?
			std::array<int, 4>{GLFW_KEY_A, GLFW_KEY_D, GLFW_KEY_W, GLFW_KEY_S} :
			std::array<int, 4>{ customInput[0], customInput[1], customInput[2], customInput[3] };

		std::array<glm::vec2, 4> movements = {
			glm::vec2(-speed, 0),
			glm::vec2(speed, 0), 
			glm::vec2(0, speed), 
			glm::vec2(0, -speed) 
		};

		for (auto [i, key] : std::views::enumerate(keys)) 
		{
			if (window.IsKeyPressed(key)) 
			{
				transform.Move(movements[i].x, movements[i].y);
			}
		}
	}

	glm::mat4 GetMatrix()
	{
		return transform.GetMatrix();
	}

	bool CheckCollision(glm::vec3 ballPos, glm::vec3 paddlePos)
	{
		float ballWidth = 0.04f;
		float ballHeight = 0.04f;

		float paddleWidth = 0.04f;
		float paddleHeight = 0.2f;

		bool xOverlap = (ballPos.x < paddlePos.x + paddleWidth / 2) &&
			(ballPos.x + ballWidth / 2 > paddlePos.x);

		bool yOverlap = (ballPos.y < paddlePos.y + paddleHeight / 2) &&
			(ballPos.y + ballHeight / 2 > paddlePos.y);

		return xOverlap && yOverlap;
	}

private:
	float speed = 0.01;
};