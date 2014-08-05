#ifndef __ENEMY_MANAGER_H_
#define __ENEMY_MANAGER_H_

#include <vector>

#define TIME_BETWEEN_ENEMIES 50.0f 
#define HITS 20
#define EMENIES_BETWEEN_POWERS 4

class Enemy;
class EnemyMaster;
class Player;
class LifeBar;
class Power;

class EnemyManager
{
public:
	int hits;

	EnemyManager();
	EnemyManager(int shader_programme, int lifeBar_shader_programme);
	~EnemyManager();

	void Draw();
	void Update(Player* player);

	void Add();
	void Remove(unsigned int i);

private:
	int shader_programme, lifeBar_shader_programme;

	std::vector<Enemy*> enemies;
	float timeBetweenEnemies;
	float maxTime;

	EnemyMaster* master;
	int goMaster;
	LifeBar* lifeBar;



	std::vector<Power*> powers;
	int enemiesBetweenPowers;
};

#endif	// __ENEMY_MANAGER_H_