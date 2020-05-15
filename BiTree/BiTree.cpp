// BiTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "tree_data_structure.h"


int main()
{
    BiTree root;
    createBiTree_level_traversal(root, 3);
    std::cout << std::endl;
    std::cout << "printTree_level_traversal..." << std::endl;
    printTree_level_traversal(root);
    std::cout << std::endl;
    std::cout << "printTree_preOrder_recursion..." << std::endl;
    printTree_preOrder_recursion(root);
    std::cout << std::endl;
    std::cout << "printTree_inOrder_recursion..." << std::endl;
    printTree_inOrder_recursion(root);
    std::cout << std::endl;
    std::cout << "printTree_postOrder_recursion..." << std::endl;
    printTree_postOrder_recursion(root);
    std::cout << std::endl;
    std::cout << "printTree_inOrder_non_recursion..." << std::endl;
    printTree_inOrder_non_recursion(root);
    std::cout << std::endl;
    std::cout << "printTree_preOrder_non_recursion..." << std::endl;
    printTree_preOrder_non_recursion(root);
    std::cout << std::endl;
    std::cout << "printTree_postOrder_non_recursion..." << std::endl;
    printTree_postOrder_non_recursion(root);
    std::cout << std::endl;
    destroyTree_postOrder_recursion(root);
    std::cout << std::endl;
    std::cout << "huffmanCoding..." << std::endl;
    HuffmanTree HT;
    HuffmanCode HC;
    int w[] = {7, 5, 2, 4};
    huffmanCoding(HT, HC, w, sizeof(w) / sizeof(w[0]));
    free(HT);
    free(HC);
    return 0;
}

