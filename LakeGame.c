#include<stdlib.h>
#include<windows.h>
#include<stdio.h>

#include"random.h"
#include"LakeGame.h"
#include"VisualTool.h"
#include"Episode.h"

tile** bm;
int bmw, bmh;
int sx, sy;
int ex, ey;
int numofBomb;
int* bx;
int* by;
int playerx, playery;
Lake_msg_type* msg;

void Lake_createbm(int w, int h, int bn)
{
	if (bm != NULL)
		Lake_endgame();

	bmw = w;
	bmh = h;
	numofBomb = bn;

	bm = malloc(sizeof(tile*) * bmh);
	for (int i = 0; i < bmh; i++)
		bm[i] = malloc(sizeof(tile) * bmw);

	tile* bmdeck = malloc(sizeof(tile) * bmh * bmw);
	bmdeck[0] = startPoint;
	bmdeck[1] = endPoint;
	for (int i = 0; i < numofBomb; i++)
		bmdeck[2 + i] = bombPoint;
	for (int i = 2+numofBomb; i < bmh * bmw; i++)
		bmdeck[i] = nonePoint;

	for (int i = 0; i < 100000; i++)
	{
		int tmpi1 = randint(0, bmh * bmw - 1);
		int tmpi2 = randint(0, bmh * bmw - 1);
		tile m = bmdeck[tmpi1];
		bmdeck[tmpi1] = bmdeck[tmpi2];
		bmdeck[tmpi2] = m;
	}

	int k = 0;
	for (int i = 0; i < bmh; i++)
	{
		for (int j = 0; j < bmw; j++)
		{
			bm[i][j] = bmdeck[k];
			k++;
		}
	}

	bx = malloc(sizeof(int)*bn);
	by = malloc(sizeof(int)*bn);
	int bc = 0;
	for (int y = 0; y < bmh; y++)
	{
		for (int x = 0; x < bmw; x++)
		{
			if (bm[y][x] == startPoint) { sx = x; sy = y; }
			else if (bm[y][x] == endPoint) { ex = x; ey = y; }
			else if (bm[y][x] == bombPoint)
			{
				*(bx + bc) = x;
				*(by + bc) = y;
				bc++;
			}
		}
	}

	playerx = sx;
	playery = sy;

	free(bmdeck);
}
int Lake_endgame()
{
	if (bm != NULL)
	{
		for (int i = 0; i < bmh; i++)
			free(bm[i]);
		free(bm);
		return 0;
	}
	free(bx);
	free(by);

	if (msg)
	{
		free(msg);
	}
	return 1;
}
int Lake_setCurrent(int x, int y)
{
	playerx = x;
	playery = y;
}
int Lake_Action(Direction action)
{
	if (action == stay)
	{
		playerx = playerx;
		playery = playery;
	}
	else if (action == up)
	{
		if (0 < playery)
		{
			playerx = playerx;
			playery = playery - 1;
		}
	}
	else if (action == right)
	{
		if (playerx < bmw-1)
		{
			playerx = playerx + 1;
			playery = playery;
		}
	}
	else if (action == down)
	{
		if (playery < bmh-1)
		{
			playerx = playerx;
			playery = playery + 1;
		}
	}
	else if (action == left)
	{
		if (0 < playerx)
		{
			playerx = playerx - 1;
			playery = playery;
		}
	}
	else
	{
		return 1;
	}
	return 0;
}
tile Lake_judge(int playerx, int playery)
{
	tile et=nonePoint;
	if (bm[playery][playerx])
	{
		switch (bm[playery][playerx])
		{
		case endPoint:
			et = endPoint;
			break;
		case bombPoint:
			et = bombPoint;
			break;
		case nonePoint:
		case startPoint:
		default:	
			et = nonePoint;
		}
	}
	return et;
}
void Lake_showScreen()
{
	for (int i = 0; i < bmh; i++)
	{
		for (int j = 0; j < bmw; j++)
		{
			if (bm[i][j] == nonePoint) { textcolor(9);  gotoxy(j * 2 + 2, i * 2 + 2); printf("O"); }
			if (bm[i][j] == startPoint) { textcolor(10); gotoxy(j * 2 + 2, i * 2 + 2); printf("s"); }
			if (bm[i][j] == endPoint) { textcolor(11); gotoxy(j * 2 + 2, i * 2 + 2); printf("e"); }
			if (bm[i][j] == bombPoint) { textcolor(12); gotoxy(j * 2 + 2, i * 2 + 2); printf("B"); }
		}
	}
	textcolor(14);  gotoxy(playerx * 2 + 2, playery * 2 + 2); printf("P");
	textcolor(15);
}
int getPlayerx()
{
	if (playerx)
		return playerx;
	else
		return 0;
}
int getPlayery()
{
	if (playery)
		return playery;
	else
		return 0;
}
int getStartingx()
{
	if (sx)
		return sx;
	return 0;
}
int getStartingy()
{
	if (sy)
		return sy;
	return 0;
}
int getEndingx()
{
	if (ex)
		return ex;
	return 0;
}
int getEndingy()
{
	if (ey)
		return ey;
	return 0;
}
int getBitMapWidth()
{
	if (bmw)
		return bmw;
	return 0;
}
int getBitMapHeight()
{
	if (bmh)
		return bmh;
	return 0;
}
Lake_msg_type* Lake_sendMsg()
{
	msg = malloc(sizeof(Lake_msg_type));
	msg->bmh = bmh;
	msg->bmw = bmw;
	msg->numOfBomb = numofBomb;
	msg->playerx = playerx;
	msg->playery = playery;
	msg->sx = sx;
	msg->sy = sy;
	msg->ex = ex;
	msg->ey = ey;

	msg->bm = malloc(sizeof(tile*) * bmh);
	for (int i = 0; i < bmh; i++)
	{
		msg->bm[i] = malloc(sizeof(tile) * bmw);
		for (int j = 0; j < bmw; j++)
			msg->bm[i][j] = bm[i][j];
	}

	msg->bx = malloc(sizeof(int)*numofBomb);
	msg->by = malloc(sizeof(int)*numofBomb);

	for (int i = 0; i < numofBomb; i++)
	{
		msg->bx[i] = bx[i];
		msg->by[i] = by[i];
	}
	return msg;
}
