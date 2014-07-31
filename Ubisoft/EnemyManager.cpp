#include "stdafx.h"
#include "EnemyManager.h"
#include "Enemy.h"
#include "Utils.h"
#include "Player.h"

EnemyManager::EnemyManager()
{
	shader_programme = -1;
	enemiesNb = 0;
	screen = SCREEN_BOTTOM;
}



EnemyManager::EnemyManager(int shader_programme)
{
	this->shader_programme = shader_programme;
	enemiesNb = 0;
	screen = SCREEN_BOTTOM;
}



EnemyManager::~EnemyManager()
{
	enemies.clear();
}



void EnemyManager::Draw()
{
	for (int i = 0; i < enemies.size(); i++) {
		enemies[i]->Draw();
	}
}



void EnemyManager::Update(Player* player)
{
	for (int i = 0; i < enemies.size(); i++) {
		enemies[i]->Update();
		
		if (player->Collide(enemies[i]) == TRUE) {
			printf("GAME OVER!!!!\n");
		}
		if (enemies[i]->Collide(player) == TRUE) {
			free(enemies[i]);
			enemies.erase(enemies.begin() + i);
		}
	}

	if (enemies.size() == 0 || 
		enemies[enemies.size() - 1]->Bottom() <= screen ||
		(enemies[enemies.size() - 1]->Top() < SCREEN_TOP && enemies[enemies.size() - 1]->Left() < SCREEN_LEFT) ||
		(enemies[enemies.size() - 1]->Top() < SCREEN_TOP && enemies[enemies.size() - 1]->Right() > SCREEN_RIGHT)) {
		Add();
	}

	if (enemies[enemies.size() - 1]->Top() <= SCREEN_BOTTOM) {
		Remove(enemies.size() - 1);
	}

	for (int i = 0; i < enemies.size(); i++) {
		for (int j = 0; j < enemies.size(); j++) {
			if (enemies[i]->Left() < enemies[j]->Right() &&
				enemies[i]->Right() > enemies[j]->Left() &&
				enemies[i]->Bottom() < enemies[j]->Top() &&
				enemies[i]->Top() > enemies[j]->Bottom()) {

				enemies[i]->dir = -enemies[i]->dir;
				enemies[j]->dir = -enemies[j]->dir;
			}
		}
	}
}



void EnemyManager::Add()
{
	int leftSide = 85 - (rand() % 170);
	
	if (enemiesNb < 5) {
		enemies.push_back(new Enemy(shader_programme, leftSide));
		enemiesNb++;
	}
	else {
		enemies.push_back(new Enemy(shader_programme, leftSide));
		enemies.push_back(new Enemy(shader_programme, -leftSide));
		enemiesNb += 2;

		if (enemiesNb > 20) {
			screen = SCREEN_TOP - 0.35f;
		}
		else if (enemiesNb > 15) {
			screen = SCREEN_TOP - 0.5f;
		}
		else if (enemiesNb > 9) {
			screen = SCREEN_TOP - 1.0f;
		}		
	}
}



void EnemyManager::Remove(int i)
{
	if (i < enemies.size()) {
		free(enemies[i]);
		enemies.erase(enemies.begin() + i);
	}
	else {
		fprintf(stderr, "Index out of bounds!\n");
	}
}
