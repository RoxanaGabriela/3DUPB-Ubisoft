#pragma once
#include "Sprite.h"

class Player
{
private:
	Sprite *player;

public:
	Player();
	Player(float vertex_buffer[], float texture_buffer[], unsigned int index_buffer[]);
	~Player();

	void Init(int shader_programme, const char *filename);
	void Draw();

	void moveOY(float ty);
	void moveOX(float tx);

	void show();
};

