#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <string>
#include "glad/glad.h"

class ShaderProgram
{
public:
	/* Creates a shader program with vertex and fragment shaders. */
	ShaderProgram(std::string vertexShaderFile, std::string fragmentShaderFile);

	/* Compiles shaders and returns true if success. */
	bool compileShaders();

	/* Links shaders to the program and returns true if success. */
	bool linkShaders();

	/* Combines compilation and linking. */
	bool compileAndLink();

	/* Binds shader program if it was successfully compiled and linked. */
	void use() const;

	/* Returns openGL identifier. */
	GLuint getID() const { return mProgram; }

	/* Destructor. Deletes shaders. */
	virtual ~ShaderProgram();

private:
	GLuint mProgram;

	GLuint mVertexShader;
	GLuint mFragmentShader;
	
	bool mLoadSuccess;
	bool mCompileSuccess;
	bool mLinkSuccess;

private:
	std::string getSourceFromFile(std::string fileName);
	bool loadShader(int shaderType, GLuint& shaderVariable, std::string fileName);
	bool compileShader(GLuint shaderVariable);
};

#endif


