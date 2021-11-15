#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaderClass.h"
#include "EBO.h"
#include "VAO.h"
#include "VBO.h"

int main() {

	// Our vertecie points, pre calculated
	GLfloat vertices[] = {
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,	// Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,		// Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,	// Upper corner
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,	// Inner left
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,	// Inner right
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f		// Inner bottom
	};

	GLuint indices[] = {
		0, 3, 5,	// Lower left triangle
		3, 2, 4,	// Lower right triangle
		5, 4, 1		// top triangle 
	};

	// Initialize our glfw. Every time we exit our program, we need to terminate it
	glfwInit();

	// Here we make our monitor so we can make the window fullscreen windowed
	/*GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	*/
	// We hint at fullscreen windowed
	/*glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	*/

	// Hint at OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Hint at the profile, we only need Core
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create our window with the size, title, and screen type (in this case fullscreen windowed)
	GLFWwindow* window = glfwCreateWindow(800, 800, "My Title", NULL, NULL);

	// If somehow our program didn't create a window, throw an error;
	if(window == NULL){
		std::cout << "Failed to create GLFW window" << std::endl;

		// Exiting here so we terminate out glfw
		glfwTerminate();
		return -1;
	}

	// We need to place our window in context for it to show on our screen
	glfwMakeContextCurrent(window);

	// Telling Glad to load in OpenGL
	gladLoadGL();
	// The area of the window we want open gl to render in
	// In this case we are starting at x = 0, y = 0. And we go until x = 1920, y = 1080
	glViewport(0, 0, 800, 800);

	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkVBO(VBO1, 0);
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// To keep the window open, we don't close it until we need to close it
	while (!glfwWindowShouldClose(window)) {
		// Prepare the colour to update
		glClearColor(0.2f, 0.2f, 0.19f, 1.0f);

		// Clear back buffer, assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);

		// Tell OpenGL which Shader Program to use
		shaderProgram.Activate();

		// Bind VAO so that OpenGL knows to use it
		VAO1.Bind();

		// Draw triangle with elements and using the GL_TRIANGLES primitive
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		// Use this to update window events such as resize or move
		glfwPollEvents();
	}
	
	// Delete created objects
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	// Destroy our window before exiting our program, and terminate glfw
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}