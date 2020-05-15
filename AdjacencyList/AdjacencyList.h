#pragma once

#define MAX_VERTEX_NUM 20

typedef char * VertexType;
typedef int status;

typedef enum { DG, DN, UDG, UDN } GraphKind; // {有向图, 有向网, 无向图, 无向网}

typedef void (*Visit) (const char *);

#define MAX_BUFF_SIZE 10
#define CHECK_PTR(ptr)\
    if (!ptr) {\
        cout << "allocate memory failed!!!" << __FILE__ << ": " << __LINE__ << endl;\
        return -1;\
    }

#define CHECK_VERTEX(v) \
    if (v < 0 || v >= MAX_VERTEX_NUM) {\
        cout << "You input invalid vertex id: " << v << "---" << __FILE__ << ": " << __LINE__ << endl;\
        return -1;\
    }\
    else {\
        if (G.vertices[v].firstArc == nullptr) {\
            cout << "You input invalid vertex id: " << v << "---" << __FILE__ << ": " << __LINE__ << endl;\
            return -1;\
        }\
    }

typedef struct ArcNode {
    int            adjvex;    // 该弧所指向的顶点的位置
    struct ArcNode * nextArc; // 指向下一条弧的指针
    int            info;      // 弧的权重 
} ArcNode;

typedef struct VNode {
    VertexType data;       // 顶点的信息
    ArcNode    * firstArc; // 指向第一条依附改顶点的弧的指针
}VNode, AdjList[MAX_VERTEX_NUM];

typedef struct {
    AdjList   vertices;
    int       vexnum, arcnum; // 图的当前顶点数和弧数
    GraphKind kind;           // 图的类型
}ALGraph;

status createGraph(ALGraph & G);

void printGraph(const ALGraph & G);

status destroyGraph(ALGraph & G);

/*
    初始条件: 图G存在
    操作结果: 若G中存在顶点v, 则返回该顶点在图中的位置，否则返回其他信息
*/
int locateVex(const ALGraph & G, const char *v);

/*
    初始条件: 图G存在, v是图G中的某个点
    操作结果: 返回v的值
*/
status getVex(const ALGraph & G, int v, char * vVal);

status putVex(ALGraph & G, int v, const char * value);

status firstAdjVex(const ALGraph & G, int v);

void printFirstArc(const ALGraph & G);

inline void print(const char * str) {
    cout << str << " ";
}

status nextAdjVex(const ALGraph & G, int v, int w);

status insertVex(ALGraph & G, int v);

status deleteVex(ALGraph & G, int v);

status insertArc(ALGraph &G, int v, int w, int weight);

status deleteArc(ALGraph & G, int v, int w);

status DFSTraverse(const ALGraph & G, Visit visit);

void DFS(const ALGraph & G, int i, bool * visited, Visit visit);

status BFSTraverse(const ALGraph & G, Visit visit);


