#ifndef MESH_H
#define MESH_H

#include <vector>
#include "glad/glad.h"
#include "vertex.h"

class Mesh
{
public:
	/* Creates a mesh from the given sets of vertices and indicies. */
	Mesh(std::vector<Vertex> verticies, std::vector<GLuint> indicies)
		: mVertices(verticies), mIndices(indicies) 
	{ loadMesh(); }

	/* Draws mesh in GL_TRIANGLES mode. */
	void render() const; 

	/* Destructor. */
	virtual ~Mesh() { 
		//should be fixed!!!
		//glDeleteBuffers(1, &mEBO);
		//glDeleteBuffers(1, &mVBO);
		//glDeleteVertexArrays(1, &mVAO); 
	}

private:
	std::vector<Vertex> mVertices;
	std::vector<GLuint> mIndices;

	GLuint mVAO;
	GLuint mVBO;
	GLuint mEBO;

	void loadMesh();
};


#endif
