#include "stdafx.h"
#include "stb_image.h"
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW32/glfw3.h> // GLFW helper library
#include "SpriteManager.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#define PI 3.1415926f

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

// functie banala de incarcat continutul unui fisier intr-un buffer
char * LoadFileInMemory(const char *filename)
{
	int size = 0;
	char *buffer = NULL;
	FILE *f = fopen(filename, "rb");
	if (f == NULL)
	{
		return NULL;
	}
	fseek(f, 0, SEEK_END);
	size = ftell(f);
	fseek(f, 0, SEEK_SET);
	buffer = new char[size + 1];
	if (size != fread(buffer, sizeof(char), size, f))
	{
		delete[] buffer;
	}
	fclose(f);
	buffer[size] = 0;
	return buffer;
}

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Initializare (se creeaza contextul)
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return 1;
	}

	// Se creeaza fereastra
	GLFWwindow* window = glfwCreateWindow(640, 480, "Workshop1", NULL, NULL);
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

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);
	GLuint shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);

	delete[] vertex_shader;
	delete[] fragment_shader;

	int vertex_num = 12;
	int index_num = 6;
	
	/* PATRAT */
	float vertex_buffer1[] = {
		-0.75f, -0.25f, 0.0f,
		-0.75f, -0.75f, 0.0f,
		-0.25f, -0.75f, 0.0f,
		-0.25f, -0.25f, 0.0f
	};

	float vertex_buffer2[] = {
		-0.75f, 0.75f, 0.0f,
		-0.75f, 0.25f, 0.0f,
		-0.25f, 0.25f, 0.0f,
		-0.25f, 0.75f, 0.0f
	};

	unsigned int index_buffer[] = {
		0, 1, 3,
		1, 2, 3
	};
	
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
	
	SpriteManager *spriteM = new SpriteManager(shader_programme);
	spriteM->AddSprite(vertex_buffer1, index_buffer, "../data/player0000.png");
	
	Sprite *sprite = new Sprite(vertex_buffer2, index_buffer, vertex_num, index_num);
	spriteM->AddSprite(sprite, "../data/player0000/png");

	while (!glfwWindowShouldClose(window)) {
		//..... Randare................. 
		// stergem ce s-a desenat anterior
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// spunem ce shader vom folosi pentru desenare
		glUseProgram(shader_programme);

		//sprite->Draw();
		spriteM->DrawSprites();

		// facem swap la buffere (Double buffer)
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();
	
	return 0;
}