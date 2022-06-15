#include<stdio.h>
#include<windows.h>

#include"visualTool.h"

void textcolor(int colorNum) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}

void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int clearScreen()
{
	SetConsoleOutputCP(437);
	gotoxy(0, 0); printf("%c", 218); for (int i = 1; i < 99; i++) { gotoxy(i, 0); printf("%c", 196); } gotoxy(100, 0); printf("%c", 191);
	for (int i = 1; i < 20; i++) { gotoxy(0, i); printf("%c", 179); for (int j = 1; j < 99; j++) { gotoxy(j, i); printf(" "); } gotoxy(100, i); printf("%c", 179); }
	gotoxy(0, 20); printf("%c", 192); for (int i = 1; i < 99; i++) { gotoxy(i, 20); printf("%c", 196); } gotoxy(100, 20); printf("%c", 217);
	SetConsoleOutputCP(949);
}

int prtLoading(showSequence step)
{
	SetConsoleOutputCP(437);
	if (step == step1)
	{
		gotoxy(0, 0); printf("%c", 218);
		for (int i = 1; i < 99; i++) { gotoxy(i, 0); printf("%c", 196); }
		gotoxy(100,0); printf("%c", 191);
		for (int i = 1; i < 20; i++) { gotoxy(0, i); printf("%c", 179); }
		gotoxy(0, 20); printf("%c", 192);
		for (int i = 1; i < 20; i++) { gotoxy(100, i); printf("%c", 179); }
		gotoxy(100, 20); printf("%c", 217);
		for (int i = 1; i < 99; i++) { gotoxy(i, 20); printf("%c", 196); }
		gotoxy(30, 10); printf("Before learning.");
		Sleep(3000);
	}
	else if (step == step2)
	{
		gotoxy(0, 0); printf("%c", 218);
		for (int i = 1; i < 99; i++) { gotoxy(i, 0); printf("%c", 196); }
		gotoxy(100, 0); printf("%c", 191);
		for (int i = 1; i < 20; i++) { gotoxy(0, i); printf("%c", 179); }
		gotoxy(0, 20); printf("%c", 192);
		for (int i = 1; i < 20; i++) { gotoxy(100, i); printf("%c", 179); }
		gotoxy(100, 20); printf("%c", 217);
		for (int i = 1; i < 99; i++) { gotoxy(i, 20); printf("%c", 196); }
		gotoxy(30, 10); printf("Learning by trial of episode.");
	}
	else if (step == step3)
	{
		gotoxy(0, 0); printf("%c", 218);
		for (int i = 1; i < 99; i++) { gotoxy(i, 0); printf("%c", 196); }
		gotoxy(100, 0); printf("%c", 191);
		for (int i = 1; i < 20; i++) { gotoxy(0, i); printf("%c", 179); }
		gotoxy(0, 20); printf("%c", 192);
		for (int i = 1; i < 20; i++) { gotoxy(100, i); printf("%c", 179); }
		gotoxy(100, 20); printf("%c", 217);
		for (int i = 1; i < 99; i++) { gotoxy(i, 20); printf("%c", 196); }
		gotoxy(30, 10); printf("After learning.");
		Sleep(3000);
	}
	else
	{
		SetConsoleOutputCP(949);
		return 1;
	}
	SetConsoleOutputCP(949);
	return 0;
}