#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>

class EBO {
public:
	GLuint ID;									// Refrence ID of our EBO
	EBO(GLuint* indices, GLsizeiptr size);		// Constructor

	void Bind();								// Bind the EBO
	void Unbind();								// Unbind the EBO
	void Delete();								// Delete the EBO
};

#endif // !EBO_CLASS_H
