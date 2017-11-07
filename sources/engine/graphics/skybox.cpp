#include "skybox.h"

#include <iostream>
#include "stb/stb_image.h"
#include "glm/gtc/type_ptr.hpp"

void Skybox::render(const Camera & camera) const
{
	//depth comparing function should be equal 
	glDepthFunc(GL_LEQUAL);

	mProgram.use();

	//upload view and projection uniforms provided by the camera
	glm::mat4 view = glm::mat4(glm::mat3(camera.getViewMatrix()));
	glm::mat4 projection = camera.getProjectionMatrix();

	glUniformMatrix4fv(glGetUniformLocation(mProgram.getID(), "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(mProgram.getID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	//bind vertex array object and texture object
	glBindVertexArray(mVAO);
	glBindTexture(GL_TEXTURE_CUBE_MAP, mTextureID);
	glActiveTexture(GL_TEXTURE0);

	//upload samplerCube uniform
	GLuint loc = glGetUniformLocation(mProgram.getID(), "cubemap");
	glUniform1i(loc, 0);

	//draw call
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	//restore depth function
	glDepthFunc(GL_LESS);
}

Skybox::~Skybox()
{
	glDeleteTextures(1, &mTextureID);
	glDeleteVertexArrays(1, &mVAO);
}

void Skybox::setup(const std::vector<std::string>& faces)
{
	mProgram.compileAndLink();

	glGenTextures(1, &mTextureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, mTextureID);

	int width, height;
	unsigned char* image;

	//load all faces from files and upload image data to VRAM
	for (GLuint i = 0; i < faces.size(); ++i) {
		image = stbi_load(faces[i].c_str(), &width, &height, nullptr, 4);

		if (!image) {
			std::cerr << "Texture loading failed..." << std::endl;
			return;
		}

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA,
					 width, height, 0,
					 GL_RGBA, GL_UNSIGNED_BYTE, image);

		delete image;
	}

	//some texture parameters, texture wrap should be GL_CLAMP_TO_EDGE for cube to look seamless
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

	//cube vertices
	GLfloat vertices[] = {
		-1.0f,  1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f, 1.0f,  1.0f, -1.0f, -1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f, -1.0f,  1.0f,  1.0f, -1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f, 1.0f, -1.0f,  1.0f, 1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f, 1.0f,  1.0f, -1.0f, 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,-1.0f, 1.0f,  1.0f, 1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f, 1.0f, -1.0f,  1.0f, -1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f, 1.0f,  1.0f, -1.0f, 1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f, 1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f, 1.0f, -1.0f,  1.0f
	};

	//buffer data uploading
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}
