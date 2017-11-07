#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include "glad/glad.h"
#include "glm/gtc/matrix_transform.hpp"
#include "texture.h"
#include "color.h"
#include "font.h"
#include "../sources/engine/geometry/point_2d.h"
#include "../sources/engine/geometry/dimension_2d.h"
#include "../sources/engine/graphics/shader_program.h"

class Renderer2D final
{
public:
	/*	Creates a 2d renderer which draws to screen space based on a given shader. */
	Renderer2D(const Dimension2D& displayResolution, const std::string& shadersName) 
		: mProgram("shaders/" + shadersName + ".vs", "shaders/" + shadersName + ".fs"),
		mTextProgram("shaders/text.vs", "shaders/text.fs")
	{ 
		mProgram.compileAndLink();
		mTextProgram.compileAndLink();
		sResolution.update(displayResolution.getWidth(), displayResolution.getHeight());
		setupRenderingData(); 
	}

	/* Renders a sprite's image at a given position and with a given size. */
	void renderSprite(const Texture& image, const Point2D& position, const Dimension2D& size) const;
	
	/* Renders text at a given position and color using specified font. */
	void renderText(const std::string& text, const Font& font, const Point2D& position, const Color& color, float rotation = 0.0f) const;

	//no copy allowed
	Renderer2D(const Renderer2D& nocopy) = delete;
	Renderer2D& operator=(const Renderer2D& nocopy) = delete;

	/*	Destructor. */
	virtual ~Renderer2D() {}

private:
	GLuint mVAO;
	GLuint mTextVAO, mTextVBO;

	ShaderProgram mProgram;
	ShaderProgram mTextProgram;

	static Dimension2D sResolution;

	void setupRenderingData();
};

#endif
