#pragma once
#include "Sprite.h"

class Enemy
{
private:
	short type;
	int dir;

public:
	Sprite *enemy;
	int life;

	Enemy();
	Enemy(float vertex_buffer[], float texture_buffer[], unsigned int index_buffer[]);
	~Enemy();

	void Init(int shader_programme, const char *filename);
	void Draw();

	void moveLine(float tx);
	void moveCircle(float r, float angle);
	void moveSin(float angle);
	void move();

	void show();
};

