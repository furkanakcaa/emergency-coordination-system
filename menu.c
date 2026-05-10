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
#include "performance_test.h"

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
            incidentMenu(pq, ht, bst, stack, g);
            break;
        case 2:
            resourceMenu(list, g);
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

void incidentMenu(PriorityQueue *pq, HashTable *ht, BST *bst, Stack *stack, Graph *g)
{
    int secim;
    do
    {
        printf("\n\n** Olay Yonetimi **\n");
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

            if (searchRecord(ht, inc.id) != NULL)
            {
                printf("Bu ID zaten mevcut!\n");
                break;
            }

            do
            {
                printf("Oncelik (1-5): ");
                scanf("%d", &inc.priority);
                if (inc.priority < 1 || inc.priority > 5)
                    printf("Gecersiz! 1-5 arasi girin.\n");
            } while (inc.priority < 1 || inc.priority > 5);

            int tip;
            do
            {
                printf("Tip (0:FIRE, 1:MEDICAL, 2:RESCUE): ");
                scanf("%d", &tip);
                if (tip < 0 || tip > 2)
                    printf("Gecersiz! 0-2 arasi girin.\n");

            } while (tip < 0 || tip > 2);

            inc.type = (IncidentType)tip;

            do
            {
                printf("Bolge ID (0-%d): ", g->node_count - 1);
                scanf("%d", &inc.regionId);
                if (inc.regionId < 0 || inc.regionId >= g->node_count)
                    printf("Gecersiz! Boyle bir bolge yok. \n");
            } while (inc.regionId < 0 || inc.regionId >= g->node_count);

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
            printf("\nTip: %s", incidentTypeToString(top.type));
            printf("\nBolge: %s", g->nodes[top.regionId].region_name);
            break;
        }
        case 3:
        {
            if (isEmptyPQ(pq))
            {
                printf("Kuyruk bos!\n");
                break;
            }

            Incident top = peekMin(pq);
            printf("Kapatilacak olay:\n");
            printf("ID      : %d\n", top.id);
            printf("Oncelik : %d\n", top.priority);
            printf("Tip     : %s\n", incidentTypeToString(top.type));
            printf("Bolge   : %s\n", g->nodes[top.regionId].region_name);
            printf("Onayliyor musunuz? (1:Evet 0:Hayir): ");

            int onay;
            scanf("%d", &onay);
            if (onay != 1)
                break;

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
                printf("\nTip  : %s", incidentTypeToString(inc->type));
                printf("\nDurum: %s", incidentStatusToString(inc->status));
                printf("\nBolge: %s", g->nodes[inc->regionId].region_name);
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

void resourceMenu(ResourceList *list, Graph *g)
{
    int secim;
    do
    {
        printf("\n\n** Ekip Yonetimi **\n");
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

            if (findById(list, r.id) != NULL)
            {
                printf("Bu ID zaten mevcut!\n");
                break;
            }

            printf("Ad: ");
            scanf("%s", r.name);

            do
            {
                printf("Tip (0:ITFAIYE 1:AMBULANS 2:KURTARMA): ");
                scanf("%d", &r.type);
                if (r.type < 0 || r.type > 2)
                    printf("Gecersiz! 0-2 arasi girin.\n");

            } while (r.type < 0 || r.type > 2);

            do
            {
                printf("Bolge ID (0-%d): ", g->node_count - 1);
                scanf("%d", &r.regionId);
                if (r.regionId < 0 || r.regionId >= g->node_count)
                    printf("Gecersiz! Boyle bir bolge yok.\n");
            } while (r.regionId < 0 || r.regionId >= g->node_count);

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
        printf("\n\n** Bolge Islemleri **\n");
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

            if (start >= g->node_count || end >= g->node_count || start < 0 || end < 0)
            {
                printf("Gecersiz bolge ID!\n");
                break;
            }

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
        printf("\n\n** Raporlama **\n");
        printf("1. Olaylari oncelik sirasinda listele\n");
        printf("2. Hash table yazdir\n");
        printf("3. Rapor\n");
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
        case 3:
            performanceTesti();
            break;
        case 0:
            break;
        }
    } while (secim != 0);
}