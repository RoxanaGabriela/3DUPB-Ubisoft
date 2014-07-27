#include "stdafx.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Player.h"
#include <stdlib.h>

Enemy::Enemy()
{
}

Enemy::Enemy(int id)
{
	this->id = id;
	timeBetweenProjectiles = MAX_TIME_BETWEEN_PROJECTILES - id * 500;

	float vertex_buffer[] = {
		-0.65f, 1.0f - id * 0.3, 0.0f,
		-0.65f, 0.7f - id * 0.3, 0.0f,
		-0.95f, 0.7f - id * 0.3, 0.0f,
		-0.95f, 1.0f - id * 0.3, 0.0f
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

	enemy = new Sprite(vertex_buffer, texture_buffer, index_buffer);
	
	speed = rand() % 5;
	speed /= 10000;

}

Enemy::~Enemy()
{
	free(enemy);
}

void Enemy::Init(int shader_programme, const char *filename)
{
	enemy->Init(shader_programme, filename);
	//type = rand() % 3;
	type = 0;
	life = 4;
	dir = RIGHT;
	srand(time(NULL));
}

void Enemy::Update()
{
	timeBetweenProjectiles++;

	if (timeBetweenProjectiles >= MAX_TIME_BETWEEN_PROJECTILES) {
		Projectile* projectile = new Projectile(enemy->vertex_buffer, ENEMY);
		projectile->Init(enemy->shader_programme, "../data/Space/Rockets/rocket_type_B0008.png");
		projectiles.push_back(projectile);

		timeBetweenProjectiles = 0;
	}
}

void Enemy::Draw()
{
	enemy->Draw();

	for (int i = 0; i < projectiles.size(); i++) {
		projectiles[i]->Draw();
		projectiles[i]->move(-0.0005);
	}
}

void Enemy::moveLine(float tx)
{
	glm::mat4 transMatrix = glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, tx, 0, 0, 1);
	for (int i = 0; i < 12; i += 3) {
		glm::vec4 vector = glm::vec4(enemy->vertex_buffer[i], enemy->vertex_buffer[i + 1],
									enemy->vertex_buffer[i + 2], 1);
		glm::vec4 result = transMatrix * vector;

		enemy->vertex_buffer[i] = result.x;
		enemy->vertex_buffer[i + 1] = result.y;
		enemy->vertex_buffer[i + 2] = result.z;
	}
}

void Enemy::moveCircle(float r, float angle)
{
	/*float originX = enemy->minX() + (enemy->maxX() - enemy->minX()) / 2;
	float originY = enemy->minY() + (enemy->maxY() - enemy->minY()) / 2;

	for (int i = 0; i < 12; i += 3) {
		enemy->vertex_buffer[i] = originX + sinf(angle) * r;
		enemy->vertex_buffer[i + 1] = originY + cosf(angle) * r;
	}*/
}

void Enemy::moveSin(float angle)
{

}

void Enemy::move()
{
	if (type == LINE) {
		if (enemy->minX() <= -1) dir = RIGHT;
		if (enemy->maxX() >= 1) dir = LEFT;

		if (dir == RIGHT) {
			moveLine(speed);
		}
		else { // dir == LEFT
			moveLine(-speed);
		}
	}
	else if (type == CIRCLE)
		moveCircle(0.15f, PI / 18);
	else if (type == SIN)
		moveSin(PI / 6);
}

void Enemy::show()
{
	enemy->show();
}