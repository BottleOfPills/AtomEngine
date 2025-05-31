#include <include/RenderUtils.h>
#include <include/GLUtils.h>

#include <iostream>

int main()
{
	OpenGLWindow window(800, 600, "Test");

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f 
	};

	const char* vertexShaderSource = R"(
		#version 330 core
		layout (location = 0) in vec3 position;
		void main() {
			gl_Position = vec4(position, 1.0);
		}
	)";

	const char* fragmentShaderSource = R"(
		#version 330 core
		out vec4 frag_color;
		void main() {
			frag_color = vec4(1.0, 0.5, 0.2, 1.0);
		}
	)";

	Mesh triangle(vertices, 9);
	Shader triangleShader(vertexShaderSource, fragmentShaderSource);

	while (!window.ShouldClose())
	{
		glClear(GL_COLOR_BUFFER_BIT);

		triangleShader.Use();
		triangle.Draw();

		window.SwapBuffers();
		window.PollEvents();
	}

	return 0;
}