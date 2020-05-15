#pragma once

typedef int TElemType;
typedef int status;

#define SUCCESS 0
#define FAIL    -1;

typedef struct BiTNode {
    TElemType data;
    struct BiTNode * lchild, *rchild;
} BiTNode, *BiTree;

#define CHECK_PTR(ptr) \
    if (ptr == NULL) { \
        cout << "Allocate memory failed!!!" <<__FILE__ << ":" << __LINE__ << endl; \
        return FAIL; \
    }

/*
    �ǵݹ鴴���������� ��α�������, ���ö���
    T: ����
*/
status createBiTree_level_traversal(BiTree & T, int nodeNum);

/*
    ����ݹ����������
*/
status printTree_preOrder_recursion(const BiTree & T);

/*
    ����ǵݹ����������
*/
status printTree_preOrder_non_recursion(const BiTree & T);

/*
    ����ݹ����������, ������
*/
status destroyTree_postOrder_recursion(const BiTree & T);
/*
    ����ݹ����������
*/
status printTree_inOrder_recursion(const BiTree & T);

/*
    ����ǵݹ����������
*/
status printTree_inOrder_non_recursion(const BiTree & T);

/*
    ����ݹ����������
*/
status printTree_postOrder_recursion(const BiTree & T);

/*
    ����ǵݹ����������
*/
status printTree_postOrder_non_recursion(const BiTree & T);

/*
    ��α���������
*/
status printTree_level_traversal(const BiTree & T);

//-----�������Ķ��������洢��ʾ-----
typedef enum PointerTag {Link = 0, Thread} PointerTag; // Link == 0: ָ��, Thread == 1: ����
typedef struct BiThrNode {
    TElemType        data;
    struct BiThrNode *lchild, *rchild; // ���Һ���ָ��
    PointerTag       LTag, RTag;       // ���ұ�־
} BiThrNode, * BiThrTree;

status inOderTraverse_Thr(BiThrTree T);

status inOrderThreading(BiThrTree & Thrt, BiThrTree T);

status preBuildThreading(BiThrTree T);


// -----�շ������ͺշ�������Ĵ洢��ʾ --------
typedef struct {
    unsigned int weight;
    unsigned int parent, lchild, rchild;
}HTNode, *HuffmanTree;       //��̬��������洢�շ�����

typedef char ** HuffmanCode; //��̬��������洢�շ��������

/*
    w���n���ַ���Ȩֵ(��>0)�������շ�����HT�������
    n���ַ��ĺշ�������HC.
*/
status huffmanCoding(HuffmanTree & HT,
    HuffmanCode & HC,
    int * w,
    int n);


