#pragma once
#include <stdlib.h>
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW32/glfw3.h> // GLFW helper library
#include "stb_image.h"

class Sprite
{
private:
	int vertex_num; // numarul de vertecsi
	int index_num; // numarul de indecsi

	float *vertex_buffer; // buffer cu vertecsi in RAM
	unsigned int *index_buffer; // buffer cu indecsii din RAM
	
	GLuint vbo;
	GLuint ibo;
	GLuint tex;

public:
	Sprite();
	Sprite(float vertex_buffer[], unsigned int index_buffer[], int vertex_num, int index_num);
	~Sprite();

	void Init(GLuint shader_programme, const char *filename);
	void FlipTexture(unsigned char* image_data, int x, int y, int n);
	void Draw();
};

