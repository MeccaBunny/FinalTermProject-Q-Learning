#ifndef LAKEGAME
#define LAKEGAME

#ifndef DIRECTION
#define DIRECTION

typedef enum _Direction { stay, up, right, down, left } Direction;

#endif

#ifndef TILE
#define TILE

typedef enum { nonePoint, startPoint, endPoint, bombPoint } tile;

#endif

typedef struct _Lake_msg_type
{
	tile** bm;
	int bmw, bmh;
	int sx, sy;
	int ex, ey;
	int numOfBomb;
	int* bx;
	int* by;
	int playerx, playery;
} Lake_msg_type;

void Lake_createbm(int w, int h, int bn);
int Lake_endgame();
int Lake_setCurrent(int x, int y);
int Lake_Action(Direction action);
tile Lake_judge(int playerx, int playery);
void Lake_showScreen();
int getPlayerx();
int getPlayery();
int getStartingx();
int getStartingy();
int getEndingx();
int getEndingy();
int getBitMapWidth();
int getBitMapHeight();
Lake_msg_type* Lake_sendMsg();

#endif