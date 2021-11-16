#include "Texture.h"

// Constructor
Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType) {
	Type = texType;																			// Assigns type of texture to texture object
	int imgWidth, imgHeight, colorChannels;													// Create variables to hold image info
	stbi_set_flip_vertically_on_load(true);													// Image is read from bottom left, we need to flip it vertically so the texture isn't upside down
	unsigned char* bytes = stbi_load(image, &imgWidth, &imgHeight, &colorChannels, 0);		// Import image using stb library

	glGenTextures(1, &ID);			// Generates OpenGL Texture object
	glActiveTexture(slot);			// Assigns texture to a Texture Unit
	glBindTexture(texType, ID);		// Binds the texture

	// Set the texture scaling type, in this case we use nearest
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Set the texture wrap type on the x (s) and y (t) axes, we use the type repeat
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Assigns image to the OpenGL texture object
	glTexImage2D(texType, 0, GL_RGBA, imgWidth, imgHeight, 0, format, pixelType, bytes);

	glGenerateMipmap(texType);
	
	// Deletes the image as it is already stored in the OpenGL Texture Object
	stbi_image_free(bytes);

	// Unbinds texture so it isn't accidentally modified
	glBindTexture(texType, 0);
}


void Texture::texUnit(Shader shader, const char* uniform, GLuint unit) {
	
	// Get location of uniform
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);

	// Need to activate shader before assigning a value of a uniform
	shader.Activate();
	
	// Sets value of the uniform
	glUniform1i(texUni, unit);
}

// Binds Texture
void Texture::Bind() {
	glBindTexture(Type, ID);
}

// Unbinds Texture
void Texture::Unbind() {
	glBindTexture(Type, 0);
}

// Deletes Texture Object
void Texture::Delete() {
	glDeleteTextures(1, &ID);
}