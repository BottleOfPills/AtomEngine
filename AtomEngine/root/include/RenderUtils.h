#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

class Mesh
{
public:
	Mesh(float* vertices, int count, unsigned int* indices, int indexCount) : vertexCount(count)
	{
		if (indices)
		{
			usesIndices = true;
		}

		if (usesIndices)
		{
			printf("Drawing %d indices (triangles: %d)\n", vertexCount, vertexCount / 3);
		}
		else
		{
			printf("Drawing %d vertices (%d triangles)\n", vertexCount / 3, (vertexCount / 3) / 3);
		}

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);
	}
	~Mesh()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}

	void Draw()
	{
		glBindVertexArray(VAO);
		if (usesIndices) 
		{
			glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, 0);
		}
		else
		{
			glDrawArrays(GL_TRIANGLES, 0, vertexCount / 3);
		}
	}

private:
	unsigned int VAO, VBO, EBO;
	int vertexCount;
	bool usesIndices;
};

class Shader
{
public:
    Shader(const char* vertex_source, const char* fragment_source)
	{
        unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader, 1, &vertex_source, nullptr);
        glCompileShader(vertex_shader);

        unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_shader, 1, &fragment_source, nullptr);
        glCompileShader(fragment_shader);

        programId = glCreateProgram();
        glAttachShader(programId, vertex_shader);
        glAttachShader(programId, fragment_shader);
        glLinkProgram(programId);

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
    }
	~Shader() 
	{
		glDeleteProgram(programId);
	}

    void Use() 
	{
        glUseProgram(programId);
    }
private:
	unsigned int programId;
};