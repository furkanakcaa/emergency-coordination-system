#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "region_tree.h"

TreeNode *createTreeNode(int id, char *name)
{
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->id = id;
    strcpy(node->name, name);
    node->firstChild = NULL;
    node->nextSibling = NULL;

    return node;
}

void addChild(TreeNode *parent, TreeNode *child)
{
    if (parent->firstChild == NULL)
        parent->firstChild = child;

    else
    {
        TreeNode *last = parent->firstChild;
        while (last->nextSibling != NULL)
            last = last->nextSibling;
        last->nextSibling = child;
    }
}

void printTree(TreeNode *node, int depth)
{
    if (node == NULL)
        return;

    for (int i = 0; i < depth; i++)
        printf("  ");
    printf("%d - %s\n", node->id, node->name);
    printTree(node->firstChild, depth + 1);
    printTree(node->nextSibling, depth);
}

TreeNode *searchTree(TreeNode *node, int id)
{
    if (node == NULL)
        return NULL;
    if (node->id == id)
        return node;
    TreeNode *found = searchTree(node->firstChild, id);
    if (found != NULL)
        return found;
    return searchTree(node->nextSibling, id);
}

void freeTree(TreeNode *node)
{
    if (node == NULL)
        return;
    freeTree(node->firstChild);
    freeTree(node->nextSibling);
    free(node);
}