#include<stdlib.h>
#include<time.h>
#include<stdio.h>
#include<windows.h>

#include"random.h"

#define FALSE 0
#define TRUE 1

double random()
{
	static int init = FALSE;
	if (!init)
	{
		srand(time(NULL));
		init = TRUE;
	}
	return (double) rand() / RAND_MAX;
}
int randint(int sn, int en)
{
	static int init = FALSE;
	if (!init)
	{
		srand(time(NULL));
		init = TRUE;
	}
	return rand() % (en - sn + 1) + sn;
}

void roller_create(Roller* r)
{
	Prob* head = (Prob*)malloc(sizeof(Prob));
	Prob* tail = (Prob*)malloc(sizeof(Prob));

	head->next = tail;
	head->prev = NULL;
	head->index = 0;
	head->pb = 0;
	head->headflag = true;
	head->tailflag = false;

	tail->next = NULL;
	tail->prev = head;
	tail->index = 0;
	tail->pb = 0;
	tail->headflag = false;
	tail->tailflag = true;

	r->head = head;
	r->tail = tail;
	r->ProbsSize = 0;
}
void roller_end(Roller* r)
{
	Prob* search;
	for (search = r->head->next; search->next; search = search->next)
		free(search->prev);
	free(search);
}
int roller_set(Roller* r, int index, double prob)
{
	for (Prob* search = r->head->next; search->next != NULL; search = search->next)
	{
		if (search->index == index)
		{
			search->pb = prob;
			return 1;
		}
	}

	Prob* tmp = (Prob*)malloc(sizeof(Prob));

	tmp->next = r->tail;
	tmp->prev = r->tail->prev;
	tmp->index = index;
	tmp->pb = prob;
	tmp->headflag = false;
	tmp->tailflag = false;

	r->tail->prev->next = tmp;
	r->tail->prev = tmp;
	r->ProbsSize += 1;

	return 0;
}
void roller_show(Roller* r)
{
	printf("========================================================================================\n");
	Prob* search;
	printf("(begin)->");
	for (search = r->head->next; search->next; search = search->next)
		printf("(index:%d, prob:%.2lf)->", search->index, search->pb);
	printf("(end)\n");
	printf("ProbsSize:%d\n", r->ProbsSize);
	printf("========================================================================================\n");
}
int roller_roll(Roller* r, double pb)
{
	int* indexlist = (int*)malloc(sizeof(int) * r->ProbsSize);
	double* pblist = (double*)malloc(sizeof(double) * r->ProbsSize);

	Prob* search = r->head->next;
	for (int i = 0; i < r->ProbsSize; i++)
	{
		*(indexlist + i) = search->index;
		*(pblist + i) = search->pb;
		search = search->next;
	}
	for (int i = 0; i < r->ProbsSize; i++)
	{
		pblist[i] += (double)random() / 100000;
	}
	int max_pb_index = 0;
	for (int i = 0; i < r->ProbsSize; i++)
	{
		if (pblist[max_pb_index] < pblist[i])
			max_pb_index = i;
	}

	int ans = max_pb_index;
	if (random() < 1-pb)
	{
		while(ans == max_pb_index)
			ans = (int)(random() * 10000) % r->ProbsSize;
	}
	free(indexlist);
	free(pblist);
	return ans;
}
double roller_getpb(Roller* r, int index)
{
	if (r->head)
	{
		for (Prob* s = r->head->next; s->next != NULL; s = s->next)
		{
			if (s->index == index)
			{
				return s->pb;
			}
		}
	}
	return -1;
}
double roller_maxpb(Roller* r)
{
	double max = r->head->next->pb;
	for (Prob* s = r->head->next; s->next != NULL; s = s->next)
	{
		if (max < s->pb)
		{
			max = s->pb;
		}
	}
	return max;
}

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
