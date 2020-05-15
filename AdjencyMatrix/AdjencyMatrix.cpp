// AdjencyMatrix.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "common.h"


int main()
{
    MGraph G;
    createGraph(G);
    //printGraph(G);
    //char v0Name[BUFF_SIZE] = { 0 };
    //getVex(G, 0, v0Name);
    //cout << "v0Name: " << v0Name << endl;
    //putVex(G, 0, "hahah");
    //printGraph(G);
    //putVex(G, 0, "v0");
    //cout << "v0Name: " << v0Name << endl;
    //cout << "Insert vertex..." << endl;
    //insertVex(G, 2);
    //printGraph(G);
    //cout << "delete vertex 2" << endl;
    //deleteVex(G, 2);
    //printGraph(G);
    //cout << "insert Arc..." << endl;
    //insertVex(G, 2);
    //putVex(G, 2, "v2");
    //insertVex(G, 3);
    //putVex(G, 3, "v3");
    //insertVex(G, 4);
    //putVex(G, 4, "v4");
    //insertArc(G, 0, 2, 11);
    //printGraph(G);
    //cout << "delete arc for vertex 0, 2" << endl;
    //deleteArc(G, 0, 2);
    //printGraph(G);
    ////add arc for v0 and v1
    //insertArc(G, 0, 1, 1);
    ////add arc for v0 and v2
    //insertArc(G, 0, 2, 1);
    //// add arc for v1 and v3
    //insertArc(G, 1, 3, 1);
    //// add arc for v2 and v3
    //insertArc(G, 2, 3, 1);
    printGraph(G);
    cout << "DFS traverse..." << endl;
    DFSTraverse(G, display);
    cout << endl;
    cout << "BFS traverse..." << endl;
    BFSTraverse(G, display);
    cout << endl;
    //cout << "迪杰斯特拉算法" << endl;
    //bool * P [MAX_VERTEX_NUM];
    //for (int i = 0; i < MAX_VERTEX_NUM; ++i)
    //    P[i] = (bool *)malloc(sizeof(bool) * MAX_VERTEX_NUM);
    //int D[MAX_VERTEX_NUM] = { 0 };
    //shortestPath_DIJ(G, 0, (PathMatrix)P, D);
    //cout << "Shortest path:" << endl;
    //for (int i = 0; i < G.vexnum; ++i) {
    //    cout << D[i] << " ";
    //}
    //cout << endl;
    //for (int i = 0; i < MAX_VERTEX_NUM; ++i)
    //    free(P[i]);
    cout << "Prim algorithm..." << endl;
    miniSpanTreee_PRIM(G, "v0");

    cout << "minSpanTree_KRUSKAL..." << endl;
    minSpanTree_KRUSKAL(G);

    destroyGraph(G);
    return 0;
}

