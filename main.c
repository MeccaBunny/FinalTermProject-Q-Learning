/***************************************************************************
* CBNU ���¼ҽ�����������Ʈ2022 �⸻������Ʈ �ڿ���2021042010
* Q-Learning
***************************************************************************/
#include"VisualTool.h"
#include"LakeGame.h"
#include"Episode.h"

int main(void)
{	
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
	for (int i = 0; i < 10; i++)
		showEpisode(); // Episode after trial.
	end();
	return 0;
}