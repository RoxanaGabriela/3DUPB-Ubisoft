#include "stdafx.h"
#include "Player.h"
#include "Projectile.h"
#include "Enemy.h"
#include "Sprite.h"
#include "Utils.h"

Player::Player()
{
	sprite = NULL;
	life = -1;
	speed = 0;
	timeBetweenProjectiles = TIME_BETWEEN_PROJECTILES_MAX;
}



Player::Player(int shader_programme)
{
	float vertex_buffer[] = {
		0.10f, -0.65f, 0.0f,
		0.10f, -0.95f, 0.0f,
		-0.10f, -0.95f, 0.0f,
		-0.10f, -0.65f, 0.0f,
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
	sprite->Init(shader_programme, "../data/Space/Player/player0000.png");
	
	life = 20;
	speed = PLAYER_SPEED;
	timeBetweenProjectiles = TIME_BETWEEN_PROJECTILES_MAX;
}



Player::~Player()
{
	free(sprite);
	projectiles.clear();
}



void Player::Draw()
{
	sprite->Draw();
	for (int i = 0; i < projectiles.size(); i++) {
		projectiles[i]->Draw();
	}
}



void Player::Update()
{
	timeBetweenProjectiles += DELTA_TIME;
	for (int i = 0; i < projectiles.size(); i++) {
		projectiles[i]->Update();
		if (projectiles[i]->Bottom() >= 1) {
			free(projectiles[i]);
			projectiles.erase(projectiles.begin() + i);
		}
	}
}



int Player::Collide(Enemy* enemy)
{
	for (int i = 0; i < enemy->projectiles.size(); i++) {
		if (Left() < enemy->projectiles[i]->Right() &&
			Right() > enemy->projectiles[i]->Left() &&
			Bottom() < enemy->projectiles[i]->Top() &&
			Top() > enemy->projectiles[i]->Bottom()) {

			free(enemy->projectiles[i]);
			enemy->projectiles.erase(enemy->projectiles.begin() + i);
			life--;

			if (life == 0) {
				return TRUE;
			}
		}
	}
	return FALSE;
}



void Player::MoveOY(int dir)
{
	if ((dir == UP && Top() <= SCREEN_TOP) || (dir == DOWN && Bottom() >= SCREEN_BOTTOM)) {
		glm::mat4 transMatrix = glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, speed * DELTA_TIME * dir, 0, 1);
		for (int i = 0; i < 12; i += 3) {
			glm::vec4 vector = glm::vec4(sprite->vertex_buffer[i], sprite->vertex_buffer[i + 1],
				sprite->vertex_buffer[i + 2], 1);
			glm::vec4 result = transMatrix * vector;

			sprite->vertex_buffer[i] = result.x;
			sprite->vertex_buffer[i + 1] = result.y;
			sprite->vertex_buffer[i + 2] = result.z;
		}
	}
}




void Player::MoveOX(int dir)
{
	if ((dir == RIGHT && Right() <= SCREEN_RIGHT) || (dir == LEFT && Left() >= SCREEN_LEFT)) {
		glm::mat4 transMatrix = glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, speed * DELTA_TIME * dir, 0, 0, 1);
		for (int i = 0; i < 12; i += 3) {
			glm::vec4 vector = glm::vec4(sprite->vertex_buffer[i], sprite->vertex_buffer[i + 1],
				sprite->vertex_buffer[i + 2], 1);
			glm::vec4 result = transMatrix * vector;

			sprite->vertex_buffer[i] = result.x;
			sprite->vertex_buffer[i + 1] = result.y;
			sprite->vertex_buffer[i + 2] = result.z;
		}
	}
}



void Player::Fire()
{
	if (timeBetweenProjectiles >= TIME_BETWEEN_PROJECTILES_MAX) {
		projectiles.push_back(new Projectile(sprite->shader_programme, sprite, UP));
		timeBetweenProjectiles = 0;
	}
}


float Player::Bottom()	{ return sprite->Bottom(); }
float Player::Top()		{ return sprite->Top(); }
float Player::Left()	{ return sprite->Left(); }
float Player::Right()	{ return sprite->Right(); }



void Player::show()
{
	sprite->show();
}