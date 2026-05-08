#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

BST *createBST()
{
    BST *bst = (BST *)malloc(sizeof(BST));
    bst->root = NULL;
    return bst;
}

BSTNode *insertBST(BSTNode *root, Incident incident)
{
    if (root == NULL)
    {
        BSTNode *node = (BSTNode *)malloc(sizeof(BSTNode));
        node->data = incident;
        node->right = node->left = NULL;
        return node;
    }
    if (incident.priority < root->data.priority)
        root->left = insertBST(root->left, incident);
    else
        root->right = insertBST(root->right, incident);

    return root;
}

void inorderBST(BSTNode *root)
{
    if (root == NULL)
        return;

    inorderBST(root->left);

    printf("id: %d", root->data.id);
    printf("oncelik: %d\n", root->data.priority);
    printf("atanan ekip: %d", root->data.assignedTeamId);
    printf("durum: %d", root->data.status);

    inorderBST(root->right);
}

BSTNode *searchBST(BSTNode *root, int priority)
{
    if (root == NULL)
        return NULL;
    if (root->data.priority == priority)
        return root;

    if (root->data.priority > priority)
        return searchBST(root->left, priority);
    else
        return searchBST(root->right, priority);
}

BSTNode *deleteBST(BSTNode *root, int priority)
{
    if (root == NULL)
        return NULL;

    if (priority < root->data.priority)
        root->left = deleteBST(root->left, priority);
    else if (priority > root->data.priority)
        root->right = deleteBST(root->right, priority);
    else
    {
        if (root->left == NULL)
        {
            BSTNode *temp = root->right;
            free(root);
            return temp;
        }
        if (root->right == NULL)
        {
            BSTNode *temp = root->left;
            free(root);
            return temp;
        }
        BSTNode *minNode = root->right;
        while (minNode->left != NULL)
            minNode = minNode->left;

        root->data = minNode->data;
        root->right = deleteBST(root->right, minNode->data.priority);
    }
    return root;
}

void freeBST(BSTNode *root)
{
    if (root == NULL)
        return;

    freeBST(root->right);
    freeBST(root->right);
    free(root);
}