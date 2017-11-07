#include "model.h"

#include <iostream>
#include "glm/gtc/type_ptr.hpp"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"

void Model::render(const ShaderProgram & shader) const
{
	//use passed in shader
	shader.use();

	//upload uniform Model
	glm::mat4 model = mTransform.getModelMatrix();
	GLint modelLoc = glGetUniformLocation(shader.getID(), "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	//use texture if it is valid
	if(mTexture.isValid())
		mTexture.use();

	//draw all meshes the model consists of
	for (GLuint i = 0; i < mMeshes.size(); i++)
		mMeshes[i].render();
}

void Model::loadModel(const std::string & path)
{
	//initialize importer and load the file
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_OptimizeMeshes);

	//check if model was correctly loaded
	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "Couldn't load 3D model file..." << std::endl;
		return;
	}

	//recursively process all subnodes
	processNode(scene->mRootNode, scene);

	//free resources
	importer.FreeScene();
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	//for all submeshes
	for (GLuint i = 0; i < node->mNumMeshes; ++i) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;
		
		//load vertices' attributes
		for (GLuint i = 0; i < mesh->mNumVertices; ++i)
		{
			Vertex vertex;
			
			glm::vec3 temp_vec;

			//load position
			temp_vec.x = mesh->mVertices[i].x;
			temp_vec.y = mesh->mVertices[i].y;
			temp_vec.z = mesh->mVertices[i].z;
			vertex.position = temp_vec;

			//load normals
			if (mesh->HasNormals()) {
				temp_vec.x = mesh->mNormals[i].x;
				temp_vec.y = mesh->mNormals[i].y;
				temp_vec.z = mesh->mNormals[i].z;
				vertex.normal = temp_vec;
			} else {
				vertex.normal = glm::vec3(0.0f);
			}

			//load texture coordinates
			temp_vec.x = mesh->mTextureCoords[0][i].x;
			temp_vec.y = mesh->mTextureCoords[0][i].y;
			vertex.uvcoords = glm::vec2(temp_vec);

			vertices.push_back(vertex);
		}

		//load all indices
		for (GLuint i = 0; i < mesh->mNumFaces; ++i)
		{
			aiFace face = mesh->mFaces[i];
			for (GLuint j = 0; j < face.mNumIndices; ++j)
				indices.push_back(face.mIndices[j]);
		}

		//create mesh object in-place
		mMeshes.emplace_back(vertices, indices);
	}

	//process children meshes
	for (GLuint i = 0; i < node->mNumChildren; ++i)
		processNode(node->mChildren[i], scene);
}


