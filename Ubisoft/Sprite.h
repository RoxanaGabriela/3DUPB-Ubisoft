#ifndef __H_SPRITE
#define __H_SPRITE

#include <stdlib.h>
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW32/glfw3.h> // GLFW helper library
#include "stb_image.h"

class Sprite
{
public:
	float *vertex_buffer; // buffer cu vertecsi in RAM
	int shader_programme;

	Sprite();
	Sprite(float vertex_buffer[], float texture_buffer[], unsigned int index_buffer[]);
	virtual ~Sprite();

	void Init(GLuint shader_programme, const char *filename);
	void FlipTexture(unsigned char* image_data, int x, int y, int n);
	void Draw();

	float Left();
	float Right();
	float Bottom();
	float Top();

	void show();

private:
	GLuint vbo;
	GLuint tex_vbo;
	GLuint ibo;
	GLuint tex;
	GLuint pos;

	GLint pos_loc;
	GLint tex_loc;
	GLint ModelMatrix_loc;
	GLint basic_tex;

	float *texture_buffer;
	unsigned int *index_buffer; // buffer cu indecsii din RAM
};

#endif	// __H_SPRITE