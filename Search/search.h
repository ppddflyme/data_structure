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
    ƽ����������
*/
template<typename T>
struct BSTNode {
    T       data;              // �ڵ������
    int     bf;                // �ڵ��ƽ������
    BSTNode * lchild, *rchild; // ���Һ���
};

#define LH +1 // ���
#define EH 0  // �ȸ�
#define RH -1 // �Ҹ�

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
    ��α���������
    */
    void printTree_level_traversal();

private:
    BSTNode<T> * root; // ���ĸ��ڵ�
};

/************************************************************************************/
/*
    ��������̬����
*/
/************************************************************************************/
/*
    �������������
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
    T             data;     // �����������ݲ���
    BiTreeNode<T> * lChild; // ��������������
    BiTreeNode<T> * rChild; // ��������������
};

template <typename T>
class BiTreeSearch {
public:
    inline BiTreeSearch():root(nullptr) {}
    ~BiTreeSearch();
    /*
        ���ú����������ٶ�����, �ͷ��ڴ�
    */
    void destroyBiTree(BiTreeNode<T> * rootNode);
    /*
        ����key, ���û���ҵ�, �ҵ��������insertNode
    */
    bool search(const BiTreeNode<T> * root, const BiTreeNode<T> * parentNode, BiTreeNode<T> * & insertNode, T key) const;
    /*
        ɾ��ĳ��ֵΪkey�Ľڵ�
    */
    bool deleteBST(T key);
    bool deleteBSTImpl(BiTreeNode<T> * & node, T key);
    /*
        ɾ��ĳ���ڵ�
        1. �����ɾ�ڵ�����Һ��Ӿ�Ϊ�գ�ֱ��ɾ��֮
        2. �����ɾ�ڵ������Һ���Ϊ�գ�ֱ�����亢�Ӵ���֮
        3. �����ɾ�ڵ�����Һ��Ӿ���Ϊ�գ�����ǰ��ȡ��֮��Ȼ��ɾ��ǰ��
    */
    bool del(BiTreeNode<T> * & node);
    /*
        �õ����ڵ�
    */
    inline BiTreeNode<T> * getRootNode() const { return root; }
    /*
        �����������key�ڶ�������û��, ����֮
    */
    void insert(T key);
    void traverseTree() const;
    /*
        ������������Ǹ����������
    */
    void traverseTreeImpl(BiTreeNode<T> * rootNode) const;
private:
    BiTreeNode<T> * root; // �������ĸ��ڵ�
};




/************************************************************************************/
/*
    ˳���ľ�̬����
*/
/************************************************************************************/
template <typename T>
struct IndexTable {
    T            maxVaule;    // ĳ�������������Ǹ�ֵ
    unsigned int begin_index; // ĳ�����ݵ���ʼ��ַ
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
    T             * elem;        // ����Ԫ�ش洢�ռ��ַ������ʱ��ʵ�ʳ��ȷ��䣬0�ŵ�Ԫ����
    unsigned int  length;        // ����
    IndexTable<T> * indexTable;  // ������
    bool          isIndexTable;  // ��ʶ�Ƿ�����������
    unsigned int  indexTableLen; // ��ʶ������ĳ���
};


/*
    ��ʼ��SSTable, length should be > 0;
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
˳�����(Sequential Search)�Ĳ��ҹ���Ϊ: �ӱ������һ����¼��ʼ���������
��¼�Ĺؼ��ֺ͸���ֵ�ıȽϣ���ĳ����¼�Ĺؼ��ֺ͸���ֵ�Ƚ���ȣ�����ҳɹ���
�ҵ������¼����֮����ֱ����һ����¼����ؼ��ֺ͸���ֵ�Ƚ϶�����ȣ������
����û�������¼�����Ҳ��ɹ���
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
    쳲����������Ǹ���쳲��������е��ص�Ա���зָ�ġ�
    ���迪ʼʱ���м�¼������ĳ��쳲�������С����n = Fu -1,
    Ȼ�󽫸���ֵkey��ST.elem[F(u-1)].key���бȽϣ�����ȣ�
    ����ҳɹ�����key < ST.elem[F(u-1)].key�����������
    ST.elem[1]��ST.elem[F(u-1)-1]���ӱ��н��в��ң�����
    ��������ST.elem[F(u-1)+1]��ST.elem[Fu-1]���ӱ��н���
    ���ң���һ�ӱ�ĳ���ΪF(u-2)-1.
*/
template<typename T>
inline int SSTable<T>::search_fibonacci(T key)
{
    unsigned int fibonacci_sqe[] = { 0, 1, 1, 2, 3, 5, 8, 13 };
    unsigned int low = 0, high = length - 1, mid = 0,
        fibonacci_sqe_len = ARRAY_SIZE(fibonacci_sqe),
        k = find_idx(fibonacci_sqe, fibonacci_sqe_len, length);
    // ���������
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
    if (node->rChild == nullptr) { // ������Ϊ��, ��������ȡ��֮
        q = node;
        node = node->lChild;
        delete q;
        q = nullptr;
    }
    else if (node->lChild == nullptr) { // ������Ϊ�գ���������ȡ��֮
        q = node;
        node = node->rChild;
        delete q;
        q = nullptr;
    }
    else { // ������������Ϊ�գ���ǰ��ȡ��֮��Ȼ��ɾ��ǰ��
        BiTreeNode<T> * s = node->lChild;
        q = node;
        while (s->rChild) { q = s; s = s->rChild; } // �ҵ�node��ǰ��
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

    if (!search(root, NULL, p, key)) { // ���û���ҵ�key
        s = new BiTreeNode<T>();
        CHECK_PTR(s);
        s->data = key;
        s->rChild = s->rChild = nullptr;
        if (nullptr == p) { // ���ڵ�Ϊ��
            root = s;
        }
        else {     // ����֮
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
        ������ڵ�Ϊ�գ��򴴽����ڵ㣬
        �����ø��ڵ�Ĺؼ���Ϊkey
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
            ������ڵ�Ĺؼ���Ϊkey���򲻲��룬����false
        */
        if (root->data == key) {
            taller = false;
            return false;
        }
        /*
            ������ڵ�Ĺؼ��ִ���key,�����֮������������֮��Ҫ����֮��������
            ��ʱ��Ҫ������ת����
        */
        if (root->data > key) {
            // ����������Ѿ������Ĺؼ���key������Ҫ����֮,
            //   ���ؼ���
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
        else { // ����֮��������
            // ������������Ѿ������ؼ���key�� ����Ҫ����֮��ֱ�ӷ��ؼ���
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
    // ����ָ��root��ָ�ڵ�Ϊ���Ķ���������ƽ����ת����
    // ���㷨����ʱ��rootָ���µĸ��ڵ�
    BSTNode<T> * lc = root->lchild; // lc ָ��* root�����������ڵ�
    switch (lc->bf) // ���* T ����������ƽ��ȣ�����Ӧ��ƽ�⴦��
    {
    case LH: // �½ڵ������ *root�������ӵ��������ϣ���Ҫ��������ת
        root->bf = lc->bf = EH;
        R_Rotate(root); break;
    case RH:        // �½ڵ������*root�����ӵ���������Ҫ��˫��ת����
    {
        BSTNode<T> * rd = lc->rchild; // rdָ��*root�����ӵ���������
        switch (rd->bf) //�޸�*root���������ӵ�ƽ������
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
    // ���� *root Ϊ���Ķ�����������������������֮��Pָ��
    // �µ������ڵ㣬����ת����֮ǰ���������ĸ��ڵ�
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
    // ����ָ��root��ָ�ڵ�Ϊ���Ķ���������ƽ����ת����
    // ���㷨����ʱ��rootָ���µĸ��ڵ�
    BSTNode<T> * rc = root->rchild; // rc ָ��* root�����������ڵ�
    switch (rc->bf) // ���* T ����������ƽ��ȣ�����Ӧ��ƽ�⴦��
    {
    case RH: // �½ڵ������ *root���Һ��ӵ��������ϣ���Ҫ��������ת
        root->bf = rc->bf = EH;
        L_Rotate(root); break;
    case LH:        // �½ڵ������*root���Һ��ӵ���������Ҫ��˫��ת����
    {
        BSTNode<T> * rd = rc->rchild; // rdָ��*root�����ӵ���������
        switch (rd->bf) //�޸�*root���������ӵ�ƽ������
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
