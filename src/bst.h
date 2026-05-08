#include "incident.h"

typedef struct BSTNode
{
    Incident data;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

typedef struct BST
{
    BSTNode *root;
} BST;

BST *createBST();
BSTNode *insertBST(BSTNode *root, Incident incident);
BSTNode *searchBST(BSTNode *root, int priority);
void inorderBST(BSTNode *root);
BSTNode *deleteBST(BSTNode *root, int priority);
void freeBST(BSTNode *root);