#include "stdafx.h"
#include "stb_image.h"
#include <vector>
#include <map>

#include "Utils.h"
#include "Common.h"
#include "Background.h"
#include "Player.h"
#include "EnemyManager.h"
#include "LifeBar.h"
#include "EnemyMaster.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

// WIDTH-ul si HEIGHT-ul ecranului
#define W_WIDTH 1024
#define W_HEIGHT 640

GLuint shader_programme;
GLFWwindow* window;

Player* player;

/*bool keys[256];
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	int up = 0;
	int down = 1;
	int right = 2;
	int left = 3;
	int space = 4;
	
	glm::vec3 dir(0.0f, 0.0f, 0.0f);
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_UP) {
		if (action == GLFW_PRESS) keys[up] = true;
		if (action == GLFW_RELEASE) keys[up] = false;
	}
	if (key == GLFW_KEY_DOWN) {
		if (action == GLFW_PRESS) keys[down] = true;
		if (action == GLFW_RELEASE) keys[down] = false;
	}
	if (key == GLFW_KEY_LEFT) {
		if (action == GLFW_PRESS) keys[left] = true;
		if (action == GLFW_RELEASE) keys[left] = false;
	}
	if (key == GLFW_KEY_RIGHT) {
		if (action == GLFW_PRESS) keys[right] = true;
		if (action == GLFW_RELEASE) keys[right] = false;
	}
	if (key == GLFW_KEY_SPACE) {
		if (action == GLFW_PRESS) keys[space] = true;
		if (action == GLFW_RELEASE) keys[space] = false;
	}

	if (keys[up]) {
		dir.y = UP;
		player->Move(dir);
	}
	if (keys[down]) {
		dir.y = DOWN;
		player->Move(dir);
	}
	if (keys[left]) {
		dir.x = LEFT;
		player->Move(dir);
	}
	if (keys[right]) {
		dir.x = RIGHT;
		player->Move(dir);
	}
	if (keys[space]) {
		player->Fire();
	}
}*/



int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Initializare (se creeaza contextul)
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return 1;
	}

	// Se creeaza fereastra
	window = glfwCreateWindow(W_WIDTH, W_HEIGHT, "Ubisoft", NULL, NULL);
	if (!window) {
		// nu am reusit sa facem fereastra, oprim totul si dam mesaj de eroare
		printf("ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return 1;
	}
	// Atasam contextul de fereastra
	glfwMakeContextCurrent(window);

	// Pornit extension handler-ul
	glewInit();

	GLuint shader_programme = GetShaderProgramme("../data/vertexShader.glsl", "../data/pixelShader.glsl");
	GLuint shader_programme1 = GetShaderProgramme("../data/vertexShader1.glsl", "../data/pixelShader1.glsl");
	GLuint shader_programme2 = GetShaderProgramme("../data/vertexShader1.glsl", "../data/pixelShader2.glsl");

	Background* background = new Background(shader_programme);
	player = new Player(shader_programme);
	EnemyManager* manager = new EnemyManager(shader_programme, shader_programme1);
	LifeBar* lifeBar = new LifeBar();
	LifeBar* enemyHit = new LifeBar();

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glfwSetKeyCallback(window, key_callback);
	while (!glfwWindowShouldClose(window)) {
		//..... Randare................. 
		// stergem ce s-a desenat anterior
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::vec3 dir(0.0f, 0.0f, 0.0f);
		if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_UP)) {
			dir.y = UP;
			player->Move(dir);
		}
		if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_DOWN)) {
			dir.y = DOWN;
			player->Move(dir);
		}
		if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_LEFT)) {
			dir.x = LEFT;
			player->Move(dir);
		}
		if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_RIGHT)) {
			dir.x = RIGHT;
			player->Move(dir);
		}
		if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_SPACE)) {
			player->Fire();
		}

		background->Update();
		background->Draw();

		player->Update();
		player->Draw();
		player->DrawProjectiles();

		manager->Update(player);
		manager->Draw();
		
		if (manager->hits >= 0) {
			float vbo[] = {
				0.95f, -0.88f, 0.0f,
				0.95f, -0.90f, 0.0f,
				0.95f - manager->hits * 0.03f, -0.88f, 0.0f,
				0.95f - manager->hits * 0.03f, -0.90f, 0.0f
			};

			enemyHit->Init(shader_programme2, vbo);
			enemyHit->Update();
			enemyHit->Draw();
		}

		if (player->GetLife() >= 0) {
			float vbo[] = {
				0.95f, -0.92f, 0.0f,
				0.95f, -0.95f, 0.0f,
				0.95f - player->GetLife() * 0.03f, -0.95f, 0.0f,
				0.95f - player->GetLife() * 0.03f, -0.92f, 0.0f
			};

			lifeBar->Init(shader_programme1, vbo);
			lifeBar->Update();
			lifeBar->Draw();
		}

		// facem swap la buffere (Double buffer)
		glfwSwapBuffers(window);

		glfwPollEvents();
	}
	return 0;
}