#ifndef __H_ENEMY
#define __H_ENEMY

#include <vector>

#define MAX_TIME_BETWEEN_PROJECTILES 20.0f
#define ENEMY_SPEED 0.03f

#define CENTRE_TO_LEFT 0
#define RIGHT_TO_LEFT 1
#define LEFT_TO_RIGHT 2
#define CENTRE_TO_RIGHT 3

class Sprite;
class Projectile;
class Player;

class Enemy
{
public:
	std::vector<Projectile*> projectiles;
	int dir;

	Enemy();
	Enemy(int shader_programme, int left);
	~Enemy();

	void Draw();
	void Update();
	int Collide(Player* player);

	void MoveToLeft();
	void MoveToRight();

	float Bottom();
	float Top();
	float Left();
	float Right();

	void show();

private:
	Sprite* sprite;
	int life;
	glm::mat4 transMatrix;
	float speed;
	float timeBetweenProjectiles;
	float leftSide;
};

#endif	// __H_ENEMY