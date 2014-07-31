#ifndef __H_ENEMY_MANAGER
#define __H_ENEMY_MANAGER

#include <vector>

class Enemy;
class Player;

class EnemyManager
{
public:
	EnemyManager();
	EnemyManager(int shader_programme);

	~EnemyManager();

	void Draw();
	void Update(Player* player);

	void Add();
	void Remove(int i);

private:
	std::vector<Enemy*> enemies;
	int enemiesNb;
	int shader_programme;
	float screen;
};

#endif	// __H_ENEMY_MANAGER

