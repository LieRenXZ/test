
typedef struct ArcNode
{
    int adjvex;
    struct ArcNode * next;
}ArcNode;

typedef struct VexNode
{
    char data;
    ArcNode * first_arc;
}VexNode;

typedef struct
{
    char vex[maxx];
    int vexnum,arcnum;
}Adjlist;//邻接表
