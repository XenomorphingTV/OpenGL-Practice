#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

// Read our Shaders from file
std::string getFileContents(const char* filename);

class Shader {
public:
	GLuint ID;														// Refrence ID of Shader Program
	Shader(const char* vertexFile, const char* fragmentFile);		// Constructor to build the Shader Program for 2 different Shaders
	void Activate();												// Tell OpenGL which Shader Program to use
	void Delete();													// Delete our Shader Program
};

#endif