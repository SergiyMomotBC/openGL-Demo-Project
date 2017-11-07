#ifndef TEXTURE_H
#define TEXTURE_H	

#include <string>
#include "glad/glad.h"
#include "../sources/engine/geometry/dimension_2d.h"

class Texture
{
public:
	/* Creates a texture from the given image file. */
	Texture(const std::string& textureFile); 

	//no copy allowed
	Texture(const Texture& nocopy) = delete;
	Texture& operator=(const Texture& nocopy) = delete;

	/* Activates and binds the given texture unit. */
	void use(unsigned unit = 0) const;

	/* Texture size getter. */
	Dimension2D getSize() const { return mSize; }

	/* Checks if texture was loaded correctly.  */
	bool isValid() const { return mTexture != 0; }

	/* Destructor. */
	virtual ~Texture();

private:
	GLuint mTexture;
	Dimension2D mSize;

	void loadTexture(std::string fileName);
};

#endif
