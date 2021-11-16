#include "VAO.h"

// Constructor
VAO::VAO() {
	glGenVertexArrays(1, &ID);		// Bind the VAO
}

// Link the VBO to the VAO
void VAO::LinkAttrib(VBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) {
	VBO.Bind();																				// Bind the VBO
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);			// Input vertex data
	glEnableVertexAttribArray(layout);														// Enable our vertex data
	VBO.Unbind();																			// Unbind the VBO
}

// Bind the VAO
void VAO::Bind() {
	glBindVertexArray(ID);
}

// Unbind the VAO
void VAO::Unbind() {
	glBindVertexArray(0);
}

// Delete the VAO
void VAO::Delete() {
	glDeleteVertexArrays(1, &ID);
}