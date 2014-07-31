#include "stdafx.h"
#include "stb_image.h"

#include "Background.h"
#include "EnemyManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Utils.h"

#include <vector>
#include <map>
#include "GL\glew.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

// WIDTH-ul si HEIGHT-ul initial
#define W_WIDTH 1024
#define W_HEIGHT 768

Player *player;
std::vector<Enemy*> enemies;
GLuint shader_programme;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	else if (key == GLFW_KEY_UP) {
		player->MoveOY(UP);
	}
	else if (key == GLFW_KEY_DOWN) {
		player->MoveOY(DOWN);
	}
	else if (key == GLFW_KEY_LEFT) {
		player->MoveOX(LEFT);
	}
	else if (key == GLFW_KEY_RIGHT) {
		player->MoveOX(RIGHT);
	}
	else if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		player->Fire();
	}
}



int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Initializare (se creeaza contextul)
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return 1;
	}

	// Se creeaza fereastra
	GLFWwindow* window = glfwCreateWindow(W_WIDTH, W_HEIGHT, "Ubisoft", NULL, NULL);
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

	// Vedem versiunile
	const GLubyte* renderer = glGetString(GL_RENDERER); //renderer string
	const GLubyte* version = glGetString(GL_VERSION); // version string
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);

	const char * vertex_shader = LoadFileInMemory("../data/vertexShader.glsl");
	if (vertex_shader == NULL) fprintf(stderr, "Error opening vertex shader!\n");

	const char * fragment_shader = LoadFileInMemory("../data/pixelShader.glsl");
	if (fragment_shader == NULL) fprintf(stderr, "Error openning pixel shader!\n");

	int params;
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	glGetShaderiv(vs, GL_COMPILE_STATUS, &params); // iei statusul 
	if (GL_TRUE != params)
	{
		fprintf(stderr, "ERROR : GL shader index %i did not compile\ n", vs);
		_print_shader_info_log(vs); return false; // or exit or something 
	}

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &params); // iei statusul 
	if (GL_TRUE != params)
	{
		fprintf(stderr, "ERROR : GL shader index %i did not compile\ n", fs);
		_print_shader_info_log(fs); return false; // or exit or something 
	}

	shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);

	delete[] vertex_shader;
	delete[] fragment_shader;
	
	Background* background = new Background(shader_programme);

	player = new Player(shader_programme);

	//enemies.push_back(new Enemy(shader_programme));
	EnemyManager *em = new EnemyManager(shader_programme);

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glfwSetKeyCallback(window, key_callback);
	while (!glfwWindowShouldClose(window)) {
		//..... Randare................. 
		// stergem ce s-a desenat anterior
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// spunem ce shader vom folosi pentru desenare
		glUseProgram(shader_programme);
		
		background->Draw();
		
		player->Draw();
		player->Update();

		em->Draw();
		em->Update(player);

		// facem swap la buffere (Double buffer)
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	free(player);
	for (int i = 0; i < enemies.size(); i++)
		free(enemies[i]);
	enemies.clear();
	return 0;
}