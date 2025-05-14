// This needs to be included before GLFW since the latter relies on some OpenGL headers
#include <glad/glad.h>
#include <GLFW\glfw3.h>

#include <iostream>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

/** Callback function for automatic resize of viewport */
static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

static void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}


int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// This hint is for Mac only and the macro should be defined for gcc compilers on Mac
#if __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// Initilizing the window
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window); // This essentially tells OpenGL to use this window

	// Need to load GLAD stuff before using any OpenGL functions
	// Note that GLAD is not so glad when you load it before creating a window
	// This likely has to do with calling glfwMakeContextCurrent
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return 1;
	}

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT); // Viewport can be smaller than the actual window :)

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}