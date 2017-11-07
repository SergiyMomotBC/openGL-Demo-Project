#include "texture.h"

#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

Texture::Texture(const std::string & texture)
{
	loadTexture(texture);
}

void Texture::use(unsigned unit) const {
	//use texture if it was successfully uploaded and unit is in correct range
	if (mTexture != 0 && unit >= 0 && unit <= 79) {
		glBindTexture(GL_TEXTURE_2D, mTexture);
		glActiveTexture(GL_TEXTURE0 + unit);
	}
}

void Texture::loadTexture(std::string fileName) 
{
	int width, height;

	//load texture from an image file
	unsigned char* image = stbi_load(fileName.c_str(), &width, &height, nullptr, 4);
	
	//return if image wasn't loaded
	if (!image) {
		std::cerr << "Texture loading failed..." << std::endl;
		return;
	}

	//update texture size
	mSize.update(width, height);

	//allocate texture object
	glGenTextures(1, &mTexture);
	glBindTexture(GL_TEXTURE_2D, mTexture);

	//set texture displaying parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//upload texture data to VRAM
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	//free resources
	stbi_image_free(image);

	//unbind current texture object
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture() {
	glDeleteTextures(1, &mTexture);
}