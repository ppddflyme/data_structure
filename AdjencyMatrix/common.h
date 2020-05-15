#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"
using std::cout;
using std::cin;
using std::endl;

//#define INFINITY       INF_MAX             //max value
#define MAX_VERTEX_NUM 20                  // max vertex number

#ifdef INFINITY
#undef INFINITY
#endif // INFINITY
#define INFINITY 0x70000000

#define CHECK_VERTEX(v) \
    if (v < 0 || v > G.vexnum) return FAILURE

typedef enum {DG, DN, UDG, UDN} GraphKind; // {有向图, 有向网, 无向图, 无向网}
typedef int VRType;
typedef char* VertexType;
typedef int InfoType;
#define BUFF_SIZE 10

#define CHECK_PTR(ptr) \
    if (ptr == nullptr)\
        cout << "ptr is nullptr--" << __FILE__ << ":" << __LINE__ << endl;\
        return FAILURE;

typedef int status;

#define SUCCESS 0
#define FAILURE 1

typedef struct ArcCell {
    VRType adj;     // VRType是顶点关系类型。对无权图， 用1或者0
                    // 表示相邻否;对带权图，则为权值类型。
    InfoType *info; // 该弧相关信息的指针
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct {
    VRType adjVex;
    VRType lowCost;
} CloseNode, Closedge[MAX_VERTEX_NUM];

typedef struct {
    VertexType vexs[MAX_VERTEX_NUM]; // 顶点向量
    AdjMatrix  arcs;                 // 邻接矩阵
    int        vexnum, arcnum;       // 图的当前顶点数和弧数
    GraphKind  kind;                 // 图的种类标志
} MGraph;

typedef void(*VisitFunPtr) (VertexType);



inline void display(VertexType vertexName) {
    cout << vertexName << " ";
}

status createGraph(MGraph & G);

status createUDN(MGraph & G);

int locateVex(const MGraph & G, const char * v);

void printGraph(const MGraph & G);

status destroyGraph(MGraph & G);

status destroyUDN(MGraph & G);

/*
    初始条件: 图G存在, v是G中某个顶点
    操作结果: 返回v的值
*/
status getVex(const MGraph & G, int v, char * vValue);

/*
    初始条件: 图G存在，v是G中某个顶点
    操作结果: 对v赋值val
*/
status putVex(MGraph & G, int v, const char *val);

/*
    初始条件: 图G存在, v是G中某个顶点。
    操作结果: 返回v的第一个邻接顶点。若顶点在G中没有邻接顶点, 则返回"空"
*/
int firstAdjVex(const MGraph & G, int v);

/*
    初始条件: 图G存在, v是G中某个顶点, w是v的邻接顶点。
    操作结果: 返回v的（相对于w的）下一个邻接顶点。若w都v的最后一个邻接点, 则返回“空”
*/
int nextAdjVex(const MGraph & G, int v, int w);

/*
    初始条件： 图G存在，v和图中顶点有相同的特征。
    操作结果： 在图G中增添新顶点V。
*/
status insertVex(MGraph & G, int v);

/*
    初始条件： 图G存在，v是G中某个顶点。
    操作结果： 删除G中顶点V及其相关的弧
*/
status deleteVex(MGraph & G, int v);

/*
    初始条件： 图G存在，V和W是G中两个顶点。
    操作结果： 在G中增添弧<v, w>，若G是无向的，还应该增添对称的弧<w,v>.
*/
status insertArc(MGraph & G, int v, int w, VRType val);

/*
    初始条件： 图G存在，v和W是G中的顶点
    操作结果： 在G中删除弧<v, w>, 若G是无向的， 还应该删除对称弧<w, v>
*/
status deleteArc(MGraph & G, int v, int w);

status DFSTraverse(const MGraph & G, VisitFunPtr visit);

void DFS(const MGraph & G, int v, bool * visited, VisitFunPtr visit);

void BFSTraverse(const MGraph & G, VisitFunPtr visit);

typedef bool ** PathMatrix;
typedef int* ShortPathTable;

typedef struct ArcType
{
    int    u;
    int    v;
    VRType adj;
    ArcType(const ArcType & that) {
        u = that.u;
        v = that.v;
        adj = that.adj;
    }
    ArcType() : u(0), v(0), adj(0) {}
    ArcType & operator = (const ArcType & that) {
        u = that.u;
        v = that.v;
        adj = that.adj;
        return *this;
    }

}ArcType, ArcMatrix[MAX_VERTEX_NUM];

status shortestPath_DIJ(const MGraph & G, int v0, PathMatrix P, ShortPathTable D);

status miniSpanTreee_PRIM(const MGraph & G, VertexType u);

int miniEdge(const Closedge & closedge, int vexNum);

status minSpanTree_KRUSKAL(const MGraph & G);

status sortArc(const MGraph & G, ArcMatrix & arcMatrix);