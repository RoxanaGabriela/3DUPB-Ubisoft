#ifndef __UTILS_H_
#define __UTILS_H_

char* LoadFileInMemory (const char* filename);
void FlipTexture(unsigned char* image_data, int x, int y, int n);
void _print_shader_info_log (GLuint shader_index);
int GetShaderProgramme(const char* vertexShader, const char* fragmentShader);

#endif	// __UTILS_H_

