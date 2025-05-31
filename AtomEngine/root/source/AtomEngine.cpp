#include <include/GLUtils.h>
#include <include/RenderUtils.h>
#include <include/GameObject.h>

int main()
{
	OpenGLWindow window(800, 600, "Test");

	const char* vertexShaderSource = R"(
		#version 330 core
		layout (location = 0) in vec3 position;
		uniform mat4 transform;
		void main() {
			gl_Position = transform * vec4(position, 1.0);
		}
	)";

	const char* fragmentShaderSource = R"(
		#version 330 core
		out vec4 frag_color;
		void main() {
			frag_color = vec4(1.0, 0.5, 0.2, 1.0);
		}
	)";


	float paddleVertices[] = {
		-0.02f, -0.1f, 0.0f,
		 0.02f, -0.1f, 0.0f,
		 0.02f,  0.1f, 0.0f,
		-0.02f,  0.1f, 0.0f
	};
	unsigned int paddleIndices[] = { 0, 1, 2, 0, 2, 3 };

	float ballVertices[] = {
		-0.02f, -0.02f, 0.0f,
		 0.02f, -0.02f, 0.0f,
		 0.02f,  0.02f, 0.0f,
		-0.02f,  0.02f, 0.0f
	};

	Mesh ballMesh(ballVertices, 12, paddleIndices, 6);

	Mesh paddleMesh(paddleVertices, 12, paddleIndices, 6);
	Shader shader(vertexShaderSource, fragmentShaderSource);

	Ball ball(&ballMesh, &shader);
	Entity leftPaddle(&paddleMesh, &shader);
	Entity rightPaddle(&paddleMesh, &shader);

	leftPaddle.GetTransform().SetPosition(-0.9f, 0.0f);
	rightPaddle.GetTransform().SetPosition(0.9f, 0.0f);
	ball.GetTransform().SetPosition(0.0f, 0.0f);

	while (!window.ShouldClose())
	{
		leftPaddle.HandleInput(window);
		rightPaddle.HandleInput(window, { GLFW_KEY_LEFT, GLFW_KEY_RIGHT, GLFW_KEY_UP, GLFW_KEY_DOWN });
		ball.Update(leftPaddle, rightPaddle);

		glClear(GL_COLOR_BUFFER_BIT);

		leftPaddle.Render();
		rightPaddle.Render();
		ball.Render();

		window.SwapBuffers();
		window.PollEvents();
	}

	return 0;
}