#pragma once
#include "Sprite.h"

class Player
{
public:
	Sprite *player;
	int life;
	float speed;

	Player();
	~Player();

	void Init(int shader_programme, const char *filename);
	void Draw();

	void moveOY(float ty);
	void moveOX(float tx);
	void rotate(float angle);
	void show();
};

