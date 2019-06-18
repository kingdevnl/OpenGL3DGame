#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Mesh.h"
#include "ShaderProgram.h"

class GameItem {
private:
	glm::vec3 position;
	glm::vec3 rotation;
	float scale;
	Mesh mesh;
public:
	GameItem(Mesh mesh);
	void render(ShaderProgram shader);

	inline void setRotation(glm::vec3 rotation) {
		this->rotation = rotation;
	}
	inline void setScale(float scale) {
		this->scale = scale;
	}
	inline void setPostion(glm::vec3 pos) {
		this->position = pos;
	}
	inline glm::vec3 getRotation() {
		return rotation;
	}
	inline float getScale() {
		return scale;
	}
	inline glm::vec3 getPostion() {
		return position;
	}

};
