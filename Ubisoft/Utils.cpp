#include "stdafx.h"
#include "Utils.h"

// functie banala de incarcat continutul unui fisier intr-un buffer
char* LoadFileInMemory (const char* filename)
{
	int size = 0;
	char* buffer = NULL;
	
	FILE* f = fopen (filename, "rb");
	if (f == NULL)
	{
		return NULL;
	}

	fseek (f, 0, SEEK_END);
	size = ftell (f);
	fseek (f, 0, SEEK_SET);
	buffer = new char[size + 1];
	if (size != fread (buffer, sizeof (char), size, f))
	{
		delete[] buffer;
	}

	fclose (f);
	buffer[size] = 0;
	return buffer;
}



// exemplu de implementare
void FlipTexture(unsigned char* image_data, int x, int y, int n)
{
	//flip texture
	int width_in_bytes = x * 4;
	unsigned char *top = NULL;
	unsigned char *bottom = NULL;
	unsigned char temp = 0;
	int half_height = y / 2;

	for (int row = 0; row < half_height; row++) {
		top = image_data + row * width_in_bytes;
		bottom = image_data + (y - row - 1) * width_in_bytes;
		for (int col = 0; col < width_in_bytes; col++) {
			temp = *top;
			*top = *bottom;
			*bottom = temp;
			top++;
			bottom++;
		}
	}
}


void _print_shader_info_log (GLuint shader_index)
{
	int max_length = 2048;
	int actual_length = 0;
	char log[2048];
	glGetShaderInfoLog (shader_index, max_length, &actual_length, log);
	printf (" shader info log for GL index %u:\ n% s\ n", shader_index, log);
}



int GetShaderProgramme(const char* vertexShader, const char* fragmentShader)
{
	const char * vertex_shader = LoadFileInMemory(vertexShader);
	if (vertex_shader == NULL) fprintf(stderr, "Error opening vertex shader!\n");

	const char * fragment_shader = LoadFileInMemory(fragmentShader);
	if (fragment_shader == NULL) fprintf(stderr, "Error openning pixel shader!\n");

	int params;
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	glGetShaderiv(vs, GL_COMPILE_STATUS, &params); // iei statusul 
	if (GL_TRUE != params)
	{
		fprintf(stderr, "ERROR : GL shader index %i did not compile\ n", vs);
		_print_shader_info_log(vs); return false; // or exit or something 
	}

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &params); // iei statusul 
	if (GL_TRUE != params)
	{
		fprintf(stderr, "ERROR : GL shader index %i did not compile\ n", fs);
		_print_shader_info_log(fs); return false; // or exit or something 
	}

	int shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);

	delete[] vertex_shader;
	delete[] fragment_shader;

	return shader_programme;
}