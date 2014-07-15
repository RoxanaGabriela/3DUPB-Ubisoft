#pragma once
#include "stb_image.h"
#include "Sprite.h"
#include <vector>

struct Loaded_Sprite
{
	char *name;
	float x, y;
	float width, height;
	int refTex;

	Loaded_Sprite() { name == NULL, x = 0, y = 0; width = 0; height = 0; refTex = 0; }
	virtual ~Loaded_Sprite() { free(name); }

};

struct Loaded_Texture
{
	int id;
	char *name;
	float width, height;
	Sprite *texture;

	Loaded_Texture() { id = -1; name = NULL; width = 0; height = 0; }
	virtual ~Loaded_Texture() { free(name); }
	void set_texture_id(int id) { this->id = id; }
	void set_texture_name(char *name) { this->name = (char*)malloc(strlen(name) * sizeof(char)); strcpy(this->name, name); }
	void set_height(int height) { this->height = height; }
	void set_width(int width) { this->width = width; }
	int get() { return id; }
};


class Loaded_Textures
{
private:
	std::vector<Loaded_Texture*> textures;
	std::vector<Loaded_Sprite*> sprites;
	
	int shader_programme;

public:
	Loaded_Textures();
	Loaded_Textures(int shader_programme);
	virtual ~Loaded_Textures();

	void add(Loaded_Texture *texture);
	void add(Loaded_Sprite *sprite);
	Loaded_Texture* find(char *image);
	int LoadTexture(char *locationTex, float *width, float *height);
	void Load();
	void Draw();
	void FlipTexture(unsigned char* image_data, int x, int y, int n);
	void show();
};

