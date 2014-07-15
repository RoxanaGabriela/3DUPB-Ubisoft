#pragma once
#include "Sprite.h"

class Projectile
{
public:
	Sprite *projectile;

	Projectile();
	Projectile(float vertex_buffer[], float texture_buffer[], unsigned int index_buffer[]);
	~Projectile();

	void Init(int shader_programme, const char *filename);
	void Draw();
	void move(float ty);
};

