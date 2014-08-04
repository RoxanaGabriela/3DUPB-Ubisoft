#ifndef __BACKGROUND_H_
#define __BACKGROUND_H_

class Sprite;

class Background
{
public:
	Background();
	Background(int shader_programme);
	~Background();

	void Draw();
	void Update();

private:
	Sprite* sprite;
};

#endif	// __BACKGROUND_H_