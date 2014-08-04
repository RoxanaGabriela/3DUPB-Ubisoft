#ifndef __SPRITE_H_
#define __SPRITE_H_

class Sprite
{
public:
	GLuint modelMatrix_loc;
	GLuint shader_programme;

	Sprite();
	~Sprite();

	void Init(int shader_programme, const char* filename, float* v);
	void Draw();
	void Update();

	void SetPosition(glm::vec3 position);
	glm::vec3 GetPosition();
	
private:
	GLuint vbo_loc;
	GLuint tex_coord_loc;
	GLuint ibo_loc;
	GLuint vao_loc;
	GLuint projectionMatrix_Loc;
	GLuint tex, basic_tex;

	glm::vec3 position;
	
	float aspectRatio;
};

#endif	// __SPRITE_H_

