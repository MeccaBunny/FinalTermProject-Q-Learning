#ifndef VISUALTOOL_H
#define VISUALTOOL_H

void textcolor(int colorNum);
void gotoxy(int x, int y);
int clearScreen();

typedef enum { step1, step2, step3 } showSequence;
int prtLoading(showSequence step);

#endif