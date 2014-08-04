#ifndef __POWER_H_
#define __POWER_H_

#define POWER_SPEED 0.05f

class Sprite;
class Enemy;

class Power
{
public:
	Power();
	Power(int shader_programme, Enemy* enemy);
	~Power();

	void Draw();
	void Update();

	void SetPosition(glm::vec3 pos);
	glm::vec3 GetPosition();

private:
	Sprite* sprite;
	float speed;
};

#endif	// __POWER_H_