#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include <include/RenderUtils.h>
#include <include/GLUtils.h>

int main()
{
	OpenGLWindow window(800, 600, "Test");

	float triangleVertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f 
	};

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

	// float planeVertices[] = {
	// 	-0.5f, -0.5f, 0.0f,
	// 	 0.5f, -0.5f, 0.0f,
	// 	 0.5f,  0.5f, 0.0f,
	// 
	// 	-0.5f, -0.5f, 0.0f,
	// 	 0.5f,  0.5f, 0.0f,
	// 	-0.5f,  0.5f, 0.0f 
	// };

	// Mesh triangle(triangleVertices, 9);
	// Mesh plane(planeVertices, 18);
	// Shader planeShader(vertexShaderSource, fragmentShaderSource);

	// Inefficient ^, wastes 2 vertices because vertex 4 is a duplicate of vertex 1 and vertex 5 is a duplicate of vertex 3

	float planeVertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f 
	};

	unsigned int planeIndices[] = {
		0, 1, 2,
		0, 2, 3 
	};

	Mesh plane(planeVertices, 12, planeIndices, 6);
	Shader planeShader(vertexShaderSource, fragmentShaderSource);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	float posX, posY = 0;
	
	while (!window.ShouldClose())
	{
		if (window.IsKeyPressed(GLFW_KEY_A)) posX -= 0.01f;
		if (window.IsKeyPressed(GLFW_KEY_D)) posX += 0.01f;
		if (window.IsKeyPressed(GLFW_KEY_W)) posY += 0.01f;
		if (window.IsKeyPressed(GLFW_KEY_S)) posY -= 0.01f;

		glm::mat4 transform = glm::translate(glm::mat4(1.0), glm::vec3(posX, posY, 0));

		glClear(GL_COLOR_BUFFER_BIT);
		planeShader.Use();

		int transformLoc = glGetUniformLocation(planeShader.GetProgramId(), "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

		plane.Draw();
		window.SwapBuffers();
		window.PollEvents();
	}

	return 0;
}