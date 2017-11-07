#include "font.h"

#include <iostream>
#include <ft2build.h>
#include FT_FREETYPE_H 

Font::Font(const std::string & fileName, GLuint size)
{
	mSize = size;

	//initialize FreeType library
	FT_Library ft;
	if (FT_Init_FreeType(&ft)) {
		std::cerr << "Could not init FreeType Library..." << std::endl;
		return;
	}

	//create a face from file
	FT_Face face;
	if (FT_New_Face(ft, fileName.c_str(), 0, &face)) {
		std::cerr << "Failed to load font from a given .ttf file..." << std::endl;
		return;
	}

	//set font size
	FT_Set_Pixel_Sizes(face, 0, size);

	//remove openGL default pixel unpacking restriction of 4
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	//loads textures for all 128 ASCII characters, English alphabet
	for (GLubyte c = 0; c < 128; c++)
	{
		// Load character glyph 
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cerr << "Failed to load glyph..." << std::endl;
			continue;
		}

		//texture allocation
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		
		//upload texture data to VRAM
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);
		
		//some texture displaying parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		//create a character object for current glyph with info retrieved form face object
		Character character {
			texture,
			glm::vec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::vec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			static_cast<GLuint>(face->glyph->advance.x)
		};

		//add to map
		mCharacters.insert(std::pair<GLchar, Character>(c, character));
	}

	//FreeType library cleanup
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}

Font::~Font() {
	//delete textures for all characters
	for (auto texture : mCharacters)
		glDeleteTextures(1, &texture.second.textureID);
}
