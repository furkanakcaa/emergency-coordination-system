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
    Graph *g = createGraph(15);
    addRegion(g, 0, "Cankaya");
    addRegion(g, 1, "Kecioren");
    addRegion(g, 2, "Mamak");
    addRegion(g, 3, "Etimesgut");
    addRegion(g, 4, "Sincan");
    addRegion(g, 5, "Yenimahalle");
    addRegion(g, 6, "Pursaklar");
    addRegion(g, 7, "Golbasi");
    addRegion(g, 8, "Altindag");
    addRegion(g, 9, "Cubuk");

    addRoad(g, 0, 1, 8);
    addRoad(g, 0, 2, 6);
    addRoad(g, 0, 5, 5);
    addRoad(g, 1, 6, 7);
    addRoad(g, 1, 8, 4);
    addRoad(g, 2, 8, 5);
    addRoad(g, 2, 9, 12);
    addRoad(g, 3, 4, 9);
    addRoad(g, 3, 5, 6);
    addRoad(g, 4, 5, 8);
    addRoad(g, 5, 8, 7);
    addRoad(g, 6, 9, 15);
    addRoad(g, 7, 0, 18);
    addRoad(g, 8, 9, 20);

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
    TreeNode *root = createTreeNode(0, "Ankara");
    TreeNode *cankaya = createTreeNode(1, "Cankaya");
    TreeNode *kecioren = createTreeNode(2, "Kecioren");
    TreeNode *mamak = createTreeNode(3, "Mamak");
    TreeNode *etimesgut = createTreeNode(4, "Etimesgut");
    TreeNode *sincan = createTreeNode(5, "Sincan");
    TreeNode *yenimahalle = createTreeNode(6, "Yenimahalle");

    TreeNode *bahcelievler = createTreeNode(7, "Bahcelievler");
    TreeNode *cukurambar = createTreeNode(8, "Cukurambar");
    TreeNode *dikmen = createTreeNode(9, "Dikmen");
    TreeNode *eryaman = createTreeNode(10, "Eryaman");
    TreeNode *batikent = createTreeNode(11, "Batikent");
    TreeNode *demetevler = createTreeNode(12, "Demetevler");
    TreeNode *pursaklar = createTreeNode(13, "Pursaklar");

    addChild(root, cankaya);
    addChild(root, kecioren);
    addChild(root, mamak);
    addChild(root, etimesgut);
    addChild(root, sincan);
    addChild(root, yenimahalle);

    addChild(cankaya, bahcelievler);
    addChild(cankaya, cukurambar);
    addChild(cankaya, dikmen);
    addChild(etimesgut, eryaman);
    addChild(sincan, batikent);
    addChild(kecioren, demetevler);
    addChild(kecioren, pursaklar);

    // Menüyü başlat
    showMenu(g, pq, list, stack, ht, bst, root);

    return 0;
}