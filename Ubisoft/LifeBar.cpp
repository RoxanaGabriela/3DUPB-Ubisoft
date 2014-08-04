#include "stdafx.h"
#include "glm\gtx\transform.hpp"
#include "glm\gtc\type_ptr.hpp"

#include "LifeBar.h"
#include "Sprite.h"
#include "Common.h"

LifeBar::LifeBar()
{
	shader_programme = -1;
}



LifeBar::~LifeBar()
{
}



void LifeBar::Init(int shader_programme, float* vbo)
{
	GLubyte ibo[] = {
		0, 1, 2,
		0, 2, 3
	};

	glGenBuffers(1, &vbo_loc);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_loc);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof (float), vbo, GL_STATIC_DRAW);

	glGenBuffers(1, &ibo_loc);
	glBindBuffer(GL_ARRAY_BUFFER, ibo_loc);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof (unsigned char), ibo, GL_STATIC_DRAW);

	this->shader_programme = shader_programme;

	vao_loc = 0;
	glGenVertexArrays(1, &vao_loc);
	glBindVertexArray(vao_loc);

	glEnableVertexAttribArray(POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_loc);
	glVertexAttribPointer(POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	// Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_loc);

	modelMatrix_loc = glGetUniformLocation(shader_programme, "u_transfMatrix");

	// luam l5ocatia matricei de proiectie din shader
	projectionMatrix_loc = glGetUniformLocation(shader_programme, "u_proj_matrix");

	SetPosition(glm::vec3(0.0f, 0.0f, -10.0f));
};



void LifeBar::Draw()
{
	glUseProgram(shader_programme);
	glBindVertexArray(vao_loc);

	// Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_loc);

	// desenam obiectul
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (void*)0);
}



void LifeBar::Update()
{
	glm::mat4 ModelMatrix;
	ModelMatrix = glm::translate(position);
	// trimitem ModelMatrix la shader (pentru deplasarea vertecsilor)
	glUniformMatrix4fv(modelMatrix_loc, 1, GL_FALSE, glm::value_ptr(ModelMatrix));

	// generam matricea de proiectie ortografica
	glm::mat4 projectionMatrix = glm::ortho(SCREEN_LEFT, SCREEN_RIGHT, SCREEN_BOTTOM, SCREEN_TOP, 0.1f, 100.0f);

	glUniformMatrix4fv(projectionMatrix_loc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
}



void LifeBar::SetPosition(glm::vec3 position)
{
	this->position = position;
}