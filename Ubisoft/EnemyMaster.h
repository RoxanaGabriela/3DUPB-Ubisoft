#ifndef __ENEMY_MASTER_H_
#define __ENEMY_MASTER_H_

#include <vector>

#define MASTER_SPEED 0.02f
#define MASTER_LIFE 30
#define MASTER_TIME_BETWEEN_PROJECTILES 15.0f

class Sprite;
class Projectile;
class Player;

class EnemyMaster
{
public:
	std::vector<Projectile*> projectiles;
	bool hit;
	
	EnemyMaster();
	EnemyMaster(int shader_programme);
	~EnemyMaster();

	void Draw();
	void Update();
	void DrawProjectiles();

	void Move(glm::vec3 dir);
	bool Collide(Player* player);
	void Fire();

	void SetPosition(glm::vec3 pos);
	glm::vec3 GetPosition();
	void SetDirection(glm::vec3 dir);
	glm::vec3 GetDirection();
	int GetLife();

	float Left() { return GetPosition().x - 0.3f; }
	float Right() { return GetPosition().x + 0.3f; }
	float Bottom() { return GetPosition().y; }
	float Top() { return GetPosition().y + 0.3; }

private:
	Sprite* sprite;
	float speed;
	int life;
	glm::vec3 direction;

	float timeBetweenProjectiles;
};

#endif	// __ENEMY_MASTER_H_