#include "GameItem.h"



GameItem::GameItem(Mesh mesh): mesh(mesh) {
	
	position = glm::vec3(0.f);
	rotation = glm::vec3(0.f);

	scale = 1.f;

}

void GameItem::render(ShaderProgram shader) {
	glm::mat4 modelMatrix(1.f);
	modelMatrix = glm::translate(modelMatrix, position);
	
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f)); //rot x
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f)); //rot y 
	
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f)); //rot z
	
	modelMatrix = glm::scale(modelMatrix, glm::vec3(scale));
	shader.setUniformMatrix4f("modelMatrix", modelMatrix);

	this->mesh.render(shader);

}
