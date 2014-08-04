#include "stdafx.h"
#include "Power.h"
#include "Sprite.h"
#include "Enemy.h"
#include "Common.h"

Power::Power()
{
	sprite = NULL;
	speed = POWER_SPEED;
}



Power::Power(int shader_programme, Enemy* enemy)
{
	float vbo[] = {
		0.1f, 0.18f, 0.0f,
		0.1f, -0.18f, 0.0f,
		-0.1f, -0.18f, 0.0f,
		-0.1f, 0.18f, 0.0f
	};

	sprite = new Sprite();
	sprite->Init(shader_programme, "../data/Space/FX/projectile_bolt_blue_single.png", vbo);
	sprite->SetPosition(enemy->GetPosition());

	speed = POWER_SPEED;
}



Power::~Power()
{
	free(sprite);
	sprite = NULL;
}



void Power::Draw()
{
	sprite->Draw();
}



void Power::Update()
{
	glm::vec3 dir(0.0f, -1.0f, 0.0f);
	dir = glm::normalize(dir);
	glm::vec3 pos = GetPosition();
	pos += dir * speed * DT;
	SetPosition(pos);
	sprite->Update();
}



void Power::SetPosition(glm::vec3 pos)
{
	sprite->SetPosition(pos);
}



glm::vec3 Power::GetPosition()
{
	return sprite->GetPosition();
}