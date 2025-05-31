#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class OpenGLWindow
{
public:
	OpenGLWindow(int w, int h, const char* title) : width(w), height(h)
	{
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        glfwMakeContextCurrent(window);
        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

        glViewport(0, 0, width, height);
	}
    ~OpenGLWindow() {
        glfwTerminate();
    }

    bool ShouldClose() { return glfwWindowShouldClose(window); }
    void SwapBuffers() { glfwSwapBuffers(window); }
    void PollEvents() { glfwPollEvents(); }
    bool IsKeyPressed(int key) { return glfwGetKey(window, key) == GLFW_PRESS; };
    GLFWwindow* getWindow() { return window; }

private:
    GLFWwindow* window;
    int width, height;
};