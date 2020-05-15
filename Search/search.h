#pragma once
#include <iostream>
using std::cout;
using std::endl;

#define SUCCESS 0
#define FAIL    -1;

#define IDX_LENGTH 4

#define ARRAY_SIZE(array) \
    sizeof((array))/sizeof((array)[0])

#define CHECK_PTR(ptr) \
    if (ptr == nullptr) {\
        cout << "ptr is nullptr" <<__FILE__ << ": " << __LINE__ << ": " << __FUNCTION__ << endl; \
        exit(EXIT_FAILURE); \
    }

typedef int status;
//typedef BiTree QElemType;

template<typename T>
struct QNode {
    T            data;
    QNode<T> * next;
};
//
//typedef struct QNode {
//    QElemType    data;
//    struct QNode * next;
//} QNode, *QueuePtr;


//typedef struct {
//    QueuePtr  front;
//    QueuePtr  rear;
//} LinkQueue;

template<typename T>
struct LinkQueue {
    QNode<T>*  front;
    QNode<T>*  rear;
};

/*
create queue
*/
template <typename T>
status initQueue(LinkQueue<T> & Q) {
    Q.front = Q.rear = (QNode<T>*)malloc(sizeof(QNode<T>));
    CHECK_PTR(Q.front);
    Q.front->next = NULL;

    return SUCCESS;
}

/*
destroy queue
*/
template <typename T>
status destroyQueue(LinkQueue<T> & Q) {
    while (Q.front) {
        Q.rear = Q.front->next;
        free(Q.front);
        Q.front = Q.rear;
    }
    return SUCCESS;
}

/*
insert data
*/
template <typename T>
status push(LinkQueue<T> & Q, T bNode) {
    QNode<T> * tempQNode = (QNode<T>*)malloc(sizeof(QNode<T>));
    CHECK_PTR(tempQNode);
    tempQNode->data = bNode;
    tempQNode->next = NULL;
    Q.rear->next = tempQNode;
    Q.rear = tempQNode;
    return SUCCESS;
}

template <typename T>
T pop(LinkQueue<T> & Q) {
    if (queueEmpty<T>(Q)) {
        cout << "The queue is empty..." << endl;
        //return SUCCESS;
    }

    QNode<T> * tempQNode = Q.front->next;
    Q.front->next = tempQNode->next;
    if (Q.rear == tempQNode) {
        Q.rear = Q.front;
    }
    T tempData = tempQNode->data;
    free(tempQNode);

    return tempData;
}
template <typename T>
bool queueEmpty(const LinkQueue<T> & Q) {
    return Q.front == Q.rear;
}

//get tail element
template <typename T>
status getTail(const LinkQueue<T> & Q, T & e) {
    if (!queueEmpty<T>(Q)) {
        e = Q.rear->data;
    }
    return SUCCESS;
}


/*
    平衡二叉查找树
*/
template<typename T>
struct BSTNode {
    T       data;              // 节点的数据
    int     bf;                // 节点的平衡因子
    BSTNode * lchild, *rchild; // 左右孩子
};

#define LH +1 // 左高
#define EH 0  // 等高
#define RH -1 // 右高

template<typename T>
class BSTSearch {
public:
    inline BSTSearch() : root(nullptr) {}
    inline ~ BSTSearch() { destroyBST(root); }
    bool insertAVL(T e);
    bool insertAVLImpl(BSTNode<T> * & root, T key, bool & taller);
    void destroyBST(BSTNode<T> * root);
    void leftBalance(BSTNode<T> * & root);
    void R_Rotate(BSTNode<T> * & root);
    void L_Rotate(BSTNode<T> * & root);
    void rightBalance(BSTNode<T> * & root);
    void traverseBST();
    void traverseBSTImpl(BSTNode<T> * root);
    /*
    层次遍历二叉树
    */
    void printTree_level_traversal();

private:
    BSTNode<T> * root; // 树的根节点
};

/************************************************************************************/
/*
    二叉树动态查找
*/
/************************************************************************************/
/*
    创建二叉树结点
*/
template <typename T>
struct BiTreeNode {
    BiTreeNode() : data(0), lChild(nullptr), rChild(nullptr) {}
    BiTreeNode& operator = (const BiTreeNode & that) {
        this->data = that.data;
        this->rChild = that.lChild;
        this->lChild = that.lChild;
        return &this;
    }
    T             data;     // 二叉树的数据部分
    BiTreeNode<T> * lChild; // 二叉树的左子树
    BiTreeNode<T> * rChild; // 二叉树的右子树
};

template <typename T>
class BiTreeSearch {
public:
    inline BiTreeSearch():root(nullptr) {}
    ~BiTreeSearch();
    /*
        利用后续遍历销毁二叉树, 释放内存
    */
    void destroyBiTree(BiTreeNode<T> * rootNode);
    /*
        查找key, 如果没有找到, 找到带插入点insertNode
    */
    bool search(const BiTreeNode<T> * root, const BiTreeNode<T> * parentNode, BiTreeNode<T> * & insertNode, T key) const;
    /*
        删除某个值为key的节点
    */
    bool deleteBST(T key);
    bool deleteBSTImpl(BiTreeNode<T> * & node, T key);
    /*
        删除某个节点
        1. 如果待删节点的左右孩子均为空，直接删除之
        2. 如果待删节点的左或右孩子为空，直接用其孩子代替之
        3. 如果待删节点的左右孩子均不为空，用其前驱取代之，然后删除前驱
    */
    bool del(BiTreeNode<T> * & node);
    /*
        得到根节点
    */
    inline BiTreeNode<T> * getRootNode() const { return root; }
    /*
        如果待搜索的key在二叉树中没有, 插入之
    */
    void insert(T key);
    void traverseTree() const;
    /*
        中序遍历树，是个有序的数列
    */
    void traverseTreeImpl(BiTreeNode<T> * rootNode) const;
private:
    BiTreeNode<T> * root; // 二叉树的根节点
};




/************************************************************************************/
/*
    顺序表的静态查找
*/
/************************************************************************************/
template <typename T>
struct IndexTable {
    T            maxVaule;    // 某段数据中最大的那个值
    unsigned int begin_index; // 某段数据的起始地址
};

template <typename T>
class SSTable {
public:
    SSTable(unsigned int length, T* srcArray, bool isIndexTable = false);
    ~SSTable();
    int search_seq(T key);
    int search_binary(T key);
    int search_fibonacci(T key);
    int search_insert(T key);
    int search_index_seq_table(T key);
    void construct_index_table();
    T * getElem() const {
        return elem;
    }
private:
    T             * elem;        // 数据元素存储空间基址，建表时按实际长度分配，0号单元留空
    unsigned int  length;        // 表长度
    IndexTable<T> * indexTable;  // 索引表
    bool          isIndexTable;  // 标识是否构造了索引表
    unsigned int  indexTableLen; // 标识索引表的长度
};


/*
    初始化SSTable, length should be > 0;
*/
template<typename T>
inline SSTable<T>::SSTable(unsigned int length, T* srcArray, bool isIndexTable):
                              elem(nullptr), length(length), isIndexTable(isIndexTable), indexTableLen((length+IDX_LENGTH-1)/IDX_LENGTH)
{
    CHECK_PTR(srcArray);
    elem = new T[length*2];
    CHECK_PTR(elem);
    memmove(elem, srcArray, length * sizeof(T));
    if (isIndexTable)
        construct_index_table();
}

template<typename T>
inline SSTable<T>::~SSTable()
{
    delete[] elem;
    if (isIndexTable)
        delete [] indexTable;
}

/*
顺序查找(Sequential Search)的查找过程为: 从表中最后一个记录开始，逐个进行
记录的关键字和给定值的比较，若某个记录的关键字和给定值比较相等，则查找成功，
找到所查记录；反之，若直至第一个记录，其关键字和给定值比较都不相等，则表明
表中没有所查记录，查找不成功。
*/
template<typename T>
inline int SSTable<T>::search_seq(T key)
{
    unsigned int i = 0;
    for (i = length - 1; elem[i] != key; --i);
    return i;
}

template<typename T>
inline int SSTable<T>::search_binary(T key)
{
    unsigned int low = 0, heigh = length - 1, mid = 0;
    while (low <= heigh) {
        mid = (heigh + low) / 2;
        if (elem[mid] == key)
            return mid;
        else if (elem[mid] > key)
            heigh = mid - 1;
        else
            low = mid + 1;
    }
    return -1;
}

//template<typename T>
//unsigned int find_idx(T * fibonacci_sqe, unsigned int fibonacci_sqe_len, T key)
//{
//    unsigned int idx = 0;
//    for (unsigned int i = 0; i < fibonacci_sqe_len; ++i) {
//        idx = i;
//        if (fibonacci_sqe[idx] >= key)
//            break;
//    }
//    if (idx == 0)
//        return fibonacci_sqe[0];
//    else
//        return fibonacci_sqe[--idx];
//}
template<typename T>
unsigned int find_idx(T * fibonacci_sqe, unsigned int fibonacci_sqe_len, T key)
{
    unsigned int idx = 0;
    for (unsigned int i = 0; i < fibonacci_sqe_len; ++i) {
        idx = i;
        if (fibonacci_sqe[idx] >= key)
            break;
    }
    return idx;
}

/*
    斐波那契查找是根据斐波那契序列的特点对表进行分割的。
    假设开始时表中记录个数比某个斐波那契数小，即n = Fu -1,
    然后将给定值key和ST.elem[F(u-1)].key进行比较，若相等，
    则查找成功；若key < ST.elem[F(u-1)].key，则继续在自
    ST.elem[1]至ST.elem[F(u-1)-1]的子表中进行查找，否则
    继续在自ST.elem[F(u-1)+1]至ST.elem[Fu-1]的子表中进行
    查找，后一子表的长度为F(u-2)-1.
*/
template<typename T>
inline int SSTable<T>::search_fibonacci(T key)
{
    unsigned int fibonacci_sqe[] = { 0, 1, 1, 2, 3, 5, 8, 13 };
    unsigned int low = 0, high = length - 1, mid = 0,
        fibonacci_sqe_len = ARRAY_SIZE(fibonacci_sqe),
        k = find_idx(fibonacci_sqe, fibonacci_sqe_len, length);
    // 补齐有序表
    for (unsigned int i = length; i < fibonacci_sqe[k]; i++)
    {
        elem[i] = elem[high];
    }

    while (low <= high) {
        mid = low + fibonacci_sqe[k - 1] - 1;
        cout << "low: " << low << " , high: " << high << " , mid: " << mid << endl;
        if (elem[mid] == key) {
            if (mid < length)
                return mid;
            else
                return length - 1;
        }
        else if (elem[mid] > key) {
            high = mid - 1;
            k = k - 1;
        }
        else {
            low = mid + 1;
            k = k - 2;
        }
    }
    return -1;
}
template<typename T>
inline int SSTable<T>::search_insert(T key)
{
    unsigned int low = 0, hight = length - 1, i = 0;
    while (low <= hight) {
        i = low + ((key - elem[low])*(hight - low)) / (elem[hight] - elem[low]);
        if (elem[i] == key)
            return i;
        else if (elem[i] > key)
            hight = i - 1;
        else
            low = i + 1;
    }
    return -1;
}
template<typename T>
inline int SSTable<T>::search_index_seq_table(T key)
{
    for (unsigned int i = 0; i < indexTableLen; ++i) {
        if (indexTable[i].maxVaule >= key) {
            if (i < indexTableLen - 1) {
                for (unsigned int j = indexTable[i].begin_index; j < indexTable[i + 1].begin_index; ++j) {
                    if (elem[j] == key)
                        return j;
                }
            }
            else {
                for (unsigned int j = indexTable[i].begin_index; j < length; ++j) {
                    if (elem[j] == key)
                        return j;
                }
            }
            break;
        }
    }
    return -1;
}
template<typename T>
inline void SSTable<T>::construct_index_table()
{
    indexTable = new IndexTable<T>[indexTableLen];
    CHECK_PTR(indexTable);
    for (unsigned int i = 0; i < indexTableLen; ++i) {
        indexTable[i].begin_index = i * IDX_LENGTH;
        indexTable[i].maxVaule = 0;
        for (unsigned int j = i * IDX_LENGTH; j < length && j < (i + 1) * IDX_LENGTH; ++j) {
            if (indexTable[i].maxVaule < elem[j])
                indexTable[i].maxVaule = elem[j];
        }
    }
}
//template<typename T>
//inline unsigned int SSTable<T>::search_fibonacci(T key)
//{
//    unsigned int fibonacci_sqe[] = { 0, 1, 1, 2, 3, 5, 8, 13 };
//    unsigned int low = 0, high = length - 1, mid = 0, length = 0,
//        fibonacci_sqe_len = ARRAY_SIZE(fibonacci_sqe);
//    while (low <= high) {
//        length = high - low;
//        mid = find_idx(fibonacci_sqe, fibonacci_sqe_len, length);
//        if (elem[low + mid] == key)
//            return low+mid;
//        else if (elem[low + mid] > key)
//            high = mid - 1;
//        else
//            low = mid + 1;
//    }
//    return 0;
//}
template<typename T>
inline BiTreeSearch<T>::~BiTreeSearch()
{
    destroyBiTree(root);
}

template<typename T>
inline void BiTreeSearch<T>::destroyBiTree(BiTreeNode<T> * rootNode)
{
    if (rootNode->lChild)
        destroyBiTree(rootNode->lChild);
    if (rootNode->rChild)
        destroyBiTree(rootNode->rChild);
    if (rootNode)
        delete rootNode;
}

template<typename T>
inline bool BiTreeSearch<T>::search(const BiTreeNode<T>* root, const BiTreeNode<T>* parentNode, BiTreeNode<T>* & insertNode, T key) const
{
    if (!root) {
        insertNode = const_cast<BiTreeNode<T>*>(parentNode);
        return false;
    }
    else if (root->data == key)
        return true;
    else if (root->data > key)
        search(root->lChild, root, insertNode, key);
    else
        search(root->rChild, root, insertNode, key);
    return false;
}

template<typename T>
inline bool BiTreeSearch<T>::deleteBST(T key)
{
    return deleteBSTImpl(root, key);
}

template<typename T>
inline bool BiTreeSearch<T>::deleteBSTImpl(BiTreeNode<T>* & node, T key)
{
    if (node == nullptr)
        return false;
    else {
        if (node->data == key) {
            return del(node);
        }
        else if (node->data > key)
            deleteBSTImpl(node->lChild, key);
        else
            deleteBSTImpl(node->rChild, key);
    }
    return true;
}

template<typename T>
inline bool BiTreeSearch<T>::del(BiTreeNode<T>* & node)
{
    BiTreeNode<T> * q = nullptr;
    if (node->rChild == nullptr) { // 右子树为空, 用左子树取代之
        q = node;
        node = node->lChild;
        delete q;
        q = nullptr;
    }
    else if (node->lChild == nullptr) { // 左子树为空，用右子树取代之
        q = node;
        node = node->rChild;
        delete q;
        q = nullptr;
    }
    else { // 左右子树都不为空，用前驱取代之，然后删除前驱
        BiTreeNode<T> * s = node->lChild;
        q = node;
        while (s->rChild) { q = s; s = s->rChild; } // 找到node的前驱
        node->data = s->data;
        if (q != node)
            node->rChild = s->lChild;
        else
            node->lChild = s->lChild;
        delete s;
    }
    return true;

}

template<typename T>
inline void BiTreeSearch<T>::insert(T key)
{
    BiTreeNode<T> * p = nullptr, * s = nullptr;

    if (!search(root, NULL, p, key)) { // 如果没有找到key
        s = new BiTreeNode<T>();
        CHECK_PTR(s);
        s->data = key;
        s->rChild = s->rChild = nullptr;
        if (nullptr == p) { // 根节点为空
            root = s;
        }
        else {     // 插入之
            if (p->data > key)
                p->lChild = s;
            else
                p->rChild = s;
        }
    }
}

template<typename T>
inline void BiTreeSearch<T>::traverseTree() const
{
    traverseTreeImpl(root);
}

template<typename T>
inline void BiTreeSearch<T>::traverseTreeImpl(BiTreeNode<T> * rootNode) const
{
    if (rootNode->lChild)
        traverseTreeImpl(rootNode->lChild);
    if (rootNode)
        cout << rootNode->data << " ";
    if (rootNode->rChild)
        traverseTreeImpl(rootNode->rChild);
}

template<typename T>
inline bool BSTSearch<T>::insertAVL(T e)
{
    bool taller = false;
    return insertAVLImpl(root, e, taller);
}

template<typename T>
inline bool BSTSearch<T>::insertAVLImpl(BSTNode<T> * & root, T key, bool & taller)
{
    /*
        如果根节点为空，则创建根节点，
        并且置根节点的关键字为key
    */
    if (nullptr == root) {
        root = new BSTNode<T>();
        CHECK_PTR(root);
        root->data = key;
        root->lchild = root->rchild = nullptr;
        root->bf = EH;
        taller = true;
       // return true;
    }
    else {
        /*
            如果根节点的关键字为key，则不插入，返回false
        */
        if (root->data == key) {
            taller = false;
            return false;
        }
        /*
            如果根节点的关键字大于key,则插入之于左子树，反之需要插入之于右子树
            这时需要考虑旋转问题
        */
        if (root->data > key) {
            // 如果左子树已经包含改关键字key，则不需要插入之,
            //   返回即可
            if (!insertAVLImpl(root->lchild, key, taller))
                return false;
            if (taller) {
                switch (root->bf)
                {
                case LH:
                    leftBalance(root);
                    taller = false;
                    break;
                case EH:
                    root->bf = LH;
                    taller = true;
                    break;
                case RH:
                    root->bf = EH;
                    taller = false;
                    break;
                default:
                    break;
                }
            }
        }
        else { // 插入之于右子树
            // 如果右子树中已经包含关键字key， 则不需要插入之，直接返回即可
            if (!insertAVLImpl(root->rchild, key, taller))
                return false;
            if (taller) {
                switch (root->bf)
                {
                case LH:
                    root->bf = EH;
                    taller = false;
                    break;
                case EH:
                    root->bf = RH;
                    taller = true;
                    break;
                case RH:
                    rightBalance(root);
                    taller = false;
                    break;
                default:
                    break;
                }
            }

        }
    }

    return true;
}

template<typename T>
inline void BSTSearch<T>::destroyBST(BSTNode<T> * root)
{
    if (root->lchild)
        destroyBST(root->lchild);
    if (root->rchild)
        destroyBST(root->rchild);
    if (root)
        delete root;
}

template<typename T>
inline void BSTSearch<T>::leftBalance(BSTNode<T> * & root)
{
    // 对以指针root所指节点为根的二叉树作左平衡旋转处理
    // 本算法结束时，root指向新的根节点
    BSTNode<T> * lc = root->lchild; // lc 指向* root的左子树根节点
    switch (lc->bf) // 检查* T 的左子树的平衡度，做相应的平衡处理
    {
    case LH: // 新节点插入在 *root的做孩子的左子树上，需要做单右旋转
        root->bf = lc->bf = EH;
        R_Rotate(root); break;
    case RH:        // 新节点插入在*root的左孩子的右子树，要做双旋转处理
    {
        BSTNode<T> * rd = lc->rchild; // rd指向*root的左孩子的右子树根
        switch (rd->bf) //修改*root及其作孩子的平衡因子
        {
        case LH:
            root->bf = RH;
            lc->bf = EH;
            break;
        case EH:
            root->bf = lc->bf = EH;
            break;
        case RH:
            root->bf = EH;
            lc->bf = LH;
            break;
        default:
            break;
        }
        rd->bf = EH;
        L_Rotate(root->lchild);
        R_Rotate(root);
        break;
    }
    default:
        break;
    }
}

template<typename T>
inline void BSTSearch<T>::R_Rotate(BSTNode<T>*& root)
{
    // 对以 *root 为根的二叉排序树做右旋处理，处理之后P指向
    // 新的树根节点，即旋转处理之前的左子树的根节点
    BSTNode<T> * lc = root->lchild;
    root->lchild = lc->rchild;
    lc->rchild = root;
    root = lc;
}

template<typename T>
inline void BSTSearch<T>::L_Rotate(BSTNode<T>*& root)
{
    BSTNode<T> * rc = root->rchild;
    root->rchild = rc->lchild;
    rc->lchild = root;
    root = rc;
}

template<typename T>
inline void BSTSearch<T>::rightBalance(BSTNode<T> * & root)
{
    // 对以指针root所指节点为根的二叉树作右平衡旋转处理
    // 本算法结束时，root指向新的根节点
    BSTNode<T> * rc = root->rchild; // rc 指向* root的右子树根节点
    switch (rc->bf) // 检查* T 的右子树的平衡度，做相应的平衡处理
    {
    case RH: // 新节点插入在 *root的右孩子的右子树上，需要做单左旋转
        root->bf = rc->bf = EH;
        L_Rotate(root); break;
    case LH:        // 新节点插入在*root的右孩子的左子树，要做双旋转处理
    {
        BSTNode<T> * rd = rc->rchild; // rd指向*root的左孩子的右子树根
        switch (rd->bf) //修改*root及其作孩子的平衡因子
        {
        case LH:
            root->bf = RH;
            rc->bf = EH;
            break;
        case EH:
            root->bf = rc->bf = EH;
            break;
        case RH:
            root->bf = EH;
            rc->bf = LH;
            break;
        default:
            break;
        }
        rd->bf = EH;
        R_Rotate(root->rchild);
        L_Rotate(root);
        break;
    }
    default:
        break;
    }
}

template<typename T>
inline void BSTSearch<T>::traverseBST()
{
    traverseBSTImpl(root);
}

template<typename T>
inline void BSTSearch<T>::traverseBSTImpl(BSTNode<T>* root)
{
    if (root->lchild)
        traverseBSTImpl(root->lchild);
    if (root)
        cout << root->data << " ";
    if (root->rchild)
        traverseBSTImpl(root->rchild);
}

template<typename T>
inline void BSTSearch<T>::printTree_level_traversal()
{
    LinkQueue<BSTNode<T>> Q;
    BSTNode<T> t;
    initQueue<BSTNode<T>>(Q);
    push<BSTNode<T>>(Q, *root);
    while (!queueEmpty<BSTNode<T>>(Q)) {
        t = pop<BSTNode<T>>(Q);
        cout << t.data << " ";
        if (t.lchild)
            push<BSTNode<T>>(Q, *t.lchild);
        if (t.rchild)
            push<BSTNode<T>>(Q, *t.rchild);
    }
}
