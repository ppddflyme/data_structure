// AdjacencyList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include "AdjacencyList.h"
#include "Queue.h"


int main()
{
    ALGraph G;
    createGraph(G);
    printGraph(G);
    //putVex(G, 0, "1111");
    //cout << "After modify v0's value to 1111" << endl;
    //printGraph(G);
    printFirstArc(G);
    //int nextArcNode = nextAdjVex(G, 0, 1);
    //cout << "nextAdjVex(G, 0, 1) = " << nextArcNode << endl;
    //nextArcNode = nextAdjVex(G, 1, 2);
    //cout << "nextAdjVex(G, 1, 2) = " << nextArcNode << endl;
    //status st = insertVex(G, 2);
    //if (st == 0)
    //    putVex(G, 2, "v2");
    cout << "Before deleting v0..." << endl;
    deleteVex(G, 0);
    cout << "After deleting v0..." << endl;
    printGraph(G);
    cout << "Before insert arc (v1, v2, 100)..." << endl;
    insertArc(G, 1, 2, 100);
    cout << "After insert arc (v1, v2, 100)..." << endl;
    printGraph(G);
    cout << "Before delete arc (v1, v2, 100)..." << endl;
    deleteArc(G, 1, 2);
    cout << "After delete arc (v1, v2, 100)..." << endl;
    printGraph(G);
    cout << "insert vertex v0..." << endl;
    insertVex(G, 0);
    putVex(G, 0, "v0");
    printGraph(G);
    cout << "insert vertex v3..." << endl;
    insertVex(G, 3);
    putVex(G, 3, "v3");
    printGraph(G);

    insertArc(G, 0, 1, 1);
    insertArc(G, 0, 2, 1);
    insertArc(G, 1, 2, 1);
    insertArc(G, 1, 3, 1);
    printGraph(G);

    cout << "DFSTraverse..." << endl;
    DFSTraverse(G, print);
    cout << endl;
    cout << "BFSTraverse..." << endl;
    BFSTraverse(G, print);
    cout << endl;
    destroyGraph(G);
    return 0;
}

status createGraph(ALGraph & G)
{
    G.kind = DN;
    G.vexnum = 0;
    G.arcnum = 0;

    cout << "Please input vertex num: " << endl;
    cin >> G.vexnum;
    int i = 0;
    for (int j = 0; j < MAX_VERTEX_NUM; ++j)
        G.vertices[j].firstArc = nullptr;
    do {
        char buf[MAX_BUFF_SIZE] = { 0 };
        cout << "Please input " << i << "th vertex" << endl;
        cin >> buf;
        G.vertices[i].data = (VertexType)malloc(sizeof(char) * MAX_BUFF_SIZE);
        CHECK_PTR(G.vertices[i].data);
        strncpy_s(G.vertices[i].data, MAX_BUFF_SIZE, buf, strlen(buf));
        G.vertices[i].firstArc = (ArcNode *) malloc(sizeof(ArcNode));
        G.vertices[i].firstArc->nextArc = NULL;
        CHECK_PTR(G.vertices[i].firstArc);
    } while (++i < G.vexnum);
    cout << "Please input arc num: " << endl;
    cin >> G.arcnum;
    int j = 0;
    do {
        char u[MAX_BUFF_SIZE] = { 0 };
        char v[MAX_BUFF_SIZE] = { 0 };
        int w = 0;
        cout << "Please vertex pair(u,v) and weight(w): u v w" << endl;
        cin >> u >> v >> w;
        int i = locateVex(G, u);
        int j = locateVex(G, v);
        ArcNode * tmpNode = (ArcNode *)malloc(sizeof(ArcNode));
        CHECK_PTR(tmpNode);
        tmpNode->adjvex = j;
        tmpNode->nextArc = NULL;
        tmpNode->info = w;
        ArcNode * p = G.vertices[i].firstArc;
        while (p->nextArc)
            p = p->nextArc;
        p->nextArc = tmpNode;
    } while (++j < G.arcnum);
    return 0;
}

void printGraph(const ALGraph & G)
{
    // print vertex num & arc num
    cout << "vertex num: " << G.vexnum << ", arc num: " << G.arcnum << endl;
    // print vertex
    cout << "print vertex..." << endl;
    int cnt = 0;
    for (int i = 0; i < MAX_VERTEX_NUM && cnt < G.vexnum; ++i) {
        char buf[MAX_BUFF_SIZE] = { 0 };
        if (G.vertices[i].firstArc)
            ++cnt;
        else
            continue;
        status  st = getVex(G, i, buf);
        if (st == 0) {
            cout << buf << " ";
        }
    }
    cout << endl;
    cout << "print arc..." << endl;
    cnt = 0;
    for (int i = 0; i < MAX_VERTEX_NUM && cnt < G.vexnum; ++i) {
        if (G.vertices[i].firstArc)
            ++cnt;
        else
            continue;
        ArcNode * tmpNode = G.vertices[i].firstArc->nextArc;
        while (tmpNode) {
            cout << G.vertices[i].data << " -> " << G.vertices[tmpNode->adjvex].data << ": " << tmpNode->info << endl;
            tmpNode = tmpNode->nextArc;
        }
    }
    cout << endl;
}

status destroyGraph(ALGraph & G)
{
    for (int i = 0; i < G.vexnum; ++i) {
        free(G.vertices[i].data);
        while (G.vertices[i].firstArc) {
            ArcNode * tmpNode = G.vertices[i].firstArc->nextArc;
            free(G.vertices[i].firstArc);
            G.vertices[i].firstArc = tmpNode;
        }
    }
    return 0;
}

int locateVex(const ALGraph & G, const char * v)
{
    for (int i = 0; i < G.vexnum; ++i) {
        if (strncmp(G.vertices[i].data, v, strlen(v)) == 0)
            return i;
    }

    return -1;
    return 0;
}

status getVex(const ALGraph & G, int v, char * vVal)
{
    //CHECK_VERTEX(v);
    if (G.vertices[v].data) {
        strncpy_s(vVal, MAX_BUFF_SIZE, G.vertices[v].data, strlen(G.vertices[v].data));
        return 0;
    }
    return -1;
}

status putVex(ALGraph & G, int v, const char * value)
{
    CHECK_VERTEX(v);
    CHECK_PTR(value);
    if (!G.vertices[v].data)
        free(G.vertices[v].data);
    G.vertices[v].data = (VertexType)malloc(sizeof(char) * MAX_BUFF_SIZE);
    CHECK_PTR(G.vertices[v].data);
    strncpy_s(G.vertices[v].data,
              MAX_BUFF_SIZE,
              value,
              strlen(value));
    return 0;
}

status firstAdjVex(const ALGraph & G, int v)
{
    CHECK_VERTEX(v);
    ArcNode * tmpNode = G.vertices[v].firstArc->nextArc;
    if (tmpNode)
        return tmpNode->adjvex;
    return -1;
}

void printFirstArc(const ALGraph & G)
{
    for (int i = 0; i < G.vexnum; ++i)
        cout << "vertex " << i << "'s first arc node is " << firstAdjVex(G, i) << endl;
}

status nextAdjVex(const ALGraph & G, int v, int w)
{
    CHECK_VERTEX(v);
    CHECK_VERTEX(w);
    ArcNode * tmpNode = G.vertices[v].firstArc->nextArc;
    while (tmpNode) {
        if (tmpNode->adjvex == w) {
            tmpNode = tmpNode->nextArc;
            break;
        }
        tmpNode = tmpNode->nextArc;
    }
    if (tmpNode)
        return tmpNode->adjvex;
    return -1;
}

status insertVex(ALGraph & G, int v)
{
    if (v < 0 || v > MAX_VERTEX_NUM) {
        cout << "You input an invalid node index: " << v << "---" << __FILE__ << ":" << __LINE__ << endl;
        return -1;
    }
    if (G.vertices[v].firstArc != nullptr) {
        cout << "The vertex " << v << " has already existed!!!" << "---" << __FILE__ << ":" << __LINE__ << endl;
        return -1;
    }
    G.vertices[v].firstArc = (ArcNode *)malloc(sizeof(ArcNode));
    CHECK_PTR(G.vertices[v].firstArc);
    G.vertices[v].firstArc->nextArc = nullptr;
    ++G.vexnum;
    return 0;
}

status deleteVex(ALGraph & G, int v)
{
    CHECK_VERTEX(v);
    if (G.vertices[v].data) {
        free(G.vertices[v].data);
        G.vertices[v].data = NULL;
    }
    --G.vexnum;
    ArcNode * p = G.vertices[v].firstArc->nextArc;
    //delete node v's list

    while (p) {
        ArcNode * q = p->nextArc;
        free(p);
        p = q;
        G.arcnum--;
    }
    free(G.vertices[v].firstArc);
    G.vertices[v].firstArc = nullptr;
    // delete link node regarding v
    int cnt = 0;
    for (int i = 0; i < MAX_VERTEX_NUM && cnt < G.vexnum; ++i) {
        if (G.vertices[i].firstArc)
            cnt++;
        else
            continue;
        if (i != v) {
            ArcNode * p = G.vertices[i].firstArc;
            while (p && p->nextArc) {
                if (p->nextArc->adjvex == v) {
                    ArcNode * q = p->nextArc;
                    p->nextArc = q->nextArc;
                    free(q);
                    G.arcnum--;
                }
                p = p->nextArc;
            }
        }
    }
    return 0;
}

status insertArc(ALGraph & G, int v, int w, int weight)
{
    CHECK_VERTEX(v);
    CHECK_VERTEX(w);

    ArcNode * p = G.vertices[v].firstArc;
    while (p->nextArc)
        p = p->nextArc;
    ArcNode * q = (ArcNode *)malloc(sizeof(ArcNode));
    CHECK_PTR(q);
    q->adjvex = w;
    q->info = weight;
    q->nextArc = nullptr;
    p->nextArc = q;
    ++G.arcnum;
    return 0;
}

status deleteArc(ALGraph & G, int v, int w)
{
    CHECK_VERTEX(v);
    CHECK_VERTEX(w);

    ArcNode * p = G.vertices[v].firstArc,
            * q = p->nextArc;
    while (p) {
        q = p->nextArc;
        if (q->adjvex == w) {
            p->nextArc = q->nextArc;
            free(q);
            --G.arcnum;
            break;
        }
    }

    return 0;
}

status DFSTraverse(const ALGraph & G, Visit visit)
{
    bool visited[MAX_VERTEX_NUM] = { false };
    for (int i = 0; i < G.vexnum; ++i) {
        if (!visited[i])
            DFS(G, i, visited, visit);
    }

    return 0;
}

void DFS(const ALGraph & G, int i, bool * visited, Visit visit)
{
    if (!visited[i]) {
        visit(G.vertices[i].data);
        visited[i] = true;
        for (int w = firstAdjVex(G, i); w != -1; w = nextAdjVex(G, i, w)) {
            if (!visited[w])
                DFS(G, w, visited, visit);
        }
    }
}

status BFSTraverse(const ALGraph & G, Visit visit)
{
    bool visited[MAX_VERTEX_NUM] = { false };
    LinkQueue Q;
    initQueue(Q);
    enQueue(Q, 0);
    while (!queueEmpty(Q)) {
        int v = 0;
        deQueue(Q, &v);
        if (!visited[v])
            visit(G.vertices[v].data);
        visited[v] = true;
        for (int w = firstAdjVex(G, v); w != -1; w = nextAdjVex(G, v, w)) {
            if (!visited[w])
                enQueue(Q, w);
        }
    }
    destroyQueue(Q);
    return 0;
}
