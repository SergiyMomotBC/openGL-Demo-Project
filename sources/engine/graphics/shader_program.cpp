#include "shader_program.h"

#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>

ShaderProgram::ShaderProgram(std::string vertexShaderFile, std::string fragmentShaderFile)
{
	mProgram = glCreateProgram();

	bool vsSuccess = false, fsSuccess = false;

	vsSuccess = loadShader(GL_VERTEX_SHADER, mVertexShader, vertexShaderFile);
	fsSuccess = loadShader(GL_FRAGMENT_SHADER, mFragmentShader, fragmentShaderFile);

	mLoadSuccess = vsSuccess && fsSuccess ? true : false;
}

bool ShaderProgram::compileShaders()
{
	bool success = true;
	mCompileSuccess = false;

	if (mVertexShader != 0)
		success = compileShader(mVertexShader);

	if (!success) 
		return false;

	if (mFragmentShader != 0)
		success = compileShader(mFragmentShader);

	mCompileSuccess = true;

	return success;
}

bool ShaderProgram::linkShaders()
{
	mLinkSuccess = false;
	
	//attach shaders
	if (mVertexShader != 0)
		glAttachShader(mProgram, mVertexShader);

	if (mFragmentShader != 0)
		glAttachShader(mProgram, mFragmentShader);
	
	//link program
	glLinkProgram(mProgram);

	//get status
	GLint linkStatus;
	glGetProgramiv(mProgram, GL_LINK_STATUS, &linkStatus);

	//return if linking failed
	if (linkStatus == GL_FALSE) {
		GLint length;
		glGetProgramiv(mProgram, GL_INFO_LOG_LENGTH, &length);

		GLchar* text = new GLchar[length + 1];
		glGetProgramInfoLog(mProgram, length, &length, text);

		std::cerr << text << std::endl;

		delete[] text;

		return false;
	}

	mLinkSuccess = true;
	return true;
}

bool ShaderProgram::compileAndLink()
{
	bool success = compileShaders();

	if (!success)
		return false;

	success = linkShaders();

	return success;
}

void ShaderProgram::use() const
{
	if (mLoadSuccess && mCompileSuccess && mLinkSuccess)
		glUseProgram(mProgram);
	else
		std::cout << "Program wasn't used due to compilation error!.." << std::endl;
}

ShaderProgram::~ShaderProgram() 
{
	//shader cleanup
	glDetachShader(mProgram, mVertexShader);
	glDetachShader(mProgram, mFragmentShader);

	glDeleteShader(mVertexShader);
	glDeleteShader(mFragmentShader);

	glDeleteProgram(mProgram);
}

//private methods

std::string ShaderProgram::getSourceFromFile(std::string fileName) 
{
	//read file line by line to create one string representing shader's source code

	std::ifstream file(fileName);

	if (!file.good()) {
		file.close();
		std::cout << "No file!" << std::endl;
		return "";
	}

	std::stringstream sourceCode;
	sourceCode << file.rdbuf();

	file.close();

	std::string s = sourceCode.str();

	return s;
}

bool ShaderProgram::loadShader(int shaderType, GLuint& shaderVariable, std::string fileName)
{
	//upload shader's source code to GPU

	std::string s = getSourceFromFile(fileName);
	const GLchar* sourceCode = s.c_str();

	if (sourceCode == "") {
		std::cerr << "File I/O failure..." << std::endl;
		delete[] sourceCode;
		return false;
	}

	shaderVariable = glCreateShader(shaderType);

	glShaderSource(shaderVariable, 1, &sourceCode, nullptr);

	return true;
}

bool ShaderProgram::compileShader(GLuint shaderVariable)
{
	//compile and check for status

	glCompileShader(shaderVariable);

	GLint compilationStatus;
	glGetShaderiv(shaderVariable, GL_COMPILE_STATUS, &compilationStatus);

	if (compilationStatus == GL_FALSE) {
		GLint length;
		glGetShaderiv(shaderVariable, GL_INFO_LOG_LENGTH, &length);

		GLchar* text = new GLchar[length + 1];
		glGetShaderInfoLog(shaderVariable, length, &length, text);

		std::cerr << text << std::endl;

		delete[] text;

		glDeleteShader(shaderVariable);

		return false;
	}

	return true;
}
