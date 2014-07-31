#ifndef __H_PLAYER
#define __H_PLAYER

#include <vector>

#define PLAYER_SPEED 3.0f
#define TIME_BETWEEN_PROJECTILES_MAX 6.0f

class Sprite;
class Enemy;
class Projectile;

class Player
{
public:
	std::vector<Projectile*> projectiles;
	float timeBetweenProjectiles;

	Player();
	Player(int shader_programme);
	~Player();

	void Draw();
	void Update();
	int Collide(Enemy* enemy);

	void MoveOY(int dir);
	void MoveOX(int dir);
	void Fire();

	float Bottom();
	float Top();
	float Left();
	float Right();

	void show();

private:
	Sprite* sprite;
	int life;
	float speed;
};

#endif	// __H_PLAYER