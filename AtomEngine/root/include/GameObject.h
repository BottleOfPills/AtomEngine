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

	void HandleInput(OpenGLWindow& window, const std::vector<int>& customInput = {})
	{
		if (customInput.empty())
		{
			if (window.IsKeyPressed(GLFW_KEY_A)) transform.Move(-speed, 0);
			if (window.IsKeyPressed(GLFW_KEY_D)) transform.Move(speed, 0);
			if (window.IsKeyPressed(GLFW_KEY_W)) transform.Move(0, speed);
			if (window.IsKeyPressed(GLFW_KEY_S)) transform.Move(0, -speed);
		}
		else if (customInput.size() >= 4)
		{
			if (window.IsKeyPressed(customInput[0])) transform.Move(-speed, 0);
			if (window.IsKeyPressed(customInput[1])) transform.Move(speed, 0);
			if (window.IsKeyPressed(customInput[2])) transform.Move(0, speed);
			if (window.IsKeyPressed(customInput[3])) transform.Move(0, -speed);
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

class Ball : public Renderable
{
public:
	Ball(Mesh* m, Shader* s) : Renderable(m, s) {}

	void Update(Entity& leftPaddle, Entity& rightPaddle)
	{
		transform.Move(velocityX, velocityY);

		glm::vec3 pos = transform.GetPosition();

		if (pos.y > 0.9)
		{
			velocityY = -velocityY;
			transform.SetPosition(pos.x, 0.9);
		}
		if (pos.y < -0.9)
		{
			velocityY = -velocityY;
			transform.SetPosition(pos.x, -0.9);
		}

		if (CheckCollision(pos, leftPaddle.GetTransform().GetPosition()) ||
			CheckCollision(pos, rightPaddle.GetTransform().GetPosition()))
		{
			velocityX = -velocityX;
		}
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
	float velocityX = 0.002;
	float velocityY = 0.002;
};