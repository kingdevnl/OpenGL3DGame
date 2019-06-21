#pragma once
#include "gl/glew.h"
#include <vector>
#include "Texture.h"
#include <glm/glm.hpp>
#include "ShaderProgram.h"

class Mesh {
private:
	GLuint vao, vbo;
	std::vector<float> positions;
	std::vector<unsigned int> indices;
	std::vector<float> normals;
	std::vector<float> textCoords;
	std::vector<GLuint> vbos;
	Texture* texture;
	void createMesh();
public:


	Mesh(const std::vector<float>& positions, const std::vector<unsigned>& indices,
		const std::vector<float> normals, const std::vector<float>& text_coords, Texture* texture)
		: positions(positions),
		  indices(indices),
		  normals(normals),
		  textCoords(text_coords),
		  texture(texture) {
		createMesh();
	}

	void render(ShaderProgram shader);
	void destroy();
};
