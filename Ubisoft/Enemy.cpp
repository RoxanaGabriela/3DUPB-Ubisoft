#include "stdafx.h"
#include <stdlib.h>

#include "Enemy.h"
#include "Player.h"
#include "Sprite.h"
#include "Projectile.h"
#include "Utils.h"

Enemy::Enemy()
{
	sprite = NULL;
	timeBetweenProjectiles = MAX_TIME_BETWEEN_PROJECTILES;
	dir = 0;
}



Enemy::Enemy(int shader_programme, int left)
{
	leftSide = ((float)left) / 100;
	
	float vertex_buffer[] = {
		leftSide + 0.25f, 1.25f, 0.0f,
		leftSide + 0.25f, 1.0f, 0.0f,
		leftSide, 1.0f, 0.0f,
		leftSide, 1.25f, 0.0f
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
	sprite->Init(shader_programme, "../data/Space/Enemies/scythe0000.png");

	life = 5;
	speed = ENEMY_SPEED;
	timeBetweenProjectiles = MAX_TIME_BETWEEN_PROJECTILES;
	if (Left() >= 0.0f) {
		dir = LEFT;
	}
	else {	// Right <= 0.0f
		dir = RIGHT;
	}
}



Enemy::~Enemy()
{
	free(sprite);
	projectiles.clear();
}



void Enemy::Draw()
{
	sprite->Draw();
	for (int i = 0; i < projectiles.size(); i++) {
		projectiles[i]->Draw();
	}
}



void Enemy::Update()
{
	timeBetweenProjectiles += DELTA_TIME;

	if (timeBetweenProjectiles >= MAX_TIME_BETWEEN_PROJECTILES) {
		projectiles.push_back(new Projectile(sprite->shader_programme, sprite, DOWN));

		timeBetweenProjectiles = 0;
	}

	for (int i = 0; i < projectiles.size(); i++) {
		projectiles[i]->Update();
		if (projectiles[i]->Top() <= -1) {
			free(projectiles[i]);
			projectiles.erase(projectiles.begin() + i);
		}
	}

	if (dir == LEFT) {
		MoveToLeft();
	}
	else {	// dir == RIGHT
		MoveToRight();
	}

	for (int i = 0; i < 12; i += 3) {
		glm::vec4 vector = glm::vec4(sprite->vertex_buffer[i], sprite->vertex_buffer[i + 1],
			sprite->vertex_buffer[i + 2], 1);
		glm::vec4 result = transMatrix * vector;

		sprite->vertex_buffer[i] = result.x;
		sprite->vertex_buffer[i + 1] = result.y;
		sprite->vertex_buffer[i + 2] = result.z;
	}
}



int Enemy::Collide(Player* player)
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
				return TRUE;
			}
		}
	}
	return FALSE;
}



void Enemy::MoveToLeft()
{
	if (Bottom() >= 0.0f) {
		transMatrix = glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, speed * DELTA_TIME * LEFT * glm::sin(PI / 2), speed * DELTA_TIME * DOWN, 0, 1);
	}
	else {
		transMatrix = glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, speed * DELTA_TIME * LEFT * glm::sin(PI / 6), speed * DELTA_TIME * DOWN, 0, 1);
	}
}



void Enemy::MoveToRight()
{
	if (Bottom() >= 0.0f) {
		transMatrix = glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, speed * DELTA_TIME * RIGHT * glm::sin(PI / 2), speed * DELTA_TIME * DOWN, 0, 1);
	}
	else {
		transMatrix = glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, speed * DELTA_TIME * RIGHT * glm::sin(PI / 6), speed * DELTA_TIME * DOWN, 0, 1);
	}
}



float Enemy::Bottom()	{ return sprite->Bottom(); }
float Enemy::Top()		{ return sprite->Top(); }
float Enemy::Left()	{ return sprite->Left(); }
float Enemy::Right()	{ return sprite->Right(); }



void Enemy::show()
{
	sprite->show();
}