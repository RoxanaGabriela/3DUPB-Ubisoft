#pragma once
#include "Sprite.h"
#include <vector>

#define MAX_TIME_BETWEEN_PROJECTILES 2500

class Projectile;
class Player;

class Enemy
{
private:
	int id;
	short type;
	int dir;
	float speed;
	int timeBetweenProjectiles;

public:
	std::vector<Projectile*> projectiles;
	Sprite *enemy;
	int life;

	Enemy();
	Enemy(int id);
	~Enemy();

	void Init(int shader_programme, const char *filename);
	void Update();
	void Draw();

	void moveLine(float tx);
	void moveCircle(float r, float angle);
	void moveSin(float angle);
	void move();

	void show();
};

