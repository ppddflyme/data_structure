// OrthogonalList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "OrthogonalList.h"


int main()
{
    OLGraph G;
    createDG(G);
    printGraph(G);
    destroyGraph(G);
    return 0;
}

status createDG(OLGraph & G)
{
    cout << "Please input vertex num" << endl;
    cin >> G.vexNum;
    for (int i = 0; i < G.vexNum; ++i) {
        G.xlist[i].firstIn = nullptr;
        G.xlist[i].firstOut = nullptr;
    }
    int cnt = 0;
    do {
        cout << "Please input " << cnt << "th node name: " << endl;
        char buf[MAX_BUFF_SIZE] = { 0 };
        cin >> buf;
        G.xlist[cnt].data = (VertexType)malloc(sizeof(char) * MAX_BUFF_SIZE);
        strncpy_s(G.xlist[cnt].data, MAX_BUFF_SIZE, buf, strlen(buf));
    } while (++cnt < G.vexNum);
    
    cout << "Please input arc num:" << endl;
    cin >> G.arcNum;
    cnt = 0;
    do {
        cout << "Please input " << cnt << "th arc: " << endl;
        char u[MAX_BUFF_SIZE] = { 0 }, v[MAX_BUFF_SIZE] = { 0 };
        int weight = 0;
        cin >> u >> v >> weight;
        int i = locateVex(G, u);
        int j = locateVex(G, v);
        ArcBox * p = (ArcBox *)malloc(sizeof(ArcBox));
        CHECK_PTR(p);
        p->tailVex = i;
        p->headVex = j;
        p->info = weight;
        p->hlink = G.xlist[j].firstIn;
        p->tlink = G.xlist[i].firstOut;
    } while (++cnt < G.arcNum);
    return 0;
}

void printGraph(const OLGraph & G)
{
    cout << "Graph vertex num: " << G.vexNum << " , arc num: " << G.arcNum << endl;
    cout << "Print all the vertex's name: " << endl;
    for (int i = 0; i < G.vexNum; ++i)
        cout << G.xlist[i].data << " ";
    cout << endl;
}

status destroyGraph(OLGraph G)
{
    for (int i = 0; i < G.vexNum; ++i)
        free(G.xlist[i].data);
    return 0;
}
