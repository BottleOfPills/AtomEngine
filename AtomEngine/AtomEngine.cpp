#include <include/GLUtils.h>

#include <iostream>

int main()
{
	OpenGLWindow window(800, 600, "Test");

	while (!window.ShouldClose())
	{
		glClear(GL_COLOR_BUFFER_BIT);

		window.SwapBuffers();
		window.PollEvents();
	}

	return 0;
}