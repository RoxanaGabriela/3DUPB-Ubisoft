#include "stdafx.h"
#include "stb_image.h"
#include "SpriteManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Utils.h"
#include "Loaded_Textures.h"
#include <vector>
#include <map>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

#define TIME_BETWEEN_PROJECTILES_MAX 500

Player *player;
std::vector<Enemy*> enemies;
std::vector<Projectile*> projectiles;
GLuint shader_programme;
int timeBetweenProjectiles;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	else if (key == GLFW_KEY_UP) {
		player->moveOY(TOP);
	}
	else if (key == GLFW_KEY_DOWN) {
		player->moveOY(BOTTOM);
	}
	else if (key == GLFW_KEY_LEFT) {
		player->moveOX(LEFT);
	}
	else if (key == GLFW_KEY_RIGHT) {
		player->moveOX(RIGHT);
	}
	else if (key == GLFW_KEY_X) {
		player->rotate(PI / 12);
	}
	else if (key == GLFW_KEY_C) {
		player->rotate(-PI / 12);
	}
	else if (key == GLFW_KEY_SPACE && action == GLFW_PRESS && timeBetweenProjectiles >= TIME_BETWEEN_PROJECTILES_MAX) {
		projectiles.push_back(new Projectile(player->player->vertex_buffer, PLAYER));
		projectiles[projectiles.size() - 1]->Init(shader_programme, "../data/Space/Rockets/rocket_type_A0000.png");

		timeBetweenProjectiles = 0;
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
	GLFWwindow* window = glfwCreateWindow(640, 480, "Ubisoft", NULL, NULL);
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
		_print_shader_info_log(vs); //return false; // or exit or something 
	}

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &params); // iei statusul 
	if (GL_TRUE != params)
	{
		fprintf(stderr, "ERROR : GL shader index %i did not compile\ n", fs);
		_print_shader_info_log(fs); //return false; // or exit or something 
	}

	shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);

	delete[] vertex_shader;
	delete[] fragment_shader;

	/* CERC */
	/*float *vx, *vy;
	float r = 0.25f;
	float cx = 0.0f;
	float cy = 0.0f;
	vx = (float*)malloc(vertex_num_circle * sizeof(float));
	vy = (float*)malloc(vertex_num_circle * sizeof(float));
	for (int ii = 0; ii < vertex_num_circle; ii++) {
		float theta = 2.0f * PI * float(ii) / float(vertex_num_circle);//get the current angle 

		float x = r * cosf(theta);//calculate the x component 
		float y = r * sinf(theta);//calculate the y component 
		vx[ii] = x + cx;
		vy[ii] = y + cy;
	}

	for (int ii = 0; ii < vertex_num_circle; ii++) {
		vertex_buffer[i] = vx[ii];
		vertex_buffer[i + 1] = vy[ii];
		if (ii + 1 == vertex_num_circle) {
			vertex_buffer[i + 3] = vx[0];
			vertex_buffer[i + 4] = vy[0];
		}
		else {
			vertex_buffer[i + 3] = vx[ii + 1];
			vertex_buffer[i + 4] = vy[ii + 1];
		}
		i += 9;
	}
	free(vx);
	free(vy);*/
	/*Loaded_Textures *loadedTextures = new Loaded_Textures(shader_programme);
	loadedTextures->Load();*/

	float vertex_buffer[] = {
		1.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f
	};

	float texture_buffer[] = {
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f
	};

	unsigned int index_buffer[] = {
		0, 1, 3,
		1, 2, 3
	};

	Sprite* background = new Sprite(vertex_buffer, texture_buffer, index_buffer);
	background->Init(shader_programme, "../data/Space/Backgrounds/Background1.png");
	
	player = new Player();
	player->Init(shader_programme, "../data/Space/Player/player0000.png");

	for (int i = 0; i < 4; i++)
		enemies.push_back(new Enemy(i));
	
	for (int i = 0; i < enemies.size(); i++)
		enemies[i]->Init(shader_programme, "../data/Space/Enemies/scythe0000.png");

	timeBetweenProjectiles = TIME_BETWEEN_PROJECTILES_MAX;
	// Enable blending
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glfwSetKeyCallback(window, key_callback);
	while (!glfwWindowShouldClose(window)) {
		//..... Randare................. 
		// stergem ce s-a desenat anterior
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// spunem ce shader vom folosi pentru desenare
		glUseProgram(shader_programme);
		
		timeBetweenProjectiles++;
		background->Draw();
		player->Draw();

		for (int i = 0; i < projectiles.size(); i++) {
			projectiles[i]->Draw();
			projectiles[i]->move(0.0005);
			if (projectiles[i]->projectile->minY() >= 1) {
				free(projectiles[i]);
				projectiles.erase(projectiles.begin() + i);
			}
		}
		for (int i = 0; i < enemies.size(); i++) {
			enemies[i]->Update();
			enemies[i]->Draw();
			enemies[i]->move();

			if (collide(player, enemies[i]) == TRUE) {
				printf("GAME OVER!!!!\n");
			}
			if (hit(enemies[i], &projectiles) == TRUE) {
				free(enemies[i]);
				enemies.erase(enemies.begin() + i);
			}
		}

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