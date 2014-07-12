#pragma once
#include <stdlib.h>
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW32/glfw3.h> // GLFW helper library
#include "stb_image.h"

class Sprite
{
private:
	GLuint vbo;
	GLuint tex_vbo;
	GLuint ibo;
	GLuint tex;

public:
	float *vertex_buffer; // buffer cu vertecsi in RAM
	float *texture_buffer;
	unsigned int *index_buffer; // buffer cu indecsii din RAM

	int shader_programme;

	Sprite();
	Sprite(float vertex_buffer[], float texture_buffer[], unsigned int index_buffer[]);
	virtual ~Sprite();

	void Init(GLuint shader_programme, const char *filename);
	void FlipTexture(unsigned char* image_data, int x, int y, int n);
	void Draw();

	void show();
};

