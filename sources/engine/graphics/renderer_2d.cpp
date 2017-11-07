#include "renderer_2d.h"

#include "glm/gtc/type_ptr.hpp"

Dimension2D Renderer2D::sResolution;

void Renderer2D::renderSprite(const Texture & image, const Point2D & position, const Dimension2D & size) const
{
	mProgram.use();

	image.use();

	//orthogonal projection is used for 2d rendering
	glm::mat4 projection = glm::ortho(0.0f, (float)sResolution.getWidth(), 0.0f, (float)sResolution.getHeight());

	//scale represents the size of sprite and translate represent position 
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(position.getX(), position.getY(), 0.0f));
	model = glm::scale(model, glm::vec3(size.getWidth(), size.getHeight(), 1.0f));

	//upload uniforms
	GLuint modelLoc = glGetUniformLocation(mProgram.getID(), "model");
	GLuint projLoc = glGetUniformLocation(mProgram.getID(), "projection");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	//for 2d drawing depth test should be disabled
	glDisable(GL_DEPTH_TEST);

	//draw call
	glBindVertexArray(mVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

	//restore depth test
	glEnable(GL_DEPTH_TEST);
}

void Renderer2D::renderText(const std::string & text, const Font & font, const Point2D & position, const Color & color, float rotation) const
{
	//scale is forbidden since it causes some blurry text to be displayed
	float x = 0.0f, y = 0.0f, scale = 1.0f;

	mTextProgram.use();

	//text position and orientation
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(position.getX(), position.getY(), 0.0f));
	model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));

	//orthogonal projection is used
	glm::mat4 projection = glm::ortho(0.0f, (float)sResolution.getWidth(), 0.0f, (float)sResolution.getHeight());

	//uniforms
	GLuint projLoc = glGetUniformLocation(mTextProgram.getID(), "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	GLuint modelLoc = glGetUniformLocation(mTextProgram.getID(), "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	//text color uniform
	glUniform3f(
		glGetUniformLocation(mTextProgram.getID(), "textColor"), 
		color.getRedChannel(), 
		color.getGreenChannel(), 
		color.getBlueChannel()
	);

	//use text vertex array object and first texture unit
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(mTextVAO);

	//no depth test
	glDisable(GL_DEPTH_TEST);

	//render character by character for all characters in the text 
	for (GLuint i = 0; i < text.length(); ++i)
	{
		//get glyphs attributes from a specific font
		Character ch = font.getCharacterGlyph(text[i]);

		//position including char bearing and size
		GLfloat xpos = x + ch.bearing.x * scale;
		GLfloat ypos = y - (ch.size.y - ch.bearing.y) * scale;

		//width and hight from character' attributes
		GLfloat w = ch.size.x * scale;
		GLfloat h = ch.size.y * scale;
		
		//vertices for a character glyph
		GLfloat vertices[6][4] = {
			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos,     ypos,       0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 1.0 },

			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 0.0 }
		};
		
		//bind characters texture object
		glBindTexture(GL_TEXTURE_2D, ch.textureID);

		//upload buffer data
		glBindBuffer(GL_ARRAY_BUFFER, mTextVBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		
		//draw call
		glDrawArrays(GL_TRIANGLES, 0, 6);
		
		//calculate next char x position
		x += (ch.advance >> 6) * scale; //bitshift by 6 to get value in pixels (2^6 = 64)
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glEnable(GL_DEPTH_TEST);
}

void Renderer2D::setupRenderingData()
{
	//rectangle vertices' positions and texture coordinates
	GLfloat vertices[] = {
		0.0f, 1.0f, 0.01f, 0.99f,
		1.0f, 0.0f, 0.99f, 0.01f,
		0.0f, 0.0f, 0.01f, 0.01f,
		0.0f, 1.0f, 0.01f, 0.99f,
		1.0f, 1.0f, 0.99f, 0.99f,
		1.0f, 0.0f, 0.99f, 0.01f
	};

	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

	//upload buffer data
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//position and texture coordinates will be submitted as one vec4 attribute
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//text related vertex array object
	glGenVertexArrays(1, &mTextVAO);
	glGenBuffers(1, &mTextVBO);

	glBindVertexArray(mTextVAO);
	glBindBuffer(GL_ARRAY_BUFFER, mTextVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
	
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
