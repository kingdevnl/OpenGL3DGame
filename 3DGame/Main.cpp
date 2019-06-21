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
#include "ObjHelper.h"
#include "Light.h"


#pragma comment(lib, "opengl32.lib")


using namespace spdlog;

int WIDTH = 1080;
int HEIGHT = 720;

GLuint vao, vbo;


GLFWwindow* window;

Light light{glm::vec3(0,0,0), glm::vec3(1,1,1)};

int main() {

	info("Setting up.");

	glfwInit();
	glfwDefaultWindowHints();
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	window = glfwCreateWindow(WIDTH, HEIGHT, "3DGame", 0, 0);
	glfwMakeContextCurrent(window);
	glewInit();
	glfwSwapInterval(1);
	glfwShowWindow(window);

	ShaderProgram shader = ShaderProgram("./res/shaders/vertex.fs", "./res/shaders/fragment.fs");

	spdlog::info("shader {0}", shader.programID);

	


	shader.bind();
	glm::vec3 camPos(0.f, 0.0, 2.f);
	glm::vec3 worldUp(0.f, 1.f, 0.f);
	glm::vec3 camFront(0.f, 0.f, -1.f);
	glm::mat4 viewMatrix(1.f);
	float fov = 90.f;
	float nearPlane = 0.1f;
	float farPlane = 1000.f;


	glm::mat4 projectionMatrix(1.f);

	projectionMatrix = glm::perspective(glm::radians(fov), (float)WIDTH / HEIGHT, nearPlane, farPlane);

	shader.setUniformMatrix4f("projectionMatrix", projectionMatrix);

	shader.setUniform3f("lightPosition", light.position);
	shader.setUniform3f("lightColour", light.colour);


	shader.unbind();


	glEnable(GL_DEPTH_TEST);




	float camMoveSpeed = .1f;
	float camRotSpeed = glm::degrees(.03f);

	float camRot = glm::degrees(130.5f);

	std::vector<GameItem> items;
	Texture texture("./res/textures/grass.png");


	// Mesh mesh = loadObj("./res/models/block.obj", &texture);
	// GameItem item(mesh);
	// items.push_back(item);

	Mesh dragonMesh = loadObj("./res/models/dragon.obj", nullptr);
	GameItem dragon(dragonMesh);
	items.push_back(dragon);



	

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		shader.bind();


		if (glfwGetKey(window, GLFW_KEY_W)) {
			camPos += camMoveSpeed * camFront;

		}
		if (glfwGetKey(window, GLFW_KEY_S)) {
			camPos -= camMoveSpeed * camFront;
		}

		if (glfwGetKey(window, GLFW_KEY_A)) {
			camPos -= camMoveSpeed * glm::normalize(glm::cross(camFront, worldUp));
		}

		if (glfwGetKey(window, GLFW_KEY_D)) {
			camPos += camMoveSpeed * glm::normalize(glm::cross(camFront, worldUp));
		}
		if (glfwGetKey(window, GLFW_KEY_Q)) {

			camRot -= camRotSpeed;
		}
		if (glfwGetKey(window, GLFW_KEY_E)) {

			camRot += camRotSpeed;
		}

		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) {

			camPos.y += camMoveSpeed;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)) {

			camPos.y -= camMoveSpeed;
		}

		camFront.x = cos(glm::radians(camRot));
		camFront.z = sin(glm::radians(camRot));
		camFront = glm::normalize(camFront);


		viewMatrix = glm::lookAt(camPos, camPos + camFront, worldUp);


		shader.setUniformMatrix4f("viewMatrix", viewMatrix);

		for (GameItem& item : items) {
			glm::vec3 rotation = item.getRotation();
			rotation.y += .5f;

			item.setRotation(rotation);
			item.render(shader);

		}


		shader.unbind();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	dragonMesh.destroy();
	texture.destroy();
	shader.destroy();


}
