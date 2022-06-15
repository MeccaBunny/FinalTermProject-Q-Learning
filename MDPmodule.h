#ifndef MVP
#define MVP

#ifndef DIRECTION
#define DIRECTION

typedef enum _Direction { stay, up, right, down, left } Direction;

#endif

#ifndef TILE
#define TILE

typedef enum { nonePoint, startPoint, endPoint, bombPoint } tile;

#endif

typedef struct _MDPN
{
	int index;
	struct _MDPN* up_next;
	struct _MDPN* right_next;
	struct _MDPN* down_next;
	struct _MDPN* left_next;
	Roller roller;
	int reward;
}MDPN;

int MDPN_init(MDPN* node, int index);
int MDPN_end(MDPN* node);
int MDPN_connect(MDPN* snode, Direction direction, MDPN* enode);
int MDPN_setpb(MDPN* node, Direction direction, double pb);
int MDPN_Control(MDPN* target, Direction direction);
int MDPN_show(MDPN* target);

int MDP_init();
void MDP_end();
int MDP_update();
Direction MDP_decision();
int MDP_fit(Direction direction);
void MDP_show();
MDPN* MDPN_IDtoNode(int index);
int getID();

#ifndef TRACE
#define TRACE

typedef struct _Footage
{
	int index;
	Direction direction;
	struct _Footage* prev;
	struct _Footage* next;
}Footage;
typedef struct _Trace
{
	Footage* head;
	Footage* tail;
	int size;
}Trace;

int Trace_init(Trace* t);
int Trace_end(Trace* t);
int Trace_Append(Trace* t, int index, Direction direction);
void Trace_show(Trace* t);
int Trace_in(Trace* t, int id);
int Trace_size(Trace* t);

#endif

#endif