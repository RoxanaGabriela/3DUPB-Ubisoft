#include "stdafx.h"

#include "Enemy.h"
#include "Sprite.h"
#include "Player.h"
#include "Projectile.h"
#include "Common.h"

Enemy::Enemy()
{
	sprite = NULL;
	speed = ENEMY_SPEED;
	type = -1;
	direction = glm::vec3(0.0f, 0.0f, 0.0f);
	life = ENEMY_LIFE;
	timeBetweenProjectiles = TIME_BETWEEN_PROJECTILES;
}



Enemy::Enemy(int shader_programme)
{
	float vbo[] = {
		0.1f, 0.18f, 0.0f,
		0.1f, -0.18f, 0.0f,
		-0.1f, -0.18f, 0.0f,
		-0.1f, 0.18f, 0.0f
	};

	sprite = new Sprite();
	type = rand() % 8;
	switch (type)
	{
	case BUG_EYE:
		sprite->Init(shader_programme, "../data/Space/Enemies/bug_eye0000.png", vbo);
		break;

	case CRESCENT:
		sprite->Init(shader_programme, "../data/Space/Enemies/crescent0000.png", vbo);
		break;

	case FIGHTER:
		sprite->Init(shader_programme, "../data/Space/Enemies/fighter0000.png", vbo);
		break;

	case SAUCER_BLADES:
		sprite->Init(shader_programme, "../data/Space/Enemies/saucer_blades0000.png", vbo);
		break;

	case SAUCER:
		sprite->Init(shader_programme, "../data/Space/Enemies/saucer0000.png", vbo);
		break;

	case SCYTHE:
		sprite->Init(shader_programme, "../data/Space/Enemies/scythe0000.png", vbo);
		break;

	case SLICER:
		sprite->Init(shader_programme, "../data/Space/Enemies/slicer0000.png", vbo);
		break;

	case SPIKEY:
		sprite->Init(shader_programme, "../data/Space/Enemies/spikey0000.png", vbo);
		break;

	default:
		break;
	}

	glm::vec3 pos((rand() % 200) - 100, 1.0f, -10.0f);
	pos.x /= 100;
	SetPosition(pos);
	
	timeBetweenProjectiles = TIME_BETWEEN_PROJECTILES;
	speed = ENEMY_SPEED;
	life = ENEMY_LIFE;

	direction = glm::vec3((rand() % 100), -1.0f, 0.0f);
	if (pos.x < 0.0f) {
		direction.x /= 100;
	} 
	else {	// pos.x >= 0.0f
		direction.x /= -100;
	}
}



Enemy::~Enemy()
{
	free(sprite);
	sprite = NULL;

	projectiles.clear();
}



void Enemy::Draw()
{
	sprite->Draw();
}



void Enemy::Update()
{
	sprite->Update();
	timeBetweenProjectiles += DT;
	
	Fire();
	Move(direction);
}



void Enemy::DrawProjectiles()
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



void Enemy::Move(glm::vec3 dir)
{
	dir = glm::normalize(dir);

	glm::vec3 pos = GetPosition();
	pos += dir * speed * DT;

	SetPosition(pos);
}



bool Enemy::Collide(Player* player)
{
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

	return false;
}



void Enemy::Fire()
{
	if (timeBetweenProjectiles >= TIME_BETWEEN_PROJECTILES) {
		projectiles.push_back(new Projectile(sprite->shader_programme, sprite, type, CENTER));
		timeBetweenProjectiles = 0;
	}
}



void Enemy::SetPosition(glm::vec3 pos) {
	sprite->SetPosition(pos);
}



glm::vec3 Enemy::GetPosition()
{
	return sprite->GetPosition();
}



void Enemy::SetDirection(glm::vec3 dir)
{
	direction = dir;
}



glm::vec3 Enemy::GetDirection()
{
	return direction;
}