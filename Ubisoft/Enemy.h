#ifndef __ENEMY_H_
#define __ENEMY_H_

#include <vector>

#define ENEMY_SPEED 0.04f
#define ENEMY_LIFE 3
#define TIME_BETWEEN_PROJECTILES 15.0f

class Sprite;
class Player;
class Projectile;

class Enemy
{
public:
	std::vector<Projectile*> projectiles;

	Enemy();
	Enemy(int shader_programme);
	~Enemy();

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

	float Left() { return GetPosition().x; }
	float Right() { return GetPosition().x + 0.2f; }
	float Bottom() { return GetPosition().y; }
	float Top() { return GetPosition().y + 0.36f; }

private:
	Sprite* sprite;
	float speed;
	glm::vec3 direction;
	short type;
	int life;

	float timeBetweenProjectiles;
};

#endif	// __ENEMY_H_