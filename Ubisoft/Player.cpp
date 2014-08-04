#include "stdafx.h"
#include "glm\gtx\transform.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "Common.h"

#include "Player.h"
#include "Sprite.h"
#include "Enemy.h"
#include "Projectile.h"
#include "EnemyMaster.h"

Player::Player()
{
	sprite = NULL;
	speed = PLAYER_SPEED;
	life = PLAYER_LIFE;
	timeBetweenProjectiles = PLAYER_TIME_BETWEEN_PROJECTILES;
	lost = false;
}



Player::Player(int shader_programme)
{
	float vbo[] = {
		0.1f, 0.18f, 0.0f,
		0.1f, -0.18f, 0.0f,
		-0.1f, -0.18f, 0.0f,
		-0.1f, 0.18f, 0.0f
	};

	sprite = new Sprite();
	sprite->Init(shader_programme, "../data/Space/Player/player0000.png", vbo);
	SetPosition(glm::vec3(0.0f, -0.80f, -10.0f));
	
	speed = PLAYER_SPEED;
	life = PLAYER_LIFE;
	timeBetweenProjectiles = PLAYER_TIME_BETWEEN_PROJECTILES;
	lost = false;
}



Player::~Player()
{
	free(sprite);
	sprite = NULL;

	projectiles.clear();
}


void Player::Draw()
{
	sprite->Draw();
}



void Player::Update()
{	
	sprite->Update();

	glm::vec3 pos = GetPosition();
	
	if (pos.x <= SCREEN_LEFT) pos.x = SCREEN_LEFT + 0.01f;
	if (pos.x >= SCREEN_RIGHT) pos.x = SCREEN_RIGHT -0.01f;
	if (pos.y <= SCREEN_BOTTOM) pos.y = SCREEN_BOTTOM + 0.01f;
	if (pos.y >= SCREEN_TOP) pos.y = SCREEN_TOP - 0.01f;

	SetPosition(pos);

	timeBetweenProjectiles += DT;
}



void Player::Move(glm::vec3 dir)
{
	if (lost == false) {
		dir = glm::normalize(dir);

		glm::vec3 pos = GetPosition();
		pos = pos + dir * speed * DT;

		sprite->SetPosition(pos);
	}
}



bool Player::Collide(Enemy* enemy)
{
	for (int i = 0; i < enemy->projectiles.size(); i++) {
		if (Left() < enemy->projectiles[i]->Right() && Right() > enemy->projectiles[i]->Left() &&
			Bottom() < enemy->projectiles[i]->Top() && Top() > enemy->projectiles[i]->Bottom()) {
			free(enemy->projectiles[i]);
			enemy->projectiles.erase(enemy->projectiles.begin() + i);
		
			life--;
			if (life == 0) {
				return true;
			}
		}
	}

	if (Left() <= enemy->Right() && Right() >= enemy->Left() && Bottom() <= enemy->Top() && Top() >= enemy->Bottom()) {
		life--;
		printf("%d\n", life);
		if (life == 0) {
			return true;
		}
		for (int i = 0; i < 450; i++) {
			enemy->Move(glm::vec3(-enemy->GetDirection().x, -enemy->GetDirection().y, enemy->GetDirection().z));
		}
		enemy->SetDirection(glm::vec3(-enemy->GetDirection().x, enemy->GetDirection().y, enemy->GetDirection().z));
	}

	return false;
}



bool Player::Collide(EnemyMaster* enemy)
{
	for (int i = 0; i < enemy->projectiles.size(); i++) {
		if (Left() < enemy->projectiles[i]->Right() && Right() > enemy->projectiles[i]->Left() &&
			Bottom() < enemy->projectiles[i]->Top() && Top() > enemy->projectiles[i]->Bottom()) {
			free(enemy->projectiles[i]);
			enemy->projectiles.erase(enemy->projectiles.begin() + i);

			life--;
			if (life == 0) {
				return true;
			}
		}
	}

	return false;
}



void Player::Fire()
{	
	if (lost == false) {
		if (timeBetweenProjectiles >= PLAYER_TIME_BETWEEN_PROJECTILES) {
			projectiles.push_back(new Projectile(sprite->shader_programme, sprite, PLAYER, CENTER));

			timeBetweenProjectiles = 0;
		}
	}
}



void Player::DrawProjectiles()
{
	for (unsigned int i = 0; i < projectiles.size(); i++) {
		projectiles[i]->Update();
		projectiles[i]->Draw();

		if (projectiles[i]->GetPosition().x >= SCREEN_TOP) {
			free(projectiles[i]);
			projectiles.erase(projectiles.begin() + i);
		}
	}
}



void Player::SetPosition(glm::vec3 pos)
{
	sprite->SetPosition(pos);
}



glm::vec3 Player::GetPosition()
{
	return sprite->GetPosition();
}



int Player::GetLife()
{
	return life;
}



void Player::show()
{
	printf("Left = %.2f Right = %.2f Bottom = %.2f Top = %.2f", Left(), Right(), Bottom(), Top());
}