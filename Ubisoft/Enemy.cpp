#include "stdafx.h"
#include "Enemy.h"
#include <stdlib.h>

Enemy::Enemy()
{
	type = -1;
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
	type = rand() % 3;
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
	float originX, originY;
	float minX = 1;
	float maxX = -1;
	float minY = 1;
	float maxY = -1;
	
	for (int i = 0; i < 12; i += 3) {
		if (minX > enemy->vertex_buffer[i]) minX = enemy->vertex_buffer[i];
		if (maxX < enemy->vertex_buffer[i]) maxX = enemy->vertex_buffer[i];

		if (minY > enemy->vertex_buffer[i + 1]) minY = enemy->vertex_buffer[i + 1];
		if (maxY < enemy->vertex_buffer[i + 1]) maxY = enemy->vertex_buffer[i + 1];
	}
	originX = minX + (maxX - minX) / 2;
	originY = minY + (maxY - minY) / 2;

	for (int i = 0; i < 12; i += 3) {
		enemy->vertex_buffer[i] = originX + sinf(angle) * r;
		enemy->vertex_buffer[i + 1] = originY + cosf(angle) * r;
	}
}

void Enemy::moveSin(float angle)
{

}

void Enemy::show()
{
	enemy->show();
}