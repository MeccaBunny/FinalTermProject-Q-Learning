/***************************************************************************
* CBNU 오픈소스기초프로젝트2022 기말프로젝트 박영준2021042010
* Q-Learning
***************************************************************************/
#include"VisualTool.h"
#include"LakeGame.h"
#include"Episode.h"

int main(void)
{	
	//Example when map of LakeGame is large.
	prtLoading(step1);
	Lake_createbm(49, 9, 100);
	setup();
	clearScreen();
	for (int i = 0; i < 5; i++)
		showEpisode(); // Episode before learning.

	prtLoading(step2);
	for (int i = 0; i < 100000; i++)
		virtualEpisode(); // Learning by trial of the episode.
	clearScreen();

	prtLoading(step3);
	clearScreen();
	for (int i = 0; i < 5; i++)
		showEpisode(); // Episode after trial.
	end();

	//Example to show how q is updated.
	prtLoading(step1);
	Lake_createbm(5, 5, 3);
	setup();
	clearScreen();
	for (int i = 0; i < 5; i++)
		showEpisode(); // Episode before learning.
	
	prtLoading(step2);
	for (int i = 0; i < 100000; i++)
		virtualEpisode(); // Learning by trial of the episode.
	clearScreen();
	
	prtLoading(step3);
	clearScreen();
	for (int i = 0; i < 5; i++)
		showEpisode(); // Episode after trial.
	end();
	return 0;
}