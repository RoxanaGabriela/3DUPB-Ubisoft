#include "stdafx.h"
#include "SpriteManager.h"


SpriteManager::SpriteManager()
{
	vertex_buffer_global = NULL;
	shader_programme = 0;
}

SpriteManager::SpriteManager(GLuint shader_programme)
{
	vertex_buffer_global = NULL;
	this->shader_programme = shader_programme;
}

SpriteManager::~SpriteManager()
{
}

void SpriteManager::AddSprite(float vertex_buffer[], unsigned int index_buffer[], const char *filename)
{
	Sprite *sprite = new Sprite(vertex_buffer, index_buffer, 12, 6);
	sprite->Init(shader_programme, filename);
	sprites.push_back(sprite);
}

void SpriteManager::AddSprite(Sprite *sprite, const char * filename)
{
	sprite->Init(shader_programme, filename);
	sprites.push_back(sprite);
}


void SpriteManager::DeleteSprite(int id)
{
	sprites.erase(sprites.begin() + id - 1);
}

void SpriteManager::DrawSprites()
{
	for (int i = 0; i < sprites.size(); i++) {
		sprites[i]->Draw();
	}
}
