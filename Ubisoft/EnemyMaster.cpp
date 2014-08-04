#include "stdafx.h"

#include "EnemyMaster.h"
#include "Sprite.h"
#include "Common.h"
#include "Projectile.h"
#include "Player.h"

EnemyMaster::EnemyMaster()
{
	sprite = NULL;
	speed = MASTER_SPEED;
	life = MASTER_LIFE;
	direction = glm::vec3(0.0f, 0.0f, 0.0f);

	timeBetweenProjectiles = MASTER_TIME_BETWEEN_PROJECTILES;

	hit = false;
}



EnemyMaster::EnemyMaster(int shader_programme)
{
	float vbo[] = {
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f
	};

	sprite = new Sprite();
	sprite->Init(shader_programme, "../data/Space/Enemies/crescent0000.png", vbo);
	SetPosition(glm::vec3(0.0f, 1.5f, -10.0f));

	speed = MASTER_SPEED;
	life = MASTER_LIFE;
	direction = glm::vec3(0.0f, -1.0f, 0.0f);

	timeBetweenProjectiles = MASTER_TIME_BETWEEN_PROJECTILES;

	hit = false;
}



EnemyMaster::~EnemyMaster()
{
	free(sprite);
	sprite = NULL;

	projectiles.clear();
}



void EnemyMaster::Draw()
{
	sprite->Draw();
}



void EnemyMaster::Update()
{
	sprite->Update();
	timeBetweenProjectiles += DT;
	Fire();

	if (hit == false) {
		if (direction.x == LEFT && Left() <= SCREEN_LEFT) {
			direction = glm::vec3(RIGHT, 0.0f, 0.0f);
		}
		else if (direction.x == RIGHT && Right() >= SCREEN_RIGHT) {
			direction = glm::vec3(LEFT, 0.0f, 0.0f);
		}
		else if (Bottom() <= 0.50f) {
			glm::vec3 pos = sprite->GetPosition();
			sprite->SetPosition(glm::vec3(pos.x, pos.y + 0.01, pos.z));
			direction = glm::vec3(LEFT, 0.0f, 0.0f);
		}
	}
	Move(direction);
}



void EnemyMaster::DrawProjectiles()
{
	for (unsigned int i = 0; i < projectiles.size(); i++) {
		projectiles[i]->Update();
		projectiles[i]->Draw();

		if (projectiles[i]->GetPosition().y <= SCREEN_BOTTOM) {
			free(projectiles[i]);
			projectiles.erase(projectiles.begin() + i);
		}
	}
}



void EnemyMaster::Move(glm::vec3 dir)
{
	dir = glm::normalize(dir);

	glm::vec3 pos = GetPosition();
	pos += speed * DT * dir;

	SetPosition(pos);
}



bool EnemyMaster::Collide(Player* player)
{
	if (Top() <= SCREEN_TOP) {
		for (int i = 0; i < player->projectiles.size(); i++) {
			if (Left() < player->projectiles[i]->Right() &&
				Right() > player->projectiles[i]->Left() &&
				Bottom() < player->projectiles[i]->Top() &&
				Top() > player->projectiles[i]->Bottom()) {

				free(player->projectiles[i]);
				player->projectiles.erase(player->projectiles.begin() + i);
				life--;

				if (life == 0) {
					return true;
				}
			}
		}
	}

	return false;
}



void EnemyMaster::Fire()
{
	int type = rand() % 2;
	if (timeBetweenProjectiles >= MASTER_TIME_BETWEEN_PROJECTILES) {
		if (type == 0) {
			projectiles.push_back(new Projectile(sprite->shader_programme, sprite, MASTER, CENTER));
			timeBetweenProjectiles = 0;
		}
		else {	// type == 1
			projectiles.push_back(new Projectile(sprite->shader_programme, sprite, MASTER, LEFT));
			
			projectiles.push_back(new Projectile(sprite->shader_programme, sprite, MASTER, RIGHT));
			timeBetweenProjectiles = 0;
		}
	}
}



void EnemyMaster::SetPosition(glm::vec3 pos) {
	sprite->SetPosition(pos);
}



glm::vec3 EnemyMaster::GetPosition()
{
	return sprite->GetPosition();
}



void EnemyMaster::SetDirection(glm::vec3 dir)
{
	direction = dir;
}



glm::vec3 EnemyMaster::GetDirection()
{
	return direction;
}



int EnemyMaster::GetLife()
{
	return life;
}