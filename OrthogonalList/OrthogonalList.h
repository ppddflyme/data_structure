#pragma once

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#define MAX_VERTEX_NUM 20
typedef int InfoType;
typedef char * VertexType;
typedef int status;

typedef struct ArcBox {
    int           tailVex; // 该弧的尾顶点的位置
    int           headVex; // 该弧的头顶点的位置
    struct ArcBox * hlink; // 弧头相同的弧的链域
    struct ArcBox * tlink; // 弧尾相同的弧的链域
    InfoType      info;    // 该弧的权值
} ArcBox;

typedef struct VexNode {
    VertexType data;       // 顶点的名称
    ArcBox     * firstIn;  // 第一条入弧
    ArcBox     * firstOut; // 第一条出弧
} VexNode;

typedef struct {
    VexNode xlist[MAX_VERTEX_NUM]; // 表头向量
    int     vexNum;                // 有向图的顶点数
    int     arcNum;                // 有向图的弧数
} OLGraph;

#define MAX_BUFF_SIZE 10

#define CHECK_PTR(ptr)\
    if (!ptr) {\
        cout << "allocate memory failed!!!" << __FILE__ << ": " << __LINE__ << endl;\
        return -1;\
    }

status locateVex(const OLGraph & G, const char * vexName) {
    for (int i = 0; i < 0; ++i) {
        if (strncmp(G.xlist[i].data, vexName, strlen(vexName)) == 0) {
            return i;
        }
    }
    return -1;
}

status createDG(OLGraph & G);

void printGraph(const OLGraph & G);

status destroyGraph(OLGraph G);



