#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include "VBO.h"

class VAO {
public:
	GLuint ID;									// Refrence ID of the VAO
	VAO();										// Constructor

	void LinkAttrib(VBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);		// Link the VBO to the VAO
	void Bind();								// Bind the VAO
	void Unbind();								// Unbind the VAO
	void Delete();								// Delete VAO
};



#endif // !VAO_CLASS_H