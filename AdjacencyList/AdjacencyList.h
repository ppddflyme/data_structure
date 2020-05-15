#pragma once

#define MAX_VERTEX_NUM 20

typedef char * VertexType;
typedef int status;

typedef enum { DG, DN, UDG, UDN } GraphKind; // {����ͼ, ������, ����ͼ, ������}

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
    int            adjvex;    // �û���ָ��Ķ����λ��
    struct ArcNode * nextArc; // ָ����һ������ָ��
    int            info;      // ����Ȩ�� 
} ArcNode;

typedef struct VNode {
    VertexType data;       // �������Ϣ
    ArcNode    * firstArc; // ָ���һ�������Ķ���Ļ���ָ��
}VNode, AdjList[MAX_VERTEX_NUM];

typedef struct {
    AdjList   vertices;
    int       vexnum, arcnum; // ͼ�ĵ�ǰ�������ͻ���
    GraphKind kind;           // ͼ������
}ALGraph;

status createGraph(ALGraph & G);

void printGraph(const ALGraph & G);

status destroyGraph(ALGraph & G);

/*
    ��ʼ����: ͼG����
    �������: ��G�д��ڶ���v, �򷵻ظö�����ͼ�е�λ�ã����򷵻�������Ϣ
*/
int locateVex(const ALGraph & G, const char *v);

/*
    ��ʼ����: ͼG����, v��ͼG�е�ĳ����
    �������: ����v��ֵ
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


