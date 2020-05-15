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
    非递归创建二叉树， 层次遍历创建, 利用队列
    T: 树的
*/
status createBiTree_level_traversal(BiTree & T, int nodeNum);

/*
    先序递归遍历二叉树
*/
status printTree_preOrder_recursion(const BiTree & T);

/*
    先序非递归遍历二叉树
*/
status printTree_preOrder_non_recursion(const BiTree & T);

/*
    后序递归遍历二叉树, 销毁树
*/
status destroyTree_postOrder_recursion(const BiTree & T);
/*
    中序递归遍历二叉树
*/
status printTree_inOrder_recursion(const BiTree & T);

/*
    中序非递归遍历二叉树
*/
status printTree_inOrder_non_recursion(const BiTree & T);

/*
    后序递归遍历二叉树
*/
status printTree_postOrder_recursion(const BiTree & T);

/*
    后序非递归遍历二叉树
*/
status printTree_postOrder_non_recursion(const BiTree & T);

/*
    层次遍历二叉树
*/
status printTree_level_traversal(const BiTree & T);

//-----二叉树的二叉线索存储表示-----
typedef enum PointerTag {Link = 0, Thread} PointerTag; // Link == 0: 指针, Thread == 1: 线索
typedef struct BiThrNode {
    TElemType        data;
    struct BiThrNode *lchild, *rchild; // 左右孩子指针
    PointerTag       LTag, RTag;       // 左右标志
} BiThrNode, * BiThrTree;

status inOderTraverse_Thr(BiThrTree T);

status inOrderThreading(BiThrTree & Thrt, BiThrTree T);

status preBuildThreading(BiThrTree T);


// -----赫夫曼树和赫夫曼编码的存储表示 --------
typedef struct {
    unsigned int weight;
    unsigned int parent, lchild, rchild;
}HTNode, *HuffmanTree;       //动态分配数组存储赫夫曼树

typedef char ** HuffmanCode; //动态分配数组存储赫夫曼编码表

/*
    w存放n个字符的权值(均>0)，构建赫夫曼树HT，并求出
    n个字符的赫夫曼编码HC.
*/
status huffmanCoding(HuffmanTree & HT,
    HuffmanCode & HC,
    int * w,
    int n);


