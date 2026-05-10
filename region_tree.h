typedef struct TreeNode
{
    int id;
    char name[50];
    struct TreeNode *firstChild;
    struct TreeNode *nextSibling;
} TreeNode;

typedef struct Tree
{
    TreeNode *root;
} Tree;

TreeNode *createTreeNode(int id, char *name);
void addChild(TreeNode *parent, TreeNode *child);
void printTree(TreeNode *node, int depth);
TreeNode *searchTree(TreeNode *node, int id);
void freeTree(TreeNode *node);