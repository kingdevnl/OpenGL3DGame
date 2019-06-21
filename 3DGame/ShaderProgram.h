#pragma once
#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <spdlog/spdlog.h>

class ShaderProgram {

public:
	const char* vertexSrc;
	const char* fragmentSrc;

	GLuint programID, vertexID, fragmentID;

	ShaderProgram(const char* vertexFile, const char* fragmentFile);
	void createShader();

	void bind();
	void unbind();

	inline GLuint getUniform(const char* name) {
		return glGetUniformLocation(programID, name);

	}

	inline void setUniform1f(const char* name, float vec) {
		glUniform1f(getUniform(name), vec);
	}

	inline void setUniform3f(const char* name, glm::vec3 vec) {
		glUniform3f(getUniform(name), vec.x, vec.y, vec.z);
	}

	inline void setUniformMatrix3f(const char* name, glm::mat3 matrix) {
		glUniformMatrix3fv(getUniform(name), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	inline void setUniformMatrix4f(const char* name, glm::mat4 matrix) {
		glUniformMatrix4fv(getUniform(name), 1, GL_FALSE, glm::value_ptr(matrix));
	}


	void destroy();
};
