#ifndef VERTEX_H
#define VERTEX_H

#include "glm/glm.hpp"

/* Vertex attributes structure. */
struct Vertex
{
	/* Default constructor. */
	Vertex()
		: position(), normal(), uvcoords() {}

	/* Constructed with given attributes. */
	Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 uvcoords)
		: position(position), normal(normal), uvcoords(uvcoords) {}

	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uvcoords;
};

#endif

