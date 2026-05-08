#include <stdio.h>
#include <time.h>
#include "graph.h"
#include "incident.h"
#include "resource.h"
#include "stack.h"
#include "hash_table.h"
#include "bst.h"
#include "region_tree.h"
#include "menu.h"

void showMenu(Graph *g, PriorityQueue *pq, ResourceList *list, Stack *stack, HashTable *ht, BST *bst, TreeNode *root)
{
    int secim;
    do
    {
        printf("\n*** ACİL DURUM KOORDİNASYON SİSTEMİ ***\n");
        printf("1. Olay Yonetimi\n");
        printf("2. Ekip Yonetimi\n");
        printf("3. Bolge Islemleri\n");
        printf("4. Raporlama\n");
        printf("0. Cikis\n");
        printf("Seciminiz: ");
        scanf("%d", &secim);

        switch (secim)
        {
        case 1:
            incidentMenu(pq, ht, bst, stack);
            break;
        case 2:
            resourceMenu(list);
            break;
        case 3:
            regionMenu(g, root);
            break;
        case 4:
            reportMenu(bst, ht);
            break;
        case 0:
            printf("Cikis...\n");
            break;
        default:
            printf("Gecersiz secim!\n");
        }
    } while (secim != 0);
}

void incidentMenu(PriorityQueue *pq, HashTable *ht, BST *bst, Stack *stack)
{
    int secim;
    do
    {
        printf("\n** Olay Yonetimi **\n");
        printf("1. Yeni olay ekle\n");
        printf("2. En kritik olayi gor\n");
        printf("3. Olayi kapat\n");
        printf("4. ID ile sorgula\n");
        printf("0. Geri\n");
        scanf("%d", &secim);

        switch (secim)
        {
        case 1:
        {
            Incident inc;
            inc.assignedTeamId = -1;
            inc.status = WAITING;
            inc.timeStamp = time(NULL);
            printf("ID: ");
            scanf("%d", &inc.id);
            printf("Oncelik (1-5): ");
            scanf("%d", &inc.priority);
            printf("Bolge ID: ");
            scanf("%d", &inc.regionId);
            printf("Tip (0:FIRE, 1:MEDICAL, 2:RESCUE): ");
            scanf("%d", (int *)&inc.type);
            insertPQ(pq, inc);
            insertRecord(ht, inc);
            bst->root = insertBST(bst->root, inc);
            break;
        }
        case 2:
        {
            if (isEmptyPQ(pq))
            {
                printf("Kuyruk bos!\n");
                break;
            }

            Incident top = peekMin(pq);

            printf("\nEn kritik olay:");
            printf("\nID: %d", top.id);
            printf("\nOncelik: %d", top.priority);
            printf("\nTip: %d", top.type);
            printf("\nBolge: %d", top.regionId);
            break;
        }
        case 3:
        {
            if (isEmptyPQ(pq))
            {
                printf("Kuyruk bos!\n");
                break;
            }
            Incident closed = extractMin(pq);
            closed.status = RESOLVED;

            Action action;
            action.type = OLAY_KAPATMA;
            action.incidentId = closed.id;
            action.resourceId = closed.assignedTeamId;
            action.eskiDurum = WAITING;
            push(stack, action);

            printf("Olay %d kapatildi.\n", closed.id);
            break;
        }
        case 4:
        {
            int id;
            printf("\nSorgulanacak ID: ");
            scanf("%d", &id);

            Incident *inc = searchRecord(ht, id);
            if (inc == NULL)
                printf("Aranan olay bulunamadi\n");
            else
            {
                printf("\nID: %d", inc->id);
                printf("\nOncelik: %d", inc->priority);
                printf("\nTip: %d", inc->type);
                printf("\nDurum: %d", inc->status);
                printf("\nBolge: %d", inc->regionId);
                printf("\nAtanan ekip: %d", inc->assignedTeamId);
            }
            break;
        }
        case 0:
            printf("Geri donuluyor..\n");
            break;
        }
    } while (secim != 0);
}

void resourceMenu(ResourceList *list)
{
    int secim;
    do
    {
        printf("\n** Ekip Yonetimi **\n");
        printf("1. Ekip ekle\n");
        printf("2. Ekip sil\n");
        printf("3. Listeyi goster\n");
        printf("0. Geri\n");
        scanf("%d", &secim);

        switch (secim)
        {
        case 1:
        {
            Resource r;
            printf("ID: ");
            scanf("%d", &r.id);
            printf("Ad: ");
            scanf("%s", r.name);
            printf("Tip (0:ITFAIYE 1:AMBULANS 2:KURTARMA): ");
            scanf("%d", (int *)&r.type);
            printf("Bolge ID: ");
            scanf("%d", &r.regionId);
            r.isBusy = 0;
            addResource(list, r);
            break;
        }
        case 2:
        {
            int id;
            printf("Silinecek ID: ");
            scanf("%d", &id);
            removeResource(list, id);
            break;
        }
        case 3:
            printList(list);
            break;
        case 0:
            break;
        }

    } while (secim != 0);
}

void regionMenu(Graph *g, TreeNode *root)
{
    int secim;
    do
    {
        printf("\n** Bolge Islemleri **\n");
        printf("1. Graf yazdir\n");
        printf("2. En kisa yol bul\n");
        printf("3. Bolge agaci yazdir\n");
        printf("0. Geri\n");
        scanf("%d", &secim);

        switch (secim)
        {
        case 1:
            printGraph(g);
            break;
        case 2:
        {
            int start, end;
            printf("Baslangic bolge ID: ");
            scanf("%d", &start);
            printf("Hedef bolge ID: ");
            scanf("%d", &end);
            dijkstra(g, start, end);
            break;
        }
        case 3:
            printTree(root, 0);
            break;
        case 0:
            break;
        }

    } while (secim != 0);
}

void reportMenu(BST *bst, HashTable *ht)
{
    int secim;
    do
    {
        printf("\n** Raporlama **\n");
        printf("1. Olaylari oncelik sirasinda listele\n");
        printf("2. Hash table yazdir\n");
        printf("0. Geri\n");
        scanf("%d", &secim);

        switch (secim)
        {
        case 1:
            inorderBST(bst->root);
            break;
        case 2:
            printHashTable(ht);
            break;
        case 0:
            break;
        }
    } while (secim != 0);
}