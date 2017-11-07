#ifndef FONT_H
#define FONT_H

#include <map>
#include "glad/glad.h"
#include "glm/glm.hpp"

/* Character glyph attributes used for FreeType library. */
struct Character {
	GLuint     textureID;
	glm::ivec2 size;
	glm::ivec2 bearing;
	GLuint     advance;
};

class Font
{
public:
	/* Creates a font object from a given .ttf file and with given size */
	Font(const std::string& fileName, GLuint size = 24);

	/* Returns character attributes for a given glyph. */
	Character getCharacterGlyph(char glyph) const { return mCharacters.at(glyph); }

	/* Destructor destroys all textures associated with glyphs. */
	virtual ~Font();

private:
	GLuint mSize;
	std::map<char, Character> mCharacters;
};

#endif
