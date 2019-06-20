#include "Mesh.h"

void Mesh::createMesh() {

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * positions.size(), &positions[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
	vbos.push_back(vbo);


	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 1, GL_UNSIGNED_INT, false, 0, 0);
	vbos.push_back(vbo);

	if(texture != nullptr) {
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * textCoords.size(), &textCoords[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, false, 0, 0);
	vbos.push_back(vbo);
	}

	glBindVertexArray(0);

}

void Mesh::render(ShaderProgram shader) {
	if(texture !=nullptr) {
		shader.setUniform1f("hasTexture", GL_TRUE);
	}
	else {
		shader.setUniform1f("hasTexture", GL_FALSE);
	}

	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	if(texture != nullptr) {
	glEnableVertexAttribArray(2);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->textureID);
	}

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	
	
	if(texture !=nullptr) {
		glDisableVertexAttribArray(2);
		glBindTexture(GL_TEXTURE_2D, 0);

	}
	glBindVertexArray(0);


}

void Mesh::destroy() {
	for (GLuint vb : vbos) {

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &vbo);
	}


	glBindVertexArray(0);
	glDeleteVertexArrays(1, &vao);
}
