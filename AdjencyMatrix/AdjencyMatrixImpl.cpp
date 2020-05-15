#include "stdafx.h"
#include "common.h"



status createGraph(MGraph & G) {
    scanf_s("%d", &(G.kind));
    switch (G.kind) {
    case UDN:
        return createUDN(G);
    default:
        return FAILURE;
    }
    return SUCCESS;

}

status createUDN(MGraph & G) {
    cout << "请输入顶点数目，边的数目，弧的信息" << endl;
    scanf_s("%d %d", &G.vexnum, &G.arcnum);
    for (int i = 0; i < G.vexnum; ++i) {
        char buf[BUFF_SIZE] = { 0 };
        scanf_s("%s", buf, BUFF_SIZE);
        int bufSize = sizeof(buf) / sizeof(buf[0]);
        G.vexs[i] = (VertexType)malloc(sizeof(char) * bufSize);
        if (!G.vexs[i]) {
            cout << "memory is not enough" << endl;
            return FAILURE;
        }
        memcpy_s(G.vexs[i], bufSize, buf, bufSize);
    }
    for (int i = 0; i < G.vexnum; ++i)
        cout << G.vexs[i] << " ";
    cout << endl;
    for (int i = 0; i < G.vexnum; ++i)
        for (int j = 0; j < G.vexnum; ++j) // 初始化邻接矩阵
            G.arcs[i][j] = { static_cast<int>(INFINITY), NULL }; // {adj, info}
    cout << "请输入边的信息" << endl;
    for (int k = 0; k < G.arcnum; ++k) {
        char v1[BUFF_SIZE] = { 0 },
             v2[BUFF_SIZE] = { 0 };
        int weight = 0;
        scanf_s("%s %s %d", v1, BUFF_SIZE, v2, BUFF_SIZE, &weight);
        int i = locateVex(G, v1); // 确定v1和v2在G中的位置
        if (i == -1) {
            cout << "cannot find vex " << v1 << endl;
            return FAILURE;
        }
        int j = locateVex(G, v2);
        if (j == -1) {
            cout << "cannot find vex " << v2 << endl;
            return FAILURE;
        }
        G.arcs[i][j].adj = weight;
        G.arcs[j][i] = G.arcs[i][j];
    }
    return SUCCESS;
}

int locateVex(const MGraph & G, const char * v)
{
    for (int i = 0; i < G.vexnum; ++i)
        if (strncmp(G.vexs[i], v, strlen(v)) == 0)
            return i;
    return -1;
}

void printGraph(const MGraph & G)
{
    cout << "vertex num: " << G.vexnum << endl;
    cout << "edge num: " << G.arcnum << endl;
    cout << "vertex..." << endl;
    for (int i = 0; i < G.vexnum; ++i)
        cout << G.vexs[i] << " ";
    cout << endl;
    cout << "adjcent matrix..." << endl;
    for (int i = 0; i < G.vexnum; ++i) {
        for (int j = 0; j < G.vexnum; ++j)
            cout << G.arcs[i][j].adj << " ";
        cout << endl;
    }
    cout << "adjcent edge" << endl;
    for (int i = 0; i < G.vexnum; ++i) {
        int fAdjVex = firstAdjVex(G, i);
        cout << "v" << i << " first adj vex: " << fAdjVex << endl;
        cout << "v" << i << " next adj vex: " << nextAdjVex(G, i, fAdjVex) << endl;
    }
}

status destroyGraph(MGraph & G)
{
    switch (G.kind)
    {
    case UDN:
        destroyUDN(G);
        return SUCCESS;
    default:
        return FAILURE;
    }
}

status destroyUDN(MGraph & G)
{
    for (int i = 0; i < G.vexnum; ++i)
        free(G.vexs[i]);
    return SUCCESS;
}

status getVex(const MGraph & G, int v, char * vValue)
{
    if ((vValue == NULL) || (v >(G.vexnum - 1)))
        return FAILURE;
    size_t size = strlen(G.vexs[v]);
    strncpy_s(vValue, BUFF_SIZE, G.vexs[v], size);
    return SUCCESS;
}

status putVex(MGraph & G, int v, const char * val)
{
    if (v < 0 || v > G.vexnum)
        return FAILURE;
    if (val == NULL)
        return FAILURE;
    //char buf[BUFF_SIZE] = { 0 };
    try {
        //strncpy_s(buf, BUFF_SIZE, G.vexs[v], strlen(G.vexs[v]));
        if (strlen(G.vexs[v]) == strlen(val))
            strncpy_s(G.vexs[v], strlen(G.vexs[v]), val, strlen(val));
        else {
            free(G.vexs[v]);
            G.vexs[v] = (VertexType)malloc(strlen(val) * sizeof(char) + 1);
            memset(G.vexs[v], 0, strlen(val));
            strncpy_s(G.vexs[v], strlen(val) * sizeof(char) + 1, val, strlen(val));
        }
    }
    catch (...) {
        /*G.vexs[v] = (VertexType)malloc(strlen(buf) * sizeof(char));*/
        //memset(G.vexs[v], 0, strlen(buf));
        //strncpy_s(G.vexs[v], strlen(buf), buf, strlen(buf));
        return FAILURE;
    }
    return SUCCESS;
}

int firstAdjVex(const MGraph & G, int v)
{
    for (int i = 0; i < G.vexnum; ++i) {
        if (G.arcs[v][i].adj != INFINITY)
            return i;
    }

    return -1;
}

int nextAdjVex(const MGraph & G, int v, int w)
{
    if (w == -1)
        return -1;
    for (int i = w + 1; i < G.vexnum; ++i) {
        if (G.arcs[v][i].adj != INFINITY)
            return i;
    }
    return -1;
}

status insertVex(MGraph & G, int v)
{
    if (G.vexnum == MAX_VERTEX_NUM) {
        cout << "vex count beyond " << MAX_VERTEX_NUM << endl;
        return FAILURE;
    }
    if (v < 0 || v > MAX_VERTEX_NUM) {
        cout << "Please input valid vertex [0, " << MAX_VERTEX_NUM << ")" << endl;
        return FAILURE;
    }
    if (v < G.vexnum) {
        cout << "The given vertex " << v << " has already existed!!!" << endl;
        return FAILURE;
    }
    // init vertex
    G.vexs[v] = (VertexType)malloc(sizeof(char));
    if (G.vexs[v] == NULL) {
        cout << "allocate memory failed !!!" << endl;
        return FAILURE;
    }
    // init edge regarding new vertex v
    for (int i = 0; i < G.vexnum; ++i) {
        G.arcs[i][v].adj = INFINITY;
        G.arcs[v][i].adj = INFINITY;
    }
    G.arcs[v][v].adj = INFINITY;
    //increase vertex num
    ++G.vexnum;
    return SUCCESS;
}

status deleteVex(MGraph & G, int v)
{
    if (v < 0 || v > G.vexnum) {
        cout << "Please input valid vertex num [0, " << G.vexnum << ")" << endl;
        return FAILURE;
    }
    // delete vertex
    free(G.vexs[v]);
    G.vexs[v] = NULL;
    // delete edge regarding vertex v
    int deleteEdge = 0;
    for (int i = 0; i < G.vexnum; ++i) {
        if (G.arcs[v][i].adj != INFINITY)
            deleteEdge++;
        G.arcs[v][i].adj = INFINITY;
        if (G.arcs[i][v].adj != INFINITY)
            deleteEdge++;
        G.arcs[i][v].adj = INFINITY;
    }
    --G.vexnum;
    G.arcnum -= deleteEdge;
    return SUCCESS;
}

status insertArc(MGraph & G, int v, int w, VRType val)
{
    CHECK_VERTEX(v);
    CHECK_VERTEX(w);
    G.arcs[v][w].adj = val;
    if (G.kind == UDG ||G.kind == UDN)
        G.arcs[w][v].adj = val;
    ++G.arcnum;
    return SUCCESS;
}

status deleteArc(MGraph & G, int v, int w)
{
    CHECK_VERTEX(v);
    CHECK_VERTEX(w);
    G.arcs[v][w].adj = INFINITY;
    if (G.kind == UDG || G.kind == UDN)
        G.arcs[w][v].adj = INFINITY;
    --G.arcnum;

    return SUCCESS;
}

status DFSTraverse(const MGraph & G, VisitFunPtr visit)
{
    bool visited[MAX_VERTEX_NUM] = { false };
    
    for (int v = 0; v < G.vexnum; ++v) {
        if (!visited[v]) DFS(G, v,visited, visit);
    }
    return SUCCESS;
}

void DFS(const MGraph & G, int v, bool * visited, VisitFunPtr visit)
{
    visit(G.vexs[v]);
    visited[v] = true;
    for (int w = firstAdjVex(G, v); w != -1; w = nextAdjVex(G, v, w))
        if (!visited[w]) DFS(G, w, visited, visit);
}

void BFSTraverse(const MGraph & G, VisitFunPtr visit)
{
    bool visited[MAX_VERTEX_NUM] = { false };
    LinkQueue Q;
    initQueue(Q);

    for (int v = 0; v < G.vexnum; ++v) {
        if (!visited[v]) {
            visited[v] = true;
            visit(G.vexs[v]);
            enQueue(Q, v);
            while (!queueEmpty(Q)) {
                int u = -1;
                deQueue(Q, &u);
                for (int w = firstAdjVex(G, u); w != -1; w = nextAdjVex(G, u, w)) {
                    if (!visited[w]) {
                        visited[w] = true;
                        visit(G.vexs[w]);
                        enQueue(Q, w);
                    }
                }
            }
        }
    }
    destroyQueue(Q);
}

status shortestPath_DIJ(const MGraph & G, int v0, PathMatrix P, ShortPathTable D)
{
    // 用Dijkstra算法求有向网G的v0顶点到其余顶点v的最短路径P[v]及其带权长度D[v].
    // 若P[v][w]为TRUE， 则w是从v0到v当前求得最短路径上的顶点。
    // final[v]为TRUE当且仅当v属于s,即已经求得从v0到v的最短路径。
    bool * final = (bool *)malloc(sizeof(bool) * G.vexnum);
    //CHECK_PTR(final);

    //initialize D, P, final
    for (int v = 0; v < G.vexnum; ++v) {
        D[v] = G.arcs[v0][v].adj;
        final[v] = false;
        for (int w = 0; w < G.vexnum; ++w) {
            P[v][w] = false;
        }
        if (D[v] < INFINITY) {
            P[v][v0] = true;
            P[v][v] = true;
        }
    }

    D[v0] = 0;
    final[v0] = true;
    // 开始主循环，每次求得v0到某个v顶点的最短路径, 并加v到s子集
    for (int i = 1; i < G.vexnum; ++i) {
        int min = INFINITY;
        int v = 0;
        for (int w = 0; w < G.vexnum; ++w) {
            if (!final[w]) {  //找到从v0到v最短的一条路径
                if (D[w] < min) {
                    min = D[w];
                    v = w;
                }
            }
        }
        final[v] = true;
        for (int w = 0; w < G.vexnum; ++w) {
            if (!final[w]) {
                if (G.arcs[v][w].adj + min < D[w]) {
                    D[w] = G.arcs[v][w].adj + min;
                    P[w] = P[v];
                    P[w][w] = true;
                }
            }
        }

    }
    
    if (final)
        free(final);
    return SUCCESS;
}

/*
    用Prim从第u个顶点除非 构造网G的最小生成树T，输出T的各条边。
    记录从顶点集U到V-U的代价最小的边的辅助数组定义
*/
status miniSpanTreee_PRIM(const MGraph & G, VertexType u)
{
    int k = locateVex(G, u);
    Closedge closedge;
    //construct vetex u's MST
    for (int i = 0; i < G.vexnum; ++i) {
        if (i != k) {
            closedge[i].adjVex = k;
            closedge[i].lowCost = G.arcs[k][i].adj;
        }
    }
    //Put k into U
    closedge[k].lowCost = 0;
    cout << G.vexs[k] << " ";
    for (int j = 1; j < G.vexnum; ++j) {
        // find the min edge
        k = miniEdge(closedge, G.vexnum);
        //cout << closedge[k].adjVex << " " << G.vexs[k] << endl;
        cout << G.vexs[k] << " ";
        closedge[k].lowCost = 0;
        for (int n = 0; n < G.vexnum; ++n) {
            if (G.arcs[k][n].adj < closedge[n].lowCost) {
                closedge[n].adjVex = k;
                closedge[n].lowCost = G.arcs[k][n].adj;
            }
        }
    }
    cout << endl;
    return SUCCESS;
}

int miniEdge(const Closedge & closedge, int vexNum)
{
    int minVex = 0;
    int minEdge = INFINITY;
    for (int i = 0; i < vexNum; ++i) {
        if (closedge[i].lowCost != 0) {
            if (minEdge > closedge[i].lowCost) {
                minEdge = closedge[i].lowCost;
                minVex = i;
            }
        }
    }

    return minVex;
}

status minSpanTree_KRUSKAL(const MGraph & G)
{
    int connection[MAX_VERTEX_NUM];
    ArcMatrix arcMatrix;
    sortArc(G, arcMatrix);

    for (int i = 0; i < G.arcnum; ++i) {
        cout << G.vexs[arcMatrix[i].u] << "-->"
            << G.vexs[arcMatrix[i].v] << " = " << arcMatrix[i].adj << endl;
    }

    for (int i = 0; i < G.vexnum; ++i)
        connection[i] = i;
    for (int j = 0; j < G.arcnum; ++j) {
        ArcType arc = arcMatrix[j];
        if (connection[arc.u] != connection[arc.v]) {
            cout << G.vexs[arc.u] << "-->" << G.vexs[arc.v] << endl;
            //update all the connection = arc.v to arc.u
            for (int k = 0; k < G.vexnum; ++k) {
                if (connection[k] == connection[arc.v] && k != arc.v) {
                    connection[k] = connection[arc.u];
                }
            }
            connection[arc.v] = connection[arc.u];
            //for (int i = 0; i < G.vexnum; ++i)
            //    cout << "connection[" << i << "] = " << connection[i] << endl;
        }
    }
    cout << endl;
    for (int i = 0; i < G.vexnum; ++i)
        cout << "connection[" << i << "] = " << connection[i] << endl;

    return SUCCESS;
}

status sortArc(const MGraph & G, ArcMatrix & arcMatrix)
{
    int arcNum = 0;
    ArcMatrix tempArcMatrix;
    for (int i = 0; i < G.vexnum; ++i) {
        for (int j = i + 1; j < G.vexnum; ++j) {
            if (G.arcs[i][j].adj != INFINITY) {
                tempArcMatrix[arcNum].u = i;
                tempArcMatrix[arcNum].v = j;
                tempArcMatrix[arcNum].adj = G.arcs[i][j].adj;
                arcNum++;
            }
            //if (arcNum >= G.vexnum)
            //    break;
        }
        //if (arcNum >= G.vexnum)
        //    break;
    }

    for (int i = 0; i < G.arcnum; ++i) {
        ArcType minArc = tempArcMatrix[i];
        for (int j = i + 1; j < G.arcnum; ++j) {
            if (minArc.adj > tempArcMatrix[j].adj) {
                ArcType tempArc = minArc;
                minArc = tempArcMatrix[j];
                tempArcMatrix[j] = tempArc;
            }
        }
        arcMatrix[i] = minArc;
    }
    return SUCCESS;
}
