#pragma once
#include <vector>
#include "Sprite.h"

class SpriteManager
{
private:
	GLuint shader_programme;
	std::vector<Sprite*> sprites;
	float *vertex_buffer_global;
	unsigned int *index_buffer_global;

public:
	SpriteManager();
	SpriteManager(GLuint shader_programme);
	~SpriteManager();

	void AddSprite(float vertex_buffer[], unsigned int index_buffer[], const char * filename);
	void AddSprite(Sprite *sprite, const char * filename);
	void DeleteSprite(int id);

	void InitSprites();
	void DrawSprites();
};

