#ifndef __COMMON_H_
#define __COMMON_H_

#define DT 1.0f / 60.0f
#define PI 3.1415926f

#define SCREEN_LEFT -1.0f
#define SCREEN_RIGHT 1.0f
#define SCREEN_TOP 1.0f
#define SCREEN_BOTTOM -1.0f

#define UP 1.0f
#define DOWN -1.0f
#define RIGHT 1.0f
#define LEFT -1.0f
#define CENTER 0.0f

#define TRUE 1
#define FALSE 0

enum VERTEX_ATRIBUTES
{
	POSITION = 0,
	TEXTURE_COORDINATE_0 = 1
};

enum ENEMIES
{
	BUG_EYE = 0,
	CRESCENT = 1,
	FIGHTER = 2,
	SAUCER_BLADES = 3,
	SAUCER = 4,
	SCYTHE = 5,
	SLICER = 6,
	SPIKEY = 7,
	PLAYER = 8,
	MASTER = 9
};

#endif	// __COMMON_H_