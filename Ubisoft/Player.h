#ifndef __PLAYER_H_
#define __PLAYER_H_

#include <vector>

#define PLAYER_SPEED 0.1f
#define PLAYER_TIME_BETWEEN_PROJECTILES 2.0f
#define PLAYER_LIFE 20

class Sprite;
class Enemy;
class Projectile;
class EnemyMaster;

class Player
{
public:
	std::vector<Projectile*> projectiles;
	int lost;

	Player();
	Player(int shader_programme);
	~Player();

	void Draw();
	void Update();
	void DrawProjectiles();
	
	void Move(glm::vec3 dir);
	bool Collide(Enemy* enemy);
	bool Collide(EnemyMaster* enemy);
	void Fire();

	void SetPosition(glm::vec3 pos);
	glm::vec3 GetPosition();
	int GetLife();

	float Left() { return GetPosition().x - 0.05f; }
	float Right() { return GetPosition().x + 0.1f; }
	float Bottom() { return GetPosition().y; }
	float Top() { return GetPosition().y + 0.18f; }

	void show();

private:
	Sprite* sprite;
	float speed;

	float timeBetweenProjectiles;

	int life;
};

#endif	// __PLAYER_H_