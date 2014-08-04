#ifndef __LIFE_BAR_H_
#define __LIFE_BAR_H_

class Sprite;

class LifeBar
{
public:
	LifeBar();
	~LifeBar();

	void Init(int shader_programme, float* vbo);
	void Draw();
	void Update();

	void SetPosition(glm::vec3 pos);

private:
	int shader_programme;
	GLuint vbo_loc, ibo_loc, vao_loc;
	GLuint modelMatrix_loc, projectionMatrix_loc;
	glm::vec3 position;
};

#endif	// __LIFE_BAR_H_