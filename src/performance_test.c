#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bst.h"
#include "hash_table.h"
#include <windows.h>

double olcSure(LARGE_INTEGER bas, LARGE_INTEGER bitis, LARGE_INTEGER frekans)
{
    return (double)(bitis.QuadPart - bas.QuadPart) / frekans.QuadPart * 1000.0;
}

void performanceTesti()
{
    LARGE_INTEGER frekans, bas, bitis;
    QueryPerformanceFrequency(&frekans);

    srand(time(NULL));
    int boyutlar[] = {100, 1000, 10000};
    int tekrar = 10000;

    for (int b = 0; b < 3; b++)
    {
        int n = boyutlar[b];

        HashTable *ht = createHashTable();
        BST *bst = createBST();

        for (int i = 0; i < n; i++)
        {
            Incident inc;
            inc.id = i;
            inc.priority = (rand() % 5) + 1;
            inc.status = WAITING;
            inc.regionId = rand() % 10;
            inc.assignedTeamId = -1;
            inc.timeStamp = time(NULL);
            insertRecord(ht, inc);
            bst->root = insertBST(bst->root, inc);
        }

        // Arama testi
        QueryPerformanceCounter(&bas);
        for (int i = 0; i < tekrar; i++)
            searchRecord(ht, rand() % n);
        QueryPerformanceCounter(&bitis);
        double htArama = olcSure(bas, bitis, frekans) / tekrar;

        QueryPerformanceCounter(&bas);
        for (int i = 0; i < tekrar; i++)
            searchBST(bst->root, (rand() % 5) + 1);
        QueryPerformanceCounter(&bitis);
        double bstArama = olcSure(bas, bitis, frekans) / tekrar;

        // Ekleme testi
        QueryPerformanceCounter(&bas);
        for (int i = 0; i < tekrar; i++)
        {
            Incident inc;
            inc.id = n + i;
            inc.priority = (rand() % 5) + 1;
            inc.status = WAITING;
            inc.regionId = rand() % 10;
            inc.assignedTeamId = -1;
            inc.timeStamp = time(NULL);
            insertRecord(ht, inc);
        }
        QueryPerformanceCounter(&bitis);
        double htEkleme = olcSure(bas, bitis, frekans) / tekrar;

        QueryPerformanceCounter(&bas);
        for (int i = 0; i < tekrar; i++)
        {
            Incident inc;
            inc.id = n + tekrar + i;
            inc.priority = (rand() % 5) + 1;
            inc.status = WAITING;
            inc.regionId = rand() % 10;
            inc.assignedTeamId = -1;
            inc.timeStamp = time(NULL);
            bst->root = insertBST(bst->root, inc);
        }
        QueryPerformanceCounter(&bitis);
        double bstEkleme = olcSure(bas, bitis, frekans) / tekrar;

        // Silme testi
        QueryPerformanceCounter(&bas);
        for (int i = 0; i < tekrar; i++)
            deleteRecord(ht, rand() % n);
        QueryPerformanceCounter(&bitis);
        double htSilme = olcSure(bas, bitis, frekans) / tekrar;

        QueryPerformanceCounter(&bas);
        for (int i = 0; i < tekrar; i++)
            bst->root = deleteBST(bst->root, (rand() % 5) + 1);
        QueryPerformanceCounter(&bitis);
        double bstSilme = olcSure(bas, bitis, frekans) / tekrar;

        printf("\n========== %d Kayit ==========\n", n);
        printf("%-25s %.6f ms\n", "Hash Table arama:", htArama);
        printf("%-25s %.6f ms\n", "BST arama:", bstArama);
        printf("%-25s %.6f ms\n", "Hash Table ekleme:", htEkleme);
        printf("%-25s %.6f ms\n", "BST ekleme:", bstEkleme);
        printf("%-25s %.6f ms\n", "Hash Table silme:", htSilme);
        printf("%-25s %.6f ms\n", "BST silme:", bstSilme);

        freeHashTable(ht);
        freeBST(bst->root);
        free(bst);
    }
}