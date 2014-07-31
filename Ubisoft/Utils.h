#ifndef __H_UTILS_
#define __H_UTILS_

#include <vector>

#define LEFT -1
#define RIGHT 1
#define UP 1
#define DOWN -1

#define SCREEN_LEFT -1.0f
#define SCREEN_RIGHT 1.0f
#define SCREEN_TOP 1.0f
#define SCREEN_BOTTOM -1.0f

void _print_shader_info_log(GLuint shader_index);
char* LoadFileInMemory(const char* filename);

#endif	// __H_UTILS_

