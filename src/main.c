#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "region_tree.h"

int main()
{

    TreeNode *root = createTreeNode(0, "Isparta");
    TreeNode *merkez = createTreeNode(1, "Merkez");
    TreeNode *egirdir = createTreeNode(2, "Egirdir");
    TreeNode *bahcelievler = createTreeNode(3, "Bahcelievler");
    TreeNode *guneykent = createTreeNode(4, "Guneykent");
    TreeNode *yazla = createTreeNode(5, "Yazla");

    addChild(root, merkez);
    addChild(root, egirdir);
    addChild(merkez, bahcelievler);
    addChild(merkez, guneykent);
    addChild(egirdir, yazla);

    printTree(root, 0);

    return 0;
}