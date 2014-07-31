#ifndef __H_PROJECTILE
#define __H_PROJECTILE

#define SPEED 0.07f

class Sprite;

class Projectile
{
public:
	Projectile();
	Projectile(int shader_programme, Sprite* owner, int dir);
	~Projectile();

	void Init(int shader_programme, const char *filename);
	void Draw();
	void Update();

	float Bottom();
	float Top();
	float Left();
	float Right();

private:
	Sprite* sprite;
	int dir;
	float speed;
};

#endif	// __H_PROJECTILE