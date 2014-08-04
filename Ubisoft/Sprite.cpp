#include "stdafx.h"
#include "Sprite.h"
#include "glm\gtx\transform.hpp"
#include "glm\gtc\type_ptr.hpp"

#include "Common.h"
#include "Utils.h"
#include "stb_image.h"

Sprite::Sprite()
{
	shader_programme = -1;
	vbo_loc = -1;
	vao_loc = -1;
	tex_coord_loc = -1;
	ibo_loc = -1;
	modelMatrix_loc = -1;
}



Sprite::~Sprite()
{
}



void Sprite::Init(int shader_programme, const char* filename, float* vbo)
{
	this->shader_programme = shader_programme;

	GLfloat tex_coord[] = {
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f
	};

	GLubyte ibo[] = {
		0, 1, 2,
		0, 2, 3
	};

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

	glGenBuffers(1, &vbo_loc);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_loc);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof (float), vbo, GL_STATIC_DRAW);

	glGenBuffers(1, &tex_coord_loc);
	glBindBuffer(GL_ARRAY_BUFFER, tex_coord_loc);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof (float), tex_coord, GL_STATIC_DRAW);

	glGenBuffers(1, &ibo_loc);
	glBindBuffer(GL_ARRAY_BUFFER, ibo_loc);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof (unsigned char), ibo, GL_STATIC_DRAW);

	vao_loc = 0;
	glGenVertexArrays(1, &vao_loc);
	glBindVertexArray(vao_loc);

	glEnableVertexAttribArray(POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_loc);
	glVertexAttribPointer(POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(TEXTURE_COORDINATE_0);
	glBindBuffer(GL_ARRAY_BUFFER, tex_coord_loc);
	glVertexAttribPointer(TEXTURE_COORDINATE_0, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	basic_tex = glGetUniformLocation(shader_programme, "basic_texture");
	glUseProgram(shader_programme);
	glUniform1i(basic_tex, 0); // use active texture 0

	// Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_loc);

	modelMatrix_loc = glGetUniformLocation(shader_programme, "u_transfMatrix");

	// luam l5ocatia matricei de proiectie din shader
	projectionMatrix_Loc = glGetUniformLocation(shader_programme, "u_proj_matrix");

	SetPosition(glm::vec3(0.0f, 0.0f, -10.0f));
}



void Sprite::Draw()
{
	glUseProgram(shader_programme);
	glBindVertexArray(vao_loc);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);
	
	// Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_loc);

	
	// desenam obiectul
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (void*)0);
}



void Sprite::Update()
{
	glm::mat4 ModelMatrix;
	ModelMatrix = glm::translate(position);
	// trimitem ModelMatrix la shader (pentru deplasarea vertecsilor)
	glUniformMatrix4fv(modelMatrix_loc, 1, GL_FALSE, glm::value_ptr(ModelMatrix));

	// generam matricea de proiectie ortografica
	glm::mat4 projectionMatrix = glm::ortho(SCREEN_LEFT, SCREEN_RIGHT, SCREEN_BOTTOM, SCREEN_TOP, 0.1f, 100.0f);

	glUniformMatrix4fv(projectionMatrix_Loc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
}



void Sprite::SetPosition(glm::vec3 position)
{
	this->position = position;
}



glm::vec3 Sprite::GetPosition()
{
	return position;
}