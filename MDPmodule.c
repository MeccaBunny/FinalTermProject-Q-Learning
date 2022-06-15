#include<stdlib.h>
#include<windows.h>
#include<stdio.h>
#include<math.h>

#include"random.h"
#include"MDPmodule.h"
#include"LakeGame.h"
#include"VisualTool.h"

MDPN** NM;
int NMw;
int NMh;

MDPN* search;
MDPN NULLnode;
int age;

int MDPN_init(MDPN* node, int index)
{
	node->index = index;
	roller_create(&node->roller);
	roller_set(&node->roller, stay, 0);
	roller_set(&node->roller, up, 0);
	roller_set(&node->roller, right, 0);
	roller_set(&node->roller, down, 0);
	roller_set(&node->roller, left, 0);
	node->reward = 0;
}
int MDPN_end(MDPN* node)
{
	roller_end(&node->roller);
}
int MDPN_connect(MDPN* snode, Direction direction, MDPN* enode)
{
	if (direction == up)
	{
		snode->up_next = enode;
		enode->down_next = snode;
		roller_set(&snode->roller, up, 0);
		roller_set(&enode->roller, down, 0);
	}
	else if (direction == right)
	{
		snode->right_next = enode;
		enode->left_next = snode;
		roller_set(&snode->roller, right, 0);
		roller_set(&enode->roller, left, 0);
	}
	else if (direction == down)
	{
		snode->down_next = enode;
		enode->up_next = snode;
		roller_set(&snode->roller, down, 0);
		roller_set(&enode->roller, up, 0);
	}
	else if (direction == left)
	{
		snode->left_next = enode;
		enode->right_next = snode;
		roller_set(&snode->roller, left, 0);
		roller_set(&enode->roller, right, 0);
	}
	else
	{
		return 1;
	}
	return 0;
}
int MDPN_setpb(MDPN* node, Direction direction, double pb)
{
	switch (direction)
	{
	case stay:
		roller_set(&node, stay, pb);
		break;
	case up:
		roller_set(&node, up, pb);
		break;
	case right:
		roller_set(&node, right, pb);
		break;
	case down:
		roller_set(&node, down, pb);
		break;
	case left:
		roller_set(&node, left, pb);
		break;
	default:
		return 1;
	}
	return 0;
}
int MDPN_Control(MDPN* target, Direction direction)
{
	if (direction == up)
	{
		if (target->up_next->index != 0)
			target = target->up_next;
	}
	else if (direction == right)
	{
		if (target->right_next->index != 0)
		{
			target = target->right_next;
		}
	}
	else if (direction == down)
	{
		if (target->down_next->index != 0)
			target = target->down_next;
	}
	else if (direction == left)
	{
		if (target->left_next->index != 0)
			target = target->left_next;
	}
	else if (direction == stay)
	{
	}
	else
	{
		return 1;
	}
	return 0;
}
int MDPN_show(MDPN* target)
{
	printf("(");
	
	if (target->up_next)
		printf("%d",target->up_next->index);
	else
		printf("X");
	printf("/");
	
	if (target->right_next)
		printf("%d", target->right_next->index);
	else
		printf("X");
	printf("/");
	
	if (target->down_next)
		printf("%d", target->down_next->index);
	else
		printf("X");
	printf("/");
	
	if (target->left_next)
		printf("%d", target->left_next->index);
	else
		printf("X");
	
	printf(")");
}

int MDP_init()
{
	MDPN_init(&NULLnode, 0);

	Lake_msg_type* Lake_getMsg = Lake_sendMsg();
	NMw = Lake_getMsg->bmw;
	NMh = Lake_getMsg->bmh;

	NM = (MDPN**)malloc(sizeof(MDPN*) * Lake_getMsg->bmh);
	for (int i = 0; i < Lake_getMsg->bmh; i++)
		NM[i] = (MDPN*)malloc(sizeof(MDPN) * Lake_getMsg->bmw);

	for (int i = 0; i < Lake_getMsg->bmh; i++)
		for (int j = 0; j < Lake_getMsg->bmw; j++)
			MDPN_init(&NM[i][j], i * Lake_getMsg->bmh + j + 1);

	for (int j = 0; j < Lake_getMsg->bmh; j++)
	{
		MDPN_connect(&NM[j][0], left, &NULLnode);
		for (int i = 0; i < Lake_getMsg->bmw - 1; i++)
			MDPN_connect(&NM[j][i], right, &NM[j][i + 1]);
		MDPN_connect(&NM[j][Lake_getMsg->bmw - 1], right, &NULLnode);
	}
	for (int j = 0; j < Lake_getMsg->bmw; j++)
	{
		MDPN_connect(&NM[0][j], up, &NULLnode);
		for (int i = 0; i < Lake_getMsg->bmh - 1; i++)
			MDPN_connect(&NM[i][j], down, &NM[i + 1][j]);
		MDPN_connect(&NM[Lake_getMsg->bmh - 1][j], down, &NULLnode);
	}

	MDPN_connect(&NULLnode, stay, &NULLnode);
	MDPN_connect(&NULLnode, up, &NULLnode);
	MDPN_connect(&NULLnode, right, &NULLnode);
	MDPN_connect(&NULLnode, down, &NULLnode);
	MDPN_connect(&NULLnode, left, &NULLnode);

	NULLnode.index = -1;
	NULLnode.reward = 0;

	for (int i = 0; i < Lake_getMsg->bmh; i++)
	{
		for (int j = 0; j < Lake_getMsg->bmw; j++)
		{
			if (NM[i][j].up_next != &NULLnode)
				roller_set(&NM[i][j].roller, up, 0);
			if (NM[i][j].right_next != &NULLnode)
				roller_set(&NM[i][j].roller, right, 0);
			if (NM[i][j].down_next != &NULLnode)
				roller_set(&NM[i][j].roller, down, 0);
			if (NM[i][j].left_next != &NULLnode)
				roller_set(&NM[i][j].roller, left, 0);
		}
	}

	search = &NM[getPlayery()][getPlayerx()];

	NM[getEndingy()][getEndingx()].reward = 1;
	for (int i = 0; i < Lake_getMsg->numOfBomb; i++)
	{
		int bx = Lake_getMsg->bx[i];
		int by = Lake_getMsg->by[i];

		NM[by][bx].reward = -1;
	}

	age = 1;
}
void MDP_end()
{
	Lake_msg_type* Lake_getMsg = Lake_sendMsg();
	for (int i = 0; i < Lake_getMsg->bmh; i++)
	{
		for (int j = 0; j < Lake_getMsg->bmw; j++)
			MDPN_end(&NM[i][j]);
		free(NM[i]);
	}
	free(NM);
	MDPN_end(&NULLnode);
	int age = 1;
}
int MDP_update()
{
	search = &NM[getPlayery()][getPlayerx()];
}
Direction MDP_decision()
{
	age += 1;
	Direction direction = roller_roll(&search->roller, (1 / (1 + exp(-age / 100000))));
	switch (direction)
	{
	case up:
		if (search->up_next == &NULLnode)
			return stay;
		break;
	case right:
		if (search->right_next == &NULLnode)
			return stay;
		break;
	case down:
		if (search->down_next == &NULLnode)
			return stay;
		break;
	case left:
		if (search->left_next == &NULLnode)
			return stay;
		break;
	case stay:

		break;
	}
	return direction;
}
int MDP_fit(Direction action)
{
	double A = 0.3;
	double Qp = A;

	MDPN* next;
	switch (action)
	{
	case up:
		next = search->up_next;
		break;
	case right:
		next = search->right_next;
		break;
	case down:
		next = search->down_next;
		break;
	case left:
		next = search->left_next;
		break;
	case stay:
		return 1;
	default:
		return 1;
	}

	search->reward = roller_maxpb(&next->roller);
	Qp = (1 - A) * roller_getpb(&search->roller, action) + A * (next->reward + 0.95 * roller_maxpb(&next->roller));
	roller_set(&search->roller, action, Qp);
	return 0;
}
void MDP_show()
{
	if ((NMh <= 5) && (NMw <= 5))
	{
		for (int i = 0; i < NMh; i++)
		{
			for (int j = 0; j < NMw; j++)
			{
				textcolor(2); gotoxy(20 + 15 * j + 0, 2 + 4 * i + 0); printf("%d", NM[i][j].index);
				textcolor(3); gotoxy(20 + 15 * j + 5, 2 + 4 * i + 0); printf("%.2lf", roller_getpb(&NM[i][j].roller, right));
				textcolor(4); gotoxy(20 + 15 * j + 0, 2 + 4 * i - 1); printf("%.2lf", roller_getpb(&NM[i][j].roller, up));
				textcolor(5); gotoxy(20 + 15 * j + 0, 2 + 4 * i + 1); printf("%.2lf", roller_getpb(&NM[i][j].roller, down));
				textcolor(6); gotoxy(20 + 15 * j - 5, 2 + 4 * i + 0); printf("%.2lf", roller_getpb(&NM[i][j].roller, left));
			}
		}
		textcolor(15);
	}
}
MDPN* MDPN_IDtoNode(int index)
{
	for (int i = 0; i < NMh; i++)
		for (int j = 0; j < NMw; j++)
			if (NM[i][j].index == index)
				return &NM[i][j];
	return -1;
}
int getID()
{
	if (search->index)
		return search->index;
	return -1;
}

int Trace_init(Trace* t)
{
	Footage* head = (Footage*)malloc(sizeof(Footage));
	Footage* tail = (Footage*)malloc(sizeof(Footage));

	head->index = -1;
	head->direction = stay;
	head->next = tail;
	head->prev = NULL;

	tail->index = -1;
	tail->direction = stay;
	tail->next = NULL;
	tail->prev = head;

	t->head = head;
	t->tail = tail;
	t->size = 0;
}
int Trace_end(Trace* t)
{
	Footage* foot1;
	Footage* foot2;
	foot1 = t->tail;
	while (foot1)
	{
		foot2 = foot1;
		foot1 = foot2->prev;
		free(foot2);
	}
}
int Trace_Append(Trace* t, int index, Direction direction)
{
	Footage* tmp = malloc(sizeof(Footage));
	tmp->index = index;
	tmp->direction = direction;
	tmp->prev = t->tail->prev;
	tmp->next = t->tail;

	t->tail->prev->next = tmp;
	t->tail->prev = tmp;
	t->size += 1;
}
void Trace_show(Trace* t)
{
	gotoxy(0, 24); printf("                                                                             ");
	gotoxy(0, 24);
	for (Footage* search = t->tail->prev; search->prev; search = search->prev)
		printf("(%d,%d)<-", search->index, search->direction);
}
int Trace_in(Trace* t, int id)
{
	for (Footage* foot = t->head->next; foot->next != NULL; foot = foot->next)
	{
		if (foot->index == id)
			return 1;
	}
	return 0;
}
int Trace_size(Trace* t)
{
	if (t->size)
		return t->size;
	return -1;
}
