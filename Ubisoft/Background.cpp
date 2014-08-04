#include "stdafx.h"
#include "glm\gtx\transform.hpp"
#include "glm\gtc\type_ptr.hpp"

#include "Background.h"
#include "Sprite.h"

Background::Background()
{
	sprite = NULL;
}



Background::Background(int shader_programme)
{
	float vbo[] = {
		1.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f
	};
	sprite = new Sprite();
	sprite->Init(shader_programme, "../data/Space/Backgrounds/Background1.png", vbo);
}



Background::~Background()
{
	free(sprite);
	sprite = NULL;
}



void Background::Draw()
{
	sprite->Draw();
}



void Background::Update()
{
	sprite->Update();
}