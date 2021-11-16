#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <filesystem>
namespace fs = std::filesystem;

#include "shaderClass.h"
#include "Texture.h"
#include "EBO.h"
#include "VAO.h"
#include "VBO.h"

// Our vertecie points, pre calculated
GLfloat vertices[] = {
	//	Coordinates	     /		 Colours	  /	  texCoord  //
	-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
	-0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
	 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
	 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
};
GLuint indices[] = {
	0, 2, 1,	// Top left triangle
	0, 2, 3		// Lower right triangle
};

int main() {

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
	GLFWwindow* window = glfwCreateWindow(800, 800, "Pop Cat.exe", NULL, NULL);

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

	// Create Shader object with files default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and Element Buffer Object
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	// Link the VBO and VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * (sizeof(float)), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * (sizeof(float)), (void*)(3 * (sizeof(float))));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * (sizeof(float)), (void*)(6 * (sizeof(float))));

	// Unbind the VAO, VBO and EBO in the correct order
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
	

	// Refrence value for our uniform variable
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");


	std::string imageName = "pop_cat.png";
	std::string currentDir = (fs::current_path().string());
	std::string texPath = "\\Resources\\";

	// Texture
	
	Texture popcat((currentDir + texPath + imageName).c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

	popcat.texUnit(shaderProgram, "tex0", 0);

	// To keep the window open, we don't close it until we need to close it
	while (!glfwWindowShouldClose(window)) {
		// Prepare the colour to update
		glClearColor(0.2f, 0.2f, 0.19f, 1.0f);

		// Clear back buffer, assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);

		// Tell OpenGL which Shader Program to use
		shaderProgram.Activate();

		// Assign value to uniform variable
		// MUST BE ASSIGNED AFTER WE ACTIVATE OUR SHADER PROGRAM
		glUniform1f(uniID, 0.5f);

		popcat.Bind();

		// Bind VAO so that OpenGL knows to use it
		VAO1.Bind();

		// Draw triangle with elements and using the GL_TRIANGLES primitive
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		// Use this to update window events such as resize or move
		glfwPollEvents();
	}
	
	// Delete created objects
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	popcat.Delete();
	shaderProgram.Delete();

	// Destroy our window before exiting our program, and terminate glfw
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}