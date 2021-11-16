#include "VBO.h"

// Constructor
VBO::VBO(GLfloat* vertices, GLsizeiptr size) {
	glGenBuffers(1, &ID);												// Assign one element of ID to our buffer
	glBindBuffer(GL_ARRAY_BUFFER, ID);									// Bind the VBO
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);		// Introduce the data (vertices) into the VBO
}

// Bind the VBO
void VBO::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

// Unbind the VBO
void VBO::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Delete the VBO
void VBO::Delete() {
	glDeleteBuffers(1, &ID);
}