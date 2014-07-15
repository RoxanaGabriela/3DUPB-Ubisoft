#include "stdafx.h"
#include "Enemy.h"
#include <stdlib.h>

Enemy::Enemy()
{
}

Enemy::Enemy(float vertex_buffer[], float texture_buffer[], unsigned int index_buffer[])
{
	enemy = new Sprite(vertex_buffer, texture_buffer, index_buffer);
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

void Enemy::Draw()
{
	enemy->Draw();
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
			moveLine(0.0002f);
		}
		else { // dir == LEFT
			moveLine(-0.0002f);
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