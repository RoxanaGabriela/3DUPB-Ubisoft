#include "stdafx.h"
#include "Sprite.h"

Sprite::Sprite()
{
	vertex_buffer = NULL;
	texture_buffer = NULL;
	index_buffer = NULL;

	vbo = 0;
	tex_vbo = 0;
	ibo = 0;
	tex = 0;
}



Sprite::Sprite(float vertex_buffer[], float texture_buffer[], unsigned int index_buffer[])
{
	this->vertex_buffer = (float*)malloc(12 * sizeof(float));
	this->texture_buffer = (float*)malloc(8 * sizeof(float));
	this->index_buffer = (unsigned int*)malloc(6 * sizeof(unsigned int));

	for (int i = 0; i < 12; i++) this->vertex_buffer[i] = vertex_buffer[i];
	for (int i = 0; i < 8; i++) this->texture_buffer[i] = texture_buffer[i];
	for (int i = 0; i < 6; i++) this->index_buffer[i] = index_buffer[i];

	vbo = 0;
	tex_vbo = 0;
	ibo = 0;
	tex = 0;
}



Sprite::~Sprite()
{
	free(vertex_buffer);
	free(texture_buffer);
	free(index_buffer);
}



void Sprite::Init(GLuint shader_programme, const char *filename)
{
	// Generam un buffer in memoria video si scriem in el punctele din ram
	glGenBuffers(1, &vbo); // generam un buffer 
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // setam bufferul generat ca bufferul curent 
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), vertex_buffer, GL_STATIC_DRAW); //  scriem in bufferul din memoria video informatia din bufferul din memoria RAM

	// Generam un buffer in memoria video si scriem in el punctele din ram
	glGenBuffers(1, &tex_vbo); // generam un buffer 
	glBindBuffer(GL_ARRAY_BUFFER, tex_vbo); // setam bufferul generat ca bufferul curent 
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), texture_buffer, GL_STATIC_DRAW); //  scriem in bufferul din memoria video informatia din bufferul din memoria RAM

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), index_buffer, GL_STATIC_DRAW);

	this->shader_programme = shader_programme;

	// incarcam imaginea din fisier si ii fortam canalele RGBA
	int x, y, n;
	int force_channels = 4;
	unsigned char* image_data = stbi_load(filename, &x, &y, &n, force_channels);
	if (image_data == NULL) fprintf(stderr, "Error loading sprite %s image!\n", filename);

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
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	pos_loc = glGetAttribLocation(shader_programme, "vertex_position");
	glEnableVertexAttribArray(pos_loc);
	glVertexAttribPointer(pos_loc, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, tex_vbo);
	tex_loc = glGetAttribLocation(shader_programme, "texture_coordinates");
	glEnableVertexAttribArray(tex_loc);
	glVertexAttribPointer(tex_loc, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	basic_tex = glGetUniformLocation(shader_programme, "basic_texture");
	glUseProgram(shader_programme);
	glUniform1i(basic_tex, 0); // use active texture 0
}



void Sprite::Draw()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), vertex_buffer, GL_STATIC_DRAW); //  scriem in bufferul din memoria video informatia din ram
	glEnableVertexAttribArray(pos_loc);
	glVertexAttribPointer(pos_loc, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, tex_vbo);
	glEnableVertexAttribArray(tex_loc);
	glVertexAttribPointer(tex_loc, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	glUseProgram(shader_programme);
	glUniform1i(basic_tex, 0); // use active texture 0

	// Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
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



float Sprite::Left()
{
	float minX = 1;
	for (int i = 0; i < 12; i += 3) {
		if (minX > vertex_buffer[i]) minX = vertex_buffer[i];
	}
	return minX;
}



float Sprite::Right()
{
	float maxX = -1;
	for (int i = 0; i < 12; i += 3) {
		if (maxX < vertex_buffer[i]) maxX = vertex_buffer[i];
	}
	return maxX;
}



float Sprite::Bottom()
{
	float minY = 1;
	for (int i = 0; i < 12; i += 3) {
		if (minY > vertex_buffer[i + 1]) minY = vertex_buffer[i + 1];
	}
	return minY;
}



float Sprite::Top()
{
	float maxY = -1;

	for (int i = 0; i < 12; i += 3) {
		if (maxY < vertex_buffer[i + 1]) maxY = vertex_buffer[i + 1];
	}
	return maxY;
}



void Sprite::show()
{
	for (int i = 0; i < 12; i += 3) {
		printf("%.2f ", vertex_buffer[i]);
		printf("%.2f ", vertex_buffer[i + 1]);
		printf("%.2f\n", vertex_buffer[i + 2]);
	}
	printf("\n");
}