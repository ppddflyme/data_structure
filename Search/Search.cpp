// Search.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "search.h"


int main()
{
    unsigned int srcArray[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    SSTable<unsigned int> STable(ARRAY_SIZE(srcArray), srcArray);
    int idx = STable.search_seq(4);
    cout << "idx = " << idx << endl;
    cout << "search_binary..." << endl;
    idx = STable.search_binary(4);
    cout << "idx = " << idx << endl;
    cout << "search_fibonacci..." << endl;
    idx = STable.search_fibonacci(6);
    cout << "idx = " << idx << endl;
    cout << "search_insert..." << endl;
    idx = STable.search_insert(6);
    cout << "idx = " << idx << endl;
    cout << "search_index_seq_table..." << endl;
    SSTable<unsigned int> STable2(ARRAY_SIZE(srcArray), srcArray, true);
    idx = STable2.search_index_seq_table(11);
    cout << "idx = " << idx << endl;
    BiTreeSearch<int> biTreeSearch;
    for (int i = 1; i < 11; ++i)
        biTreeSearch.insert(i);
    biTreeSearch.traverseTree();
    cout << "deleteBST..." << endl;
    biTreeSearch.deleteBST(1);
    biTreeSearch.traverseTree();
    cout << endl;
    cout << "BSTSearch..." << endl;
    BSTSearch<int> bstSearch;
    for (int i = 1; i < 11; ++i)
        bstSearch.insertAVL(i);
    bstSearch.traverseBST();
    cout << endl;
    cout << "printTree_level_traversal..." << endl;
    bstSearch.printTree_level_traversal();
    cout << endl;

    return 0;
}

