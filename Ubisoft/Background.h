#ifndef __H_BACKGROUND
#define __H_BACKGROUND

class Sprite;

class Background
{
public:
	Background();
	Background(int shader_programme);
	~Background();

	void Draw();

private:
	Sprite* sprite;
};

#endif	// __H_BACKGROUND

