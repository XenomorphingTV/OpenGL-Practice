#include "shaderClass.h"

std::string getFileContents(const char* filename) {
	std::ifstream in(filename, std::ios::binary);
	if (in) {
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return contents;
	}
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile) {
	std::string vertexCode = getFileContents(vertexFile);
	std::string fragmentCode = getFileContents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// Create vector shader object and get refrence
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach vertex shader to vector source
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	// Compile the shader into machine code
	glCompileShader(vertexShader);

	// Create fragment shader object and get refrence
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach fragment shader to fragment shader source
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	// Compile the fragment shader into machine code
	glCompileShader(fragmentShader);

	// Create a shader program and get its refrence
	ID = glCreateProgram();

	// Attach vertex shader amd fragment shader to the shader program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	// Wrap/Link shaders into the shader program
	glLinkProgram(ID);

	// Delete the vertex and fragment shaders as they are now in our shader program
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Activate() {
	// Tell OpenGL which Shader Program to use
	glUseProgram(ID);
}

void Shader::Delete() {

	glDeleteProgram(ID);
}