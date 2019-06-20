#pragma once
#include "gl/glew.h"
#include <vector>
#include "Texture.h"
#include <glm/glm.hpp>
#include "ShaderProgram.h"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textCoords;
};


class Mesh {
private:
	GLuint vao, vbo;
	std::vector<float> positions;
	std::vector<unsigned int> indices;
	std::vector<GLuint> vbos;
	std::vector<float> textCoords;
	Texture* texture;
	void createMesh();
public:


	Mesh(const std::vector<float>& positions, const std::vector<unsigned>& indices,
	     const std::vector<float>& text_coords, Texture* texture)
		: positions(positions),
		  indices(indices),
		  textCoords(text_coords),
		  texture(texture) {
		createMesh();
	}

	void render(ShaderProgram shader);
	void destroy();
};
