#pragma once
#include "Sprite.h"

#define PLAYER 0
#define ENEMY 1

class Projectile
{
private:
	int owner;
public:
	Sprite *projectile;

	Projectile();
	Projectile(float vertex_buffer[], int owner);
	~Projectile();

	void Init(int shader_programme, const char *filename);
	void Draw();
	void move(float ty);
};

