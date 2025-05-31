#pragma once

#include "common.h"
#include "RenderUtils.h"

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

	void HandleInput(OpenGLWindow& window)
	{
		if (window.IsKeyPressed(GLFW_KEY_A)) transform.Move(-speed, 0);
		if (window.IsKeyPressed(GLFW_KEY_D)) transform.Move(speed, 0);
		if (window.IsKeyPressed(GLFW_KEY_W)) transform.Move(0, speed);
		if (window.IsKeyPressed(GLFW_KEY_S)) transform.Move(0, -speed);
	}

	void Render(Shader& shader)
	{
		shader.SetMatrix("transform", transform.GetMatrix());
		shader.Use();
		mesh->Draw();
	}

	glm::mat4 GetTransform() 
	{ 
		return transform.GetMatrix(); 
	}

private:
	float speed = 0.01;
};