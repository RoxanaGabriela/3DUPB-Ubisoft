#include "stdafx.h"
#include "Sprite.h"

Sprite::Sprite()
{
	vertex_num = 0;
	index_num = 0;

	vertex_buffer = NULL;
	index_buffer = NULL;

	vbo = 0;
	ibo = 0;
	tex = 0;
}

Sprite::Sprite(float vertex_buffer[], unsigned int index_buffer[], int vertex_num, int index_num)
{
	this->vertex_num = vertex_num;
	this->index_num = index_num;

	this->vertex_buffer = (float*)calloc(vertex_num, sizeof(float));
	this->index_buffer = (unsigned int*)calloc(index_num, sizeof(unsigned int));

	for (int i = 0; i < vertex_num; i++) this->vertex_buffer[i] = vertex_buffer[i];
	for (int i = 0; i < index_num; i++) this->index_buffer[i] = index_buffer[i];

	vbo = 0;
	ibo = 0;
	tex = 0;
}

Sprite::~Sprite()
{
	free(vertex_buffer);
	free(index_buffer);
}

void Sprite::Init(GLuint shader_programme, const char *filename)
{
	// Generam un buffer in memoria video si scriem in el punctele din ram
	glGenBuffers(1, &vbo); // generam un buffer 
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // setam bufferul generat ca bufferul curent 
	glBufferData(GL_ARRAY_BUFFER, vertex_num * sizeof(float), vertex_buffer, GL_STATIC_DRAW); //  scriem in bufferul din memoria video informatia din bufferul din memoria RAM

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_num * sizeof(unsigned int), index_buffer, GL_STATIC_DRAW);

	// incarcam imaginea din fisier si ii fortam canalele RGBA
	int x, y, n;
	int force_channels = 4;
	unsigned char* image_data = stbi_load(filename, &x, &y, &n, force_channels);
	if (image_data == NULL) fprintf(stderr, "Error loading player image!\n");

	// Facem flip pe textura 
	FlipTexture(image_data, x, y, n);

	// Trimitem textura la memoria video
	glGenTextures(1, &tex);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

	// setam parametri de sampling
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); //ce se intampla cand coordonata nu se inscrie in limite
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); //ce se intampla cand coordonata nu se inscrie in limite
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // setam samplare cu interpolare liniara
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // setam samplare cu interpolare liniara

	// De partea aceasta am uitat sa va spun la curs -> Pentru a defini bufferul alocat de opengl ca fiind buffer de in de atribute, stream de vertecsi trebuie sa :
	// 1. Ii spunem OpenGL-ului ca vom avea un slot pentru acest atribut (in cazul nostru 0) , daca mai aveam vreun atribut ar fi trebuit si acela enablat pe alt slot (de exemplu 1)
	// 2. Definit bufferul ca Vertex Attribute Pointer cu glVertexAttribPointer
	GLint pos_loc = glGetAttribLocation(shader_programme, "vertex_position");
	glEnableVertexAttribArray(pos_loc);
	glVertexAttribPointer(pos_loc, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	GLint tex_loc = glGetUniformLocation(shader_programme, "basic_texture");
	glUseProgram(shader_programme);
	glUniform1i(tex_loc, 0); // use active texture 0
}

void Sprite::Draw()
{
	// Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glDrawElements(GL_TRIANGLES, index_num, GL_UNSIGNED_INT, (void*)0);
}

// exemplu de implementare
void Sprite::FlipTexture(unsigned char* image_data, int x, int y, int n)
{
	//flip texture
	int width_in_bytes = x * 4;
	unsigned char *top = NULL;
	unsigned char *bottom = NULL;
	unsigned char temp = 0;
	int half_height = y / 2;

	for (int row = 0; row < half_height; row++) {
		top = image_data + row * width_in_bytes;
		bottom = image_data + (y - row - 1) * width_in_bytes;
		for (int col = 0; col < width_in_bytes; col++) {
			temp = *top;
			*top = *bottom;
			*bottom = temp;
			top++;
			bottom++;
		}
	}
}