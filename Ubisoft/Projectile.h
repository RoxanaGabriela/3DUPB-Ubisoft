#ifndef __PROJECTILE_H_
#define __PROJECTILE_H_

#define SPEED 0.1f

class Sprite;

class Projectile
{
public:
	Projectile();
	Projectile(int shader_programme, Sprite* owner, float owner_type, float type);
	~Projectile();

	void Draw();
	void Update();

	void SetPosition(glm::vec3 pos);
	glm::vec3 GetPosition();

	float Left() { return GetPosition().x; }
	float Right() { return GetPosition().x + 0.04f; }
	float Bottom() { return GetPosition().y; }
	float Top() { return GetPosition().y + 0.1f; }

private:
	Sprite* sprite;
	float speed;
	glm::vec3 dir;
};

#endif	// __PROJECTILE_H_