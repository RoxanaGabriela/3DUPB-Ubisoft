#include "stdafx.h"

#include "Common.h"
#include "Projectile.h"
#include "Sprite.h"


Projectile::Projectile()
{
	sprite = NULL;
	speed = SPEED;
	dir = glm::vec3(0.0f, 0.0f, 0.0f);
}



Projectile::Projectile(int shader_programme, Sprite* owner, float owner_type, float type)
{
	glm::vec3 pos = owner->GetPosition();
	dir = glm::vec3(0.0f, 0.0f, 0.0f);
	sprite = new Sprite();	
	if (owner_type == PLAYER) {
		float vbo[] = {
			0.02f, 0.1f, 0.0f,
			0.02f, -0.1f, 0.0f,
			-0.02f, -0.1f, 0.0f,
			-0.02f, 0.1f, 0.0f
		};

		sprite->Init(shader_programme, "../data/Space/FX/gun_blast.png", vbo);
		pos.y += 0.15f;
		dir.y = UP;
	}
	else if (owner_type == MASTER) {
		if (type == CENTER) {
			float vbo[] = {
				0.02f, 0.05f, 0.0f,
				0.02f, -0.05f, 0.0f,
				-0.02f, -0.05f, 0.0f,
				-0.02f, 0.05f, 0.0f
			};

			sprite->Init(shader_programme, "../data/Space/Rockets/rocket_type_B0008.png", vbo);
			pos.y -= 0.25f;
			dir.y = DOWN;
		}
		else if (type == LEFT) {
			float vbo[] = {
				0.02f, 0.05f, 0.0f,
				0.02f, -0.05f, 0.0f,
				-0.02f, -0.05f, 0.0f,
				-0.02f, 0.05f, 0.0f
			};

			sprite->Init(shader_programme, "../data/Space/Rockets/rocket_type_B0008.png", vbo);
			pos.x -= 0.20f;
			pos.y -= 0.20f;
			dir.y = DOWN;
		}
		else {	// type == RIGHT
			float vbo[] = {
				0.02f, 0.05f, 0.0f,
				0.02f, -0.05f, 0.0f,
				-0.02f, -0.05f, 0.0f,
				-0.02f, 0.05f, 0.0f
			};

			sprite->Init(shader_programme, "../data/Space/Rockets/rocket_type_B0008.png", vbo);
			pos.x += 0.20f;
			pos.y -= 0.20f;
			dir.y = DOWN;
		}
	}
	else if (owner_type == CRESCENT || owner_type == FIGHTER || owner_type == SCYTHE || owner_type == SLICER) {
		float vbo[] = {
			0.02f, 0.05f, 0.0f,
			0.02f, -0.05f, 0.0f,
			-0.02f, -0.05f, 0.0f,
			-0.02f, 0.05f, 0.0f
		};

		sprite->Init(shader_programme, "../data/Space/Rockets/rocket_type_B0008.png", vbo);
		pos.y -= 0.10f;
		dir.y = DOWN;
	}

	SetPosition(pos);
	speed = SPEED;
}



Projectile::~Projectile()
{
	free(sprite);
	sprite = NULL;
}



void Projectile::Draw()
{
	sprite->Draw();
}



void Projectile::Update()
{
	dir = glm::normalize(dir);
	glm::vec3 pos = GetPosition();
	pos += dir * speed * DT;
	SetPosition(pos);

	sprite->Update();
}



void Projectile::SetPosition(glm::vec3 pos)
{
	sprite->SetPosition(pos);
}



glm::vec3 Projectile::GetPosition()
{
	return sprite->GetPosition();
}