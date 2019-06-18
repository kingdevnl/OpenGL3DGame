#include "ShaderProgram.h"

#include <fstream>
#include <iostream>
#include <string>
#include <spdlog/spdlog.h>


ShaderProgram::ShaderProgram(const char* vertexPath, const char* fragmentPath) {
	using namespace std;
	std::ifstream vertexFile(vertexPath);
	std::ifstream fragmentFile(fragmentPath);
	std::string vc = std::string(
		std::istreambuf_iterator<char>(vertexFile),
		std::istreambuf_iterator<char>()
	);
	std::string fc = std::string(
		std::istreambuf_iterator<char>(fragmentFile),
		std::istreambuf_iterator<char>()
	);

	vertexSrc = vc.c_str();
	fragmentSrc = fc.c_str();

	vertexFile.close();
	fragmentFile.close();
	
	createShader();

	vertexFile.close();
	fragmentFile.close();

}


const char* getShaderError(int shader) {
	int size;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &size);
	char* msg = new char[size];
	glGetShaderInfoLog(shader, size, &size, msg);
	return msg;

}

void compileShader(GLuint shader, GLenum type) {

	glCompileShader(shader);
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if(status == GL_FALSE) {
		spdlog::error("Failed to compile shader {}", getShaderError(shader));
		std::cin.get();
		exit(1);
	}
	spdlog::info("Compiled shader {}", shader);
}

void ShaderProgram::createShader() {

	programID = glCreateProgram();
	vertexID = glCreateShader(GL_VERTEX_SHADER);
	fragmentID = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexID, 1, &vertexSrc, NULL);
	glShaderSource(fragmentID, 1, &fragmentSrc, NULL);

	compileShader(vertexID, GL_VERTEX_SHADER);
	compileShader(fragmentID, GL_FRAGMENT_SHADER);



	glAttachShader(programID, vertexID);
	glAttachShader(programID, fragmentID);
	glLinkProgram(programID);
	glValidateProgram(programID);
	spdlog::info("Created shader {0} vertex: {1} fragment: {2}", programID, vertexID, fragmentID);
}




void ShaderProgram::bind() {
	glUseProgram(programID);
}

void ShaderProgram::unbind() {
	glUseProgram(0);
}

void ShaderProgram::destroy() {
	glUseProgram(0);
	glDetachShader(programID, vertexID);
	glDetachShader(programID, fragmentID);
	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);
	glDeleteProgram(programID);
	spdlog::info("Destroyed shader {0}", programID);
}
