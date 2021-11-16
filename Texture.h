#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <glad/glad.h>
#include <stb/stb_image.h>

#include "shaderClass.h"

class Texture {
public:
	GLuint ID;		// Reference ID of our Texture
	GLenum Type;	// Shader type

	// Constructor
	Texture(const char* image, GLenum textureType, GLenum slot, GLenum format, GLenum pixelType);

	void texUnit(Shader shader, const char* uniform, GLuint unit);		// Assigns texture unit to texture
	void Bind();														// Bind Texture
	void Unbind();														// Unbind Texture
	void Delete();														// Delete Texture Object
};

#endif // !TEXTURE_CLASS_H

