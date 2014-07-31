#include "stdafx.h"
#include "Background.h"
#include "Sprite.h"

Background::Background()
{
	sprite = NULL;
}



Background::Background(int shader_programme)
{
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

	sprite = new Sprite(vertex_buffer, texture_buffer, index_buffer);
	sprite->Init(shader_programme, "../data/Space/Backgrounds/Background1.png");
}



Background::~Background()
{
	free(sprite);
}



void Background::Draw()
{
	sprite->Draw();
}