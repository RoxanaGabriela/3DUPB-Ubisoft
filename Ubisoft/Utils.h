#ifndef __H_UTILS_
#define __H_UTILS_

#include <vector>

class Enemy;
class Player;
class Projectile;

void _print_shader_info_log(GLuint shader_index);
char* LoadFileInMemory(const char* filename);
int hit(Enemy* enemy, std::vector<Projectile*>* projectiles);
int collide(Player* player, Enemy* enemy);

#endif	// __H_UTILS_

