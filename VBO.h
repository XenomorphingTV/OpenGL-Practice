#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>

class VBO {
public:
	GLuint ID;									// Refrence ID of our VBO
	VBO(GLfloat* vertices, GLsizeiptr size);	// Constructor

	void Bind();								// Bind the VBO
	void Unbind();								// Unbind the VBO
	void Delete();								// Delete the VBO
};

#endif // !VBO_CLASS_H

