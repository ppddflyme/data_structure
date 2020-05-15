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
  �Ͷ����������������������ǵݹ��㷨һ������������ǵݹ��㷨ͬ����ʹ��ջ��ʵ�֣��Ӹ���㿪ʼ,
  ������������ȫ��ѹջ��ÿ��һ������ջʱ������ɨ��ý�����������ֻ�е�һ���������Ӻ�
  �Һ��ӽ��������ʹ��ˣ����ܷ��ʽ������
*/
status printTree_postOrder_non_recursion(const BiTree & T)
{
    SqStack S;
    initStack(S);
    BiTree cur = T;
    BiTree visitedNode = NULL; // ����Ѿ������ʵĽڵ㣬���ڱ���ұߵĽڵ㱻���ʹ�
    while (cur || !stackEmpty(S)) {
        // ��ǰ�ڵ㲻Ϊ�գ�һֱѹջ���в���������������
        while (cur) {
            push(S, cur);
            cur = cur->lchild;
        }
       
        if (!stackEmpty(S)) {
            BiTree t;
            getTop(S, t);
            /*
            *�Һ���Ϊ�ջ򱻷��ʹ������,���ҵ�����������������ʱ���������ǰ�ڵ㣬����
            * t->right == NULL˵���ýڵ�û���������ˣ��ýڵ���Ҫ����ӡ��
            * t->right == visitedNodeʱ˵���������Ѿ��������������������Ҫ��
            */
            if (t->rchild == NULL || t->rchild == visitedNode) {
            //if (t->rchild == NULL){
                cout << t->data << " ";
                pop(S, t);
                visitedNode = t; // ��Ǹýڵ㱻���ʹ�
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
    ʹ�ö��У���������ʱ�򣬴�ӡ������������Һ��Ӷ������
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
    Tָ��ͷ��㣬ͷ��������lchildָ����ڵ㣬�ɲμ��������㷨��
    �������������T�ķǵݹ��㷨
*/
status inOderTraverse_Thr(BiThrTree T)
{
    return SUCCESS;
}
BiThrTree pre;

void InThreading(BiThrTree p) {
    if (p) {
        InThreading(p->lchild); // ������������
        if (!p->lchild) {       // ǰ��������
            p->LTag = Thread;
            p->lchild = pre;
        }
        if (!pre->rchild) {     // ���������
            pre->RTag = Thread;
            pre->rchild = p;
        }
        pre = p;                // ����preָ��ָ��p��ǰ��
        InThreading(p->rchild); // ������������
    }
}
    status inOrderThreading(BiThrTree & Thrt, BiThrTree T)
    {
        if (!(Thrt = (BiThrTree)malloc(sizeof(BiThrTree)))) return FAIL;
        Thrt->LTag = Link;     //�������
        Thrt->RTag = Thread;   
        Thrt->rchild = Thrt;   //��ָ���ָ
        if (!T)                //���������գ�����ָ���ָ
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
        ��HT[i..i-1]ѡ��parentΪ0��weight ��С��������㣬 ����ŷֱ���s1, s2
    */
    status select(HuffmanTree & HT, int n, int & s1, int & s2) {
        s1 = getMinHuffmanNode(HT, n, NULL);
        s2 = getMinHuffmanNode(HT, n, &HT[s1]);

        return SUCCESS;
    }

    status huffmanCoding(HuffmanTree & HT, HuffmanCode & HC, int * w, int n)
    {
        if (n < 1) return FAIL;
        int m = 2 * n - 1;  //��������
        HT = (HuffmanTree)malloc(sizeof(HTNode) * m);
        CHECK_PTR(HT);
        //��ʼ��ǰn�����
        for (int i = 0; i < n; ++i) {
            HT[i].lchild = 0;
            HT[i].rchild = 0;
            HT[i].parent = 0;
            HT[i].weight = w[i];
        }
        //��ʼ��n+1��m�����
        for (int i = n; i < m; ++i) {
            HT[i].lchild = 0;
            HT[i].rchild = 0;
            HT[i].parent = 0;
            HT[i].weight = 0;
        }

        //����շ�����,�ӽ�㼯�����ҵ���С�����㣬�ϲ���ͬʱ�����������ĸ��ڵ�λ�ã�
        for (int i = n; i < m; ++i) {
            int s1 = 0, s2 = 0;
            //��HT[0..i]ѡ��parentΪ0��weight ��С��������㣬 ����ŷֱ���s1, s2
            select(HT, i, s1, s2);
            HT[i].lchild = s1;
            HT[i].rchild = s2;
            HT[i].parent = 0;
            HT[i].weight = HT[s1].weight + HT[s2].weight;
            HT[s1].parent = i;
            HT[s2].parent = i;
        }

        // ---��Ҷ�ӵ���������ÿ���ַ��ĺշ������� ---
        HC = (HuffmanCode)malloc((n + 1) * sizeof(char *)); // ����N���ַ������ͷָ������
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
