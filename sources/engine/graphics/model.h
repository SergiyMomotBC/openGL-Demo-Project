#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>
#include "mesh.h"
#include "transformation.h"
#include "texture.h"
#include "assimp/scene.h"
#include "shader_program.h"

class Model
{
public:
	/*	Constructs a 3d model from a file and a texture associated with it.	*/
	Model(const std::string& modelFile, const std::string& textureFile, float defaultScale = 1.0f) 
		: mTexture(textureFile), mTransform() 
	{ 
		loadModel(modelFile); 
		mTransform.scale(defaultScale);
	}

	/*	Constructs a 3d model from a set of vertices and indices, and a texture associated with it. */
	Model(std::vector<Vertex> vertices, std::vector<GLuint> indices, const std::string& textureFile, float defaultScale = 1.0f)
		: mTexture(textureFile), mTransform() 
	{ 
		mMeshes.emplace_back(vertices, indices); 
		mTransform.scale(defaultScale);
	}

	/* Returns a reference to model's transform object. */
	Transformation& getTransform() { return mTransform; }

	/* Renders model with a given shader program. */
	void render(const ShaderProgram& shader) const;

	/* Destructor. */
	virtual ~Model() {}

private:
	std::vector<Mesh> mMeshes;
	Texture mTexture;
	Transformation mTransform;

	void loadModel(const std::string& path);
	void processNode(aiNode* node, const aiScene* scene);
};

#endif
