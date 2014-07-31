#include "stdafx.h"
#include "Projectile.h"
#include "Sprite.h"
#include "Utils.h"

Projectile::Projectile()
{
	sprite = NULL;
	dir = 0;
}



Projectile::Projectile(int shader_programme, Sprite* owner, int dir)
{
	float texture_buffer[] = {
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f
	};

	unsigned int index_buffer[] = {
		0, 1, 3,
		1, 2, 3
	};

	if (dir == UP) {
		float vb[] = {
			owner->Left()	+ (owner->Right() - owner->Left()) / 4, owner->Top() + 0.2f, 0.0f,
			owner->Left()	+ (owner->Right() - owner->Left()) / 4, owner->Top(), 0.0f,
			owner->Right()	- (owner->Right() - owner->Left()) / 4, owner->Top(), 0.0f,
			owner->Right()	- (owner->Right() - owner->Left()) / 4, owner->Top() + 0.2f, 0.0f
		};
		sprite = new Sprite(vb, texture_buffer, index_buffer);
		sprite->Init(shader_programme, "../data/Space/Rockets/rocket_type_A0000.png");
	}
	else  {	// dir == DOWN
		float vb[] = {
			owner->Left()	+ (owner->Right() - owner->Left()) / 4 + (owner->Right() - owner->Left()) / 8, owner->Bottom(), 0.0f,
			owner->Left()	+ (owner->Right() - owner->Left()) / 4 + (owner->Right() - owner->Left()) / 8, owner->Bottom() - 0.1f, 0.0f,
			owner->Right()	- (owner->Right() - owner->Left()) / 4 - (owner->Right() - owner->Left()) / 8, owner->Bottom() - 0.1f, 0.0f,
			owner->Right()	- (owner->Right() - owner->Left()) / 4 - (owner->Right() - owner->Left()) / 8, owner->Bottom(), 0.0f
		};
		sprite = new Sprite(vb, texture_buffer, index_buffer);
		sprite->Init(shader_programme, "../data/Space/Rockets/rocket_type_B0008.png");
	}

	this->dir = dir;
	speed = SPEED;
}



Projectile::~Projectile()
{
	free(sprite);
}



void Projectile::Draw()
{
	sprite->Draw();
}



void Projectile::Update()
{
	glm::mat4 transMatrix = glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, speed * DELTA_TIME * dir, 0, 1);
	for (int i = 0; i < 12; i += 3) {
		glm::vec4 vector = glm::vec4(sprite->vertex_buffer[i], sprite->vertex_buffer[i + 1],
			sprite->vertex_buffer[i + 2], 1);
		glm::vec4 result = transMatrix * vector;

		sprite->vertex_buffer[i] = result.x;
		sprite->vertex_buffer[i + 1] = result.y;
		sprite->vertex_buffer[i + 2] = result.z;
	}
}



float Projectile::Bottom()	{ return sprite->Bottom(); }
float Projectile::Top()		{ return sprite->Top(); }
float Projectile::Left()	{ return sprite->Left(); }
float Projectile::Right()	{ return sprite->Right(); }