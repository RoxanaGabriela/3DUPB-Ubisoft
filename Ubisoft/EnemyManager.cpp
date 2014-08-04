#include "stdafx.h"
#include "EnemyManager.h"
#include "Enemy.h"
#include "EnemyMaster.h"
#include "Player.h"
#include "Common.h"
#include "LifeBar.h"

EnemyManager::EnemyManager()
{
	shader_programme = -1;
	lifeBar_shader_programme = -1;
	timeBetweenEnemies = TIME_BETWEEN_ENEMIES;
	maxTime = TIME_BETWEEN_ENEMIES;
	master = NULL;
	lifeBar = NULL;
	goMaster = false;
	hits = HITS;
	enemiesBetweenPowers = 0;
}



EnemyManager::EnemyManager(int shader_programme, int lifeBar_shader_programme)
{
	this->shader_programme = shader_programme;
	this->lifeBar_shader_programme = lifeBar_shader_programme;
	timeBetweenEnemies = TIME_BETWEEN_ENEMIES;
	maxTime = TIME_BETWEEN_ENEMIES;
	master = NULL;
	goMaster = false;
	hits = HITS;
	lifeBar = new LifeBar();
	enemiesBetweenPowers = 0;
}



EnemyManager::~EnemyManager()
{
	enemies.clear();

	free(master);
	master = NULL;

	free(lifeBar);
	lifeBar = NULL;

	powers.clear();
}



void EnemyManager::Draw()
{
	if (goMaster == false) {
		for (unsigned int i = 0; i < enemies.size(); i++) {
			enemies[i]->Update();
			enemies[i]->Draw();
			enemies[i]->DrawProjectiles();

			if (enemies[i]->GetPosition().y <= SCREEN_BOTTOM) {
				Remove(i);
			}
		}
		timeBetweenEnemies += DT;
		if (maxTime >= 15.0f) maxTime -= DT;

		Add();
	}
	else if (goMaster == true) {
		master->Update();
		master->Draw();
		master->DrawProjectiles();

		if (master->GetLife() >= 0) {
			float vbo[] = {
				-0.95f,								0.95f, 0.0f,
				-0.95f,								0.92f, 0.0f,
				-0.95f + master->GetLife() * 0.02f,	0.92f, 0.0f,
				-0.95f + master->GetLife() * 0.02f,	0.95f, 0.0f
			};

			lifeBar->Init(lifeBar_shader_programme, vbo);
			lifeBar->Update();
			lifeBar->Draw();
		}
	}
}



void EnemyManager::Update(Player* player)
{
	if (goMaster == false) {
		for (unsigned int i = 0; i < enemies.size(); i++) {
			if (player->Collide(enemies[i]) == true) {
				player->lost = true;
				printf("Game over!!!! You lost!!\n");
			}

			if (enemies[i]->Collide(player) == true) {
				free(enemies[i]);
				enemies.erase(enemies.begin() + i);
				hits--;
				if (hits == 0){
					master = new EnemyMaster(shader_programme);
					goMaster = true;
					enemies.clear();
					break;
				}
			}
		}
	}
	else if (goMaster == true) {
		if (player->Collide(master) == true) {
			player->lost = true;
			printf("Game over!!!! You lost!!\n");
		}

		if (master->Collide(player) == true) {
			glm::vec3 dir = master->GetDirection();
			dir.y = UP;
			master->SetDirection(dir);
			master->hit = true;

			if (master->GetPosition().y >= SCREEN_TOP) {
				free(master);
				goMaster = -1;
			}
		}
	}
	else {	// goMaster = -1;
		printf("Game over!!!! You won!!\n");
	}
}
void EnemyManager::Add()
{
	if (timeBetweenEnemies >= maxTime) {
		enemies.push_back(new Enemy(shader_programme));
		timeBetweenEnemies = 0;
	}
}



void EnemyManager::Remove(unsigned int i)
{
	if (i < enemies.size()) {
		free(enemies[i]);
		enemies.erase(enemies.begin() + i);
	}
}