#include "stdafx.h"
#include "SpriteManager.h"


SpriteManager::SpriteManager()
{
	shader_programme = 0;
}

SpriteManager::SpriteManager(GLuint shader_programme)
{
	this->shader_programme = shader_programme;
}

SpriteManager::~SpriteManager()
{
	for (int i = 0; i < sprites.size(); i++) {
		free(sprites[i]);
	}
	sprites.clear();
}

void SpriteManager::AddSprite(float vertex_buffer[], float texture_buffer[], unsigned int index_buffer[], const char *filename)
{
	Sprite *sprite = new Sprite(vertex_buffer, texture_buffer, index_buffer);
	sprite->Init(shader_programme, filename);
	sprites.push_back(sprite);
	free(sprite);
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
