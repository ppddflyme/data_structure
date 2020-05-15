#include "stdafx.h"
#include <iostream>
#include "Stack.h"
#include "tree_data_structure.h"
#include "Queue.h"
using std::cout;
using std::endl;
using std::cin;

status createBiTree_level_traversal(BiTree & T, int nodeNum)
{
    int cnt = 1;
    if (nodeNum <= 0) {
        cout << "It's an empty tree..." << endl;
        return FAIL;
    }
    
    T = (BiTree)malloc(sizeof(BiTNode));
    CHECK_PTR(T);
    cout << "Please input root data: " << endl;
    int data;
    cin >> data;
    T->data = data;
    T->lchild = NULL;
    T->rchild = NULL;

    LinkQueue Q;
    initQueue(Q);
    push(Q, T);

    while (!queueEmpty(Q) && cnt < nodeNum) {
        int data;
        BiTree rootNode = pop(Q);
        BiTree lNode = (BiTree)malloc(sizeof(BiTNode));
        CHECK_PTR(lNode);
        cout << "Please input left data: " << endl;
        cin >> data;
        lNode->data = data;
        lNode->lchild = NULL;
        lNode->rchild = NULL;
        rootNode->lchild = lNode;
        push(Q, rootNode->lchild);
        ++cnt;
        if (cnt < nodeNum) {
            BiTree rNode = (BiTree)malloc(sizeof(BiTNode));
            CHECK_PTR(rNode);
            cout << "Please input right data: " << endl;
            cin >> data;
            rNode->data = data;
            rNode->lchild = NULL;
            rNode->rchild = NULL;
            rootNode->rchild = rNode;
            push(Q, rootNode->rchild);
            ++cnt;
        }
    }
    destroyQueue(Q);

    return SUCCESS;
}

status printTree_preOrder_recursion(const BiTree & T)
{
    if (T) {
        cout << T->data << " ";
        if (T->lchild)
            printTree_preOrder_recursion(T->lchild);
        if (T->rchild)
            printTree_preOrder_recursion(T->rchild);
    }
    return SUCCESS;
}

status printTree_preOrder_non_recursion(const BiTree & T)
{
    //LinkQueue Q;
    //initQueue(Q);
    //push(Q, T);
    //while (!queueEmpty(Q)) {
    //    BiTree p;
    //    if (getTail(Q, p) == SUCCESS) {
    //        while (p->lchild) {
    //            push(Q, p->lchild);
    //            if (p->lchild->rchild)
    //                push(Q, p->lchild->rchild);
    //            p = p->lchild;
    //        }
    //    }
    //    p = pop(Q);
    //    cout << p->data << " ";
    //    if (p->rchild)
    //        push(Q, p->rchild);

    //}
    //destroyQueue(Q);

    SqStack S;
    initStack(S);
    push(S, T);
    while (!stackEmpty(S)) {
        BiTree p;
        pop(S, p);
        cout << p->data << " ";
        if (p->rchild)
            push(S, p->rchild);
        if (p->lchild)
            push(S, p->lchild);
     }

    destroyStack(S);
    return SUCCESS;
}

status destroyTree_postOrder_recursion(const BiTree & T)
{
    if (T->lchild)
        destroyTree_postOrder_recursion(T->lchild);
    if (T->rchild)
        destroyTree_postOrder_recursion(T->rchild);
    if (T)
        free(T);
    return SUCCESS;
}

status printTree_inOrder_recursion(const BiTree & T)
{
    if (T->lchild) {
        printTree_inOrder_recursion(T->lchild);
    }
    if (T)
        cout << T->data << " ";
    if (T->rchild)
        printTree_inOrder_recursion(T->rchild);
    return SUCCESS;
}

status printTree_inOrder_non_recursion(const BiTree & T)
{
    SqStack S;
    initStack(S);
    BiTree p = T;
    push(S, T);

    while (!stackEmpty(S)) {
        while (getTop(S, p) == SUCCESS && p) {
            push(S, p->lchild);
        }
        pop(S, p);
        if (!stackEmpty(S)) {
            pop(S, p);
            cout << p->data << " ";
            push(S, p->rchild);
        }
    }
    destroyStack(S);
    return SUCCESS;
}

status printTree_postOrder_recursion(const BiTree & T)
{
    if (T && T->lchild)
        printTree_postOrder_recursion(T->lchild);
    if (T && T->rchild)
        printTree_postOrder_recursion(T->rchild);
    if (T)
        cout << T->data << " ";
    return SUCCESS;
}

/*
  和二叉树先序遍历、中序遍历非递归算法一样，后序遍历非递归算法同样是使用栈来实现：从根结点开始,
  将所有最左结点全部压栈，每当一个结点出栈时，都先扫描该结点的右子树，只有当一个结点的左孩子和
  右孩子结点均被访问过了，才能访问结点自身。
*/
status printTree_postOrder_non_recursion(const BiTree & T)
{
    SqStack S;
    initStack(S);
    BiTree cur = T;
    BiTree visitedNode = NULL; // 标记已经被访问的节点，用于标记右边的节点被访问过
    while (cur || !stackEmpty(S)) {
        // 当前节点不为空，一直压栈，切不断往左子树深入
        while (cur) {
            push(S, cur);
            cur = cur->lchild;
        }
       
        if (!stackEmpty(S)) {
            BiTree t;
            getTop(S, t);
            /*
            *右孩子为空或被访问过则输出,而且当以下两个条件满足时才能输出当前节点，其中
            * t->right == NULL说明该节点没有右子树了，该节点需要被打印；
            * t->right == visitedNode时说明右子树已经遍历过，满足后续遍历要求。
            */
            if (t->rchild == NULL || t->rchild == visitedNode) {
            //if (t->rchild == NULL){
                cout << t->data << " ";
                pop(S, t);
                visitedNode = t; // 标记该节点被访问过
            }
            else {
                cur = t->rchild;
            }
        }
    }
    destroyStack(S);
    return SUCCESS;
}
/*
    使用队列，当出队列时候，打印结果，并将左右孩子都入队列
*/
status printTree_level_traversal(const BiTree & T)
{
    LinkQueue Q;
    BiTree t;
    initQueue(Q);
    push(Q, T);
    while (!queueEmpty(Q)) {
        t = pop(Q);
        cout << t->data << " ";
        if (t->lchild)
            push(Q, t->lchild);
        if (t->rchild)
            push(Q, t->rchild);
    }
    
    return SUCCESS;
}

/*
    T指向头结点，头结点的左链lchild指向根节点，可参见线索化算法。
    中序遍历二叉树T的非递归算法
*/
status inOderTraverse_Thr(BiThrTree T)
{
    return SUCCESS;
}
BiThrTree pre;

void InThreading(BiThrTree p) {
    if (p) {
        InThreading(p->lchild); // 左子树线索化
        if (!p->lchild) {       // 前驱线索化
            p->LTag = Thread;
            p->lchild = pre;
        }
        if (!pre->rchild) {     // 后继线索化
            pre->RTag = Thread;
            pre->rchild = p;
        }
        pre = p;                // 保持pre指针指向p的前驱
        InThreading(p->rchild); // 右子树线索化
    }
}
    status inOrderThreading(BiThrTree & Thrt, BiThrTree T)
    {
        if (!(Thrt = (BiThrTree)malloc(sizeof(BiThrTree)))) return FAIL;
        Thrt->LTag = Link;     //建立结点
        Thrt->RTag = Thread;   
        Thrt->rchild = Thrt;   //右指针回指
        if (!T)                //若二叉树空，则左指针回指
            Thrt->lchild = Thrt;
        else {
            Thrt->lchild = T;
            pre = Thrt;
            InThreading(T);
            pre->rchild = Thrt;
            pre->RTag = Thread;
            Thrt->rchild = pre;
        }
        return SUCCESS;
    }
    
    int getMinHuffmanNode(const HuffmanTree & HT, int n, const HTNode * compareTree) {
        unsigned int minWeight = 0;
        int minIdx = 0;
        for (int i = 0; i < n; ++i) {
            if (HT[i].parent == 0) {
                minIdx = i;
                minWeight = HT[i].weight;
            }
        }
        if (!compareTree) {
            for (int i = 0; i < n; ++i) {
                if ((HT[i].parent == 0) && (minWeight >= HT[i].weight)) {
                    minWeight = HT[i].weight;
                    minIdx = i;
                }
            }
        }
        else {
            for (int i = 0; i < n; ++i) {
                if ((HT[i].parent == 0) && (HT[i].weight != compareTree->weight) && (minWeight >= HT[i].weight)) {
                    minWeight = HT[i].weight;
                    minIdx = i;
                }
            }
        }
        return minIdx;
    }

    /*
        在HT[i..i-1]选择parent为0且weight 最小的两个结点， 其序号分别是s1, s2
    */
    status select(HuffmanTree & HT, int n, int & s1, int & s2) {
        s1 = getMinHuffmanNode(HT, n, NULL);
        s2 = getMinHuffmanNode(HT, n, &HT[s1]);

        return SUCCESS;
    }

    status huffmanCoding(HuffmanTree & HT, HuffmanCode & HC, int * w, int n)
    {
        if (n < 1) return FAIL;
        int m = 2 * n - 1;  //结点的总数
        HT = (HuffmanTree)malloc(sizeof(HTNode) * m);
        CHECK_PTR(HT);
        //初始化前n个结点
        for (int i = 0; i < n; ++i) {
            HT[i].lchild = 0;
            HT[i].rchild = 0;
            HT[i].parent = 0;
            HT[i].weight = w[i];
        }
        //初始化n+1到m个结点
        for (int i = n; i < m; ++i) {
            HT[i].lchild = 0;
            HT[i].rchild = 0;
            HT[i].parent = 0;
            HT[i].weight = 0;
        }

        //构造赫夫曼树,从结点集合中找到最小两个点，合并，同时标记这两个点的父节点位置，
        for (int i = n; i < m; ++i) {
            int s1 = 0, s2 = 0;
            //在HT[0..i]选择parent为0且weight 最小的两个结点， 其序号分别是s1, s2
            select(HT, i, s1, s2);
            HT[i].lchild = s1;
            HT[i].rchild = s2;
            HT[i].parent = 0;
            HT[i].weight = HT[s1].weight + HT[s2].weight;
            HT[s1].parent = i;
            HT[s2].parent = i;
        }

        // ---从叶子到根逆向求每个字符的赫夫曼编码 ---
        HC = (HuffmanCode)malloc((n + 1) * sizeof(char *)); // 分配N个字符编码的头指针向量
        char * cd = (char *)malloc(n * sizeof(char));
        cd[n - 1] = '\0';
        for (int i = 0; i < n; ++i) {
            int start = 0;
            for (int c = i, f = HT[i].parent;
                f != 0; c = f, f = HT[f].parent) {
                if (HT[f].lchild == c)
                    cd[start++] = '0';
                else
                    cd[start++] = '1';
            }
            std::cout << cd << std::endl;
            HC[i] = (char *)malloc((n + 1) * sizeof(char));
            strncpy_s(HC[i], (n + 1) * sizeof(char), &cd[start], n);
        }
        free(cd);
        return SUCCESS;
    }

    status preBuildThreading(BiThrTree T, int nodeNum)
    {
        return SUCCESS;
    }
