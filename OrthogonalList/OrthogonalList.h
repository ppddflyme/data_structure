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
    int           tailVex; // �û���β�����λ��
    int           headVex; // �û���ͷ�����λ��
    struct ArcBox * hlink; // ��ͷ��ͬ�Ļ�������
    struct ArcBox * tlink; // ��β��ͬ�Ļ�������
    InfoType      info;    // �û���Ȩֵ
} ArcBox;

typedef struct VexNode {
    VertexType data;       // ���������
    ArcBox     * firstIn;  // ��һ���뻡
    ArcBox     * firstOut; // ��һ������
} VexNode;

typedef struct {
    VexNode xlist[MAX_VERTEX_NUM]; // ��ͷ����
    int     vexNum;                // ����ͼ�Ķ�����
    int     arcNum;                // ����ͼ�Ļ���
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



