#include "stdafx.h"
#include "Utils.h"
#include "Enemy.h"
#include "Player.h"
#include "Projectile.h"

void _print_shader_info_log(GLuint shader_index)
{
	int max_length = 2048;
	int actual_length = 0;
	char log[2048];
	glGetShaderInfoLog(shader_index, max_length, &actual_length, log);
	printf(" shader info log for GL index %u:\ n% s\ n", shader_index, log);
}


// functie banala de incarcat continutul unui fisier intr-un buffer
char * LoadFileInMemory(const char *filename)
{
	int size = 0;
	char *buffer = NULL;
	FILE *f = fopen(filename, "rb");
	if (f == NULL)
	{
		return NULL;
	}
	fseek(f, 0, SEEK_END);
	size = ftell(f);
	fseek(f, 0, SEEK_SET);
	buffer = new char[size + 1];
	if (size != fread(buffer, sizeof(char), size, f))
	{
		delete[] buffer;
	}
	fclose(f);
	buffer[size] = 0;
	return buffer;
}


int hit(Enemy* enemy, std::vector<Projectile*>* projectiles)
{
	for (int i = 0; i < projectiles->size(); i++) {
		if (enemy->enemy->minX() < projectiles->at(i)->projectile->maxX() &&
			enemy->enemy->maxX() > projectiles->at(i)->projectile->minX() &&
			enemy->enemy->minY() < projectiles->at(i)->projectile->maxY() &&
			enemy->enemy->maxY() > projectiles->at(i)->projectile->minY()) {

			free(projectiles->at(i));
			projectiles->erase(projectiles->begin() + i);
			enemy->life--;
			printf("Hit!!!\n");

			if (enemy->life == 0) {
				return TRUE;
			}
		}
	}
	return FALSE;
}

int collide(Player* player, Enemy* enemy)
{
	for (int i = 0; i < enemy->projectiles.size(); i++) {
		if (player->player->minX() < enemy->projectiles[i]->projectile->maxX() &&
			player->player->maxX() > enemy->projectiles[i]->projectile->minX() &&
			player->player->minY() < enemy->projectiles[i]->projectile->maxY() &&
			player->player->maxY() > enemy->projectiles[i]->projectile->minY()) {

			free(enemy->projectiles[i]);
			enemy->projectiles.erase(enemy->projectiles.begin() + i);
			player->life--;
			printf("Awwww!!!\n");

			if (player->life == 0) {
				return TRUE;
			}
		}
	}
	return FALSE;
}