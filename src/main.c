#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "incident.h"
#include "resource.h"
#include "stack.h"
#include "hash_table.h"
#include "bst.h"
#include "region_tree.h"
#include "menu.h"

int main()
{
    // Graf
    Graph *g = createGraph(10);
    addRegion(g, 0, "Merkez");
    addRegion(g, 1, "Kuzey");
    addRegion(g, 2, "Guney");
    addRegion(g, 3, "Dogu");
    addRegion(g, 4, "Bati");
    addRegion(g, 5, "Liman");
    addRoad(g, 0, 1, 5);
    addRoad(g, 0, 2, 3);
    addRoad(g, 1, 3, 8);
    addRoad(g, 2, 4, 6);
    addRoad(g, 3, 4, 2);
    addRoad(g, 4, 5, 7);
    addRoad(g, 1, 5, 10);

    // Priority Queue — olaylar
    PriorityQueue *pq = createPQ(100);
    BST *bst = createBST();
    HashTable *ht = createHashTable();

    Incident inc1 = {1, 2, time(NULL), FIRE, WAITING, 0, -1};
    Incident inc2 = {2, 1, time(NULL), MEDICAL, WAITING, 3, -1};
    Incident inc3 = {3, 3, time(NULL), RESCUE, WAITING, 2, -1};
    Incident inc4 = {4, 1, time(NULL), FIRE, WAITING, 1, -1};
    Incident inc5 = {5, 2, time(NULL), MEDICAL, WAITING, 4, -1};

    insertPQ(pq, inc1);
    insertPQ(pq, inc2);
    insertPQ(pq, inc3);
    insertPQ(pq, inc4);
    insertPQ(pq, inc5);

    insertRecord(ht, inc1);
    insertRecord(ht, inc2);
    insertRecord(ht, inc3);
    insertRecord(ht, inc4);
    insertRecord(ht, inc5);

    bst->root = insertBST(bst->root, inc1);
    bst->root = insertBST(bst->root, inc2);
    bst->root = insertBST(bst->root, inc3);
    bst->root = insertBST(bst->root, inc4);
    bst->root = insertBST(bst->root, inc5);

    // Ekipler
    ResourceList *list = createList();
    Resource r1 = {1, "Alfa Ekibi", ITFAIYE, 0, 0};
    Resource r2 = {2, "Beta Ekibi", AMBULANS, 0, 3};
    Resource r3 = {3, "Gama Ekibi", KURTARMA, 0, 2};
    Resource r4 = {4, "Delta Ekibi", ITFAIYE, 1, 1};
    Resource r5 = {5, "Epsilon Ekibi", AMBULANS, 0, 4};
    addResource(list, r1);
    addResource(list, r2);
    addResource(list, r3);
    addResource(list, r4);
    addResource(list, r5);

    // Stack
    Stack *stack = createStack(50);

    // Bölge ağacı
    TreeNode *root = createTreeNode(0, "Isparta");
    TreeNode *merkez = createTreeNode(1, "Merkez");
    TreeNode *egirdir = createTreeNode(2, "Egirdir");
    TreeNode *yalvac = createTreeNode(3, "Yalvac");
    TreeNode *sarkikaraagac = createTreeNode(4, "Sarkikaraagac");
    TreeNode *bahcelievler = createTreeNode(5, "Bahcelievler");
    TreeNode *guneykent = createTreeNode(6, "Guneykent");
    addChild(root, merkez);
    addChild(root, egirdir);
    addChild(root, yalvac);
    addChild(root, sarkikaraagac);
    addChild(merkez, bahcelievler);
    addChild(merkez, guneykent);

    // Menüyü başlat
    showMenu(g, pq, list, stack, ht, bst, root);

    return 0;
}