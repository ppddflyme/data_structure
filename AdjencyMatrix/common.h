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

typedef enum {DG, DN, UDG, UDN} GraphKind; // {����ͼ, ������, ����ͼ, ������}
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
    VRType adj;     // VRType�Ƕ����ϵ���͡�����Ȩͼ�� ��1����0
                    // ��ʾ���ڷ�;�Դ�Ȩͼ����ΪȨֵ���͡�
    InfoType *info; // �û������Ϣ��ָ��
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct {
    VRType adjVex;
    VRType lowCost;
} CloseNode, Closedge[MAX_VERTEX_NUM];

typedef struct {
    VertexType vexs[MAX_VERTEX_NUM]; // ��������
    AdjMatrix  arcs;                 // �ڽӾ���
    int        vexnum, arcnum;       // ͼ�ĵ�ǰ�������ͻ���
    GraphKind  kind;                 // ͼ�������־
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
    ��ʼ����: ͼG����, v��G��ĳ������
    �������: ����v��ֵ
*/
status getVex(const MGraph & G, int v, char * vValue);

/*
    ��ʼ����: ͼG���ڣ�v��G��ĳ������
    �������: ��v��ֵval
*/
status putVex(MGraph & G, int v, const char *val);

/*
    ��ʼ����: ͼG����, v��G��ĳ�����㡣
    �������: ����v�ĵ�һ���ڽӶ��㡣��������G��û���ڽӶ���, �򷵻�"��"
*/
int firstAdjVex(const MGraph & G, int v);

/*
    ��ʼ����: ͼG����, v��G��ĳ������, w��v���ڽӶ��㡣
    �������: ����v�ģ������w�ģ���һ���ڽӶ��㡣��w��v�����һ���ڽӵ�, �򷵻ء��ա�
*/
int nextAdjVex(const MGraph & G, int v, int w);

/*
    ��ʼ������ ͼG���ڣ�v��ͼ�ж�������ͬ��������
    ��������� ��ͼG�������¶���V��
*/
status insertVex(MGraph & G, int v);

/*
    ��ʼ������ ͼG���ڣ�v��G��ĳ�����㡣
    ��������� ɾ��G�ж���V������صĻ�
*/
status deleteVex(MGraph & G, int v);

/*
    ��ʼ������ ͼG���ڣ�V��W��G���������㡣
    ��������� ��G������<v, w>����G������ģ���Ӧ������ԳƵĻ�<w,v>.
*/
status insertArc(MGraph & G, int v, int w, VRType val);

/*
    ��ʼ������ ͼG���ڣ�v��W��G�еĶ���
    ��������� ��G��ɾ����<v, w>, ��G������ģ� ��Ӧ��ɾ���Գƻ�<w, v>
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