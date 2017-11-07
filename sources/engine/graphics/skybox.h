#ifndef SKYBOX_H
#define SKYBOX_H

#include <string>
#include <vector>
#include "../sources/engine/graphics/shader_program.h"
#include "../sources/engine/graphics/camera.h"

class Skybox
{
public:
	/* Creates a skybox object from six faces given by files. */
	Skybox(const std::vector<std::string> faces, const std::string& shadersName)
		: mProgram(shadersName + ".vs", shadersName + ".fs")
	{ setup(faces); }

	/* Draws skybox using given 3d camera. */
	void render(const Camera& camera) const;

	/* Destructor frees all texture resources. */
	virtual ~Skybox();

private:
	GLuint mTextureID;
	GLuint mVAO;
	ShaderProgram mProgram;

	void setup(const std::vector<std::string>& faces);
};

#endif

