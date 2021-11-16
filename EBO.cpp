#include "EBO.h"

// Constructor
EBO::EBO(GLuint* indices, GLsizeiptr size) {
	glGenBuffers(1, &ID);														// Assign one element of ID to our buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);									// Bind the VBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);		// Introduce the data (vertices) into the VBO
}

// Bind the EBO
void EBO::Bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

// Unbind the EBO
void EBO::Unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// Delete the EBO
void EBO::Delete() {
	glDeleteBuffers(1, &ID);
}