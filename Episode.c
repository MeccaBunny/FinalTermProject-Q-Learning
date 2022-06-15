#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<stdio.h>

#include"random.h"
#include"MDPmodule.h"
#include"LakeGame.h"
#include"VisualTool.h"
#include"Episode.h"

int setup()
{
	MDP_init();
}

int end()
{
	MDP_end();
	Lake_endgame();
	gotoxy(0, 25);
}

int showEpisode()
{
	bool END = false;
	Direction action;
	tile endtile = nonePoint;
	Lake_setCurrent(getStartingx(), getStartingy());
	Lake_showScreen();
	Sleep(1000);
	while (!END)
	{
		MDP_update();
		action = MDP_decision();		
		Lake_Action(action);
		MDP_fit(action);
		endtile = Lake_judge(getPlayerx(), getPlayery());
		if (endtile == bombPoint || endtile == endPoint)
			END = true;
		Lake_showScreen();
		MDP_show(); // only if width, height is less than 5
		Sleep(100);
	}
	MDP_update();
	MDP_show();
	return 0;
}

int virtualEpisode()
{
	bool END = false;
	Direction action;
	tile endtile = nonePoint;
	Lake_setCurrent(getStartingx(), getStartingy());
	while (!END)
	{
		MDP_update();
		action = MDP_decision();
		Lake_Action(action);
		MDP_fit(action);
		endtile = Lake_judge(getPlayerx(), getPlayery());
		if (endtile == bombPoint || endtile == endPoint)
			END = true;
	}
	MDP_update();
	return 0;
}