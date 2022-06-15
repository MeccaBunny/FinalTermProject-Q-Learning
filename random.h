#ifndef RANDOM
#define RANDOM

#ifndef BOOL
#define BOOL

typedef enum _bool { false, true } bool;

#endif

double random();
int randint(int sn, int en);

#ifndef ROLLER
#define ROLLER

typedef struct _Prob
{
	struct _Prob* next;
	struct _Prob* prev;
	int index;
	double  pb;
	bool headflag;
	bool tailflag;
}Prob;

typedef struct _Roller
{
	Prob* head;
	Prob* tail;
	int ProbsSize;
}Roller;

#endif

void roller_create(Roller* r);
void roller_end(Roller* r);
int roller_set(Roller* r, int index, double prob);
int roller_roll(Roller* r, double pb);
void roller_show(Roller* r);
double roller_getpb(Roller* r, int index);
double roller_maxpb(Roller* r);

#endif

/**********************************************************
* roller design
*
* roller r1;
* roller_create(&r1);
* roller_set(&r1, 0, 0.8);
* roller_set(&r1, 1, 0.3);
* roller_set(&r1, 2, 0.2);
* roller_set(&r1, 0, 0.5);
*
* roller_show(&r1);
* int r1_result = roller_roll(&r1);
* roller_end(&r1);
**********************************************************/
