#include <iostream>
#include <Windows.h>
#include <spdlog/spdlog.h>

#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <gl/GL.h>
#include "ShaderProgram.h"
#include "Mesh.h"
#include "Texture.h"
#include "GameItem.h"


#pragma comment(lib, "opengl32.lib")


using namespace spdlog;

int WIDTH = 1080;
int HEIGHT = 720;

GLuint vao, vbo;


GLFWwindow* window;

int main() {

	info("Setting up.");

	glfwInit();
	glfwDefaultWindowHints();
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	window = glfwCreateWindow(WIDTH, HEIGHT, "3DGame", 0, 0);
	glfwMakeContextCurrent(window);
	glewInit();
	glfwShowWindow(window);

	ShaderProgram shader = ShaderProgram("./res/vertex.fs", "./res/fragment.fs");

	spdlog::info("shader {0}", shader.programID);

	std::vector<float> positions = {
		// V0
		-0.5f, 0.5f, 0.5f,
		// V1
		-0.5f, -0.5f, 0.5f,
		// V2
		0.5f, -0.5f, 0.5f,
		// V3
		0.5f, 0.5f, 0.5f,
		// V4
		-0.5f, 0.5f, -0.5f,
		// V5
		0.5f, 0.5f, -0.5f,
		// V6
		-0.5f, -0.5f, -0.5f,
		// V7
		0.5f, -0.5f, -0.5f,

		// For text coords in top face
		// V8: V4 repeated
		-0.5f, 0.5f, -0.5f,
		// V9: V5 repeated
		0.5f, 0.5f, -0.5f,
		// V10: V0 repeated
		-0.5f, 0.5f, 0.5f,
		// V11: V3 repeated
		0.5f, 0.5f, 0.5f,

		// For text coords in right face
		// V12: V3 repeated
		0.5f, 0.5f, 0.5f,
		// V13: V2 repeated
		0.5f, -0.5f, 0.5f,

		// For text coords in left face
		// V14: V0 repeated
		-0.5f, 0.5f, 0.5f,
		// V15: V1 repeated
		-0.5f, -0.5f, 0.5f,

		// For text coords in bottom face
		// V16: V6 repeated
		-0.5f, -0.5f, -0.5f,
		// V17: V7 repeated
		0.5f, -0.5f, -0.5f,
		// V18: V1 repeated
		-0.5f, -0.5f, 0.5f,
		// V19: V2 repeated
		0.5f, -0.5f, 0.5f,
	};
	std::vector<unsigned int> indices = {
		// Front face
		0, 1, 3, 3, 1, 2,
		// Top Face
		8, 10, 11, 9, 8, 11,
		// Right face
		12, 13, 7, 5, 12, 7,
		// Left face
		14, 15, 6, 4, 14, 6,
		// Bottom face
		16, 18, 19, 17, 16, 19,
		// Back face
		4, 6, 7, 5, 4, 7,
	};


	std::vector<float> textCoords = {
		0.0f, 0.0f,
		0.0f, 0.5f,
		0.5f, 0.5f,
		0.5f, 0.0f,

		0.0f, 0.0f,
		0.5f, 0.0f,
		0.0f, 0.5f,
		0.5f, 0.5f,

		// For text coords in top face
		0.0f, 0.5f,
		0.5f, 0.5f,
		0.0f, 1.0f,
		0.5f, 1.0f,

		// For text coords in right face
		0.0f, 0.0f,
		0.0f, 0.5f,

		// For text coords in left face
		0.5f, 0.0f,
		0.5f, 0.5f,

		// For text coords in bottom face
		0.5f, 0.0f,
		1.0f, 0.0f,
		0.5f, 0.5f,
		1.0f, 0.5f,
	};

	Texture texture("./res/grass.png");

	Mesh mesh(positions, indices, textCoords, &texture);


	GameItem gameItem(mesh);


	shader.bind();
	glm::vec3 camPos(0.f, 0.0, 2.f);
	glm::vec3 worldUp(0.f, 1.f, 0.f);
	glm::vec3 camFront(0.f, 0.f, -1.f);

	glm::mat4 viewMatrix(1.f);

	viewMatrix = glm::lookAt(camPos, camPos + camFront, worldUp);
	float fov = 90.f;
	float nearPlane = 0.1f;
	float farPlane = 1000.f;
	glm::mat4 projectionMatrix(1.f);
	projectionMatrix = glm::perspective(glm::radians(fov), (float)WIDTH/HEIGHT, nearPlane, farPlane);
	shader.setUniformMatrix4f("viewMatrix", viewMatrix);
	shader.setUniformMatrix4f("projectionMatrix", projectionMatrix);
	shader.unbind();


	glEnable(GL_DEPTH_TEST);


	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		shader.bind();
		glm::vec3 rot = gameItem.getRotation();
		rot.x += .5f;
		rot.y += .5f;
		rot.z += .5f;
		gameItem.setRotation(rot);


		gameItem.render(shader);

		shader.unbind();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	mesh.destroy();
	texture.destroy();
	shader.destroy();


}
