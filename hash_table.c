#include <stdio.h>
#include <stdlib.h>
#include "hash_table.h"

HashTable *createHashTable()
{
    HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
    for (int i = 0; i < TABLE_SIZE; i++)
        ht->buckets[i] = NULL;
    return ht;
}

void insertRecord(HashTable *ht, Incident incident)
{
    int index = incident.id % TABLE_SIZE;

    HashNode *hashNode = (HashNode *)malloc(sizeof(HashNode));
    hashNode->data = incident;
    hashNode->next = ht->buckets[index];
    ht->buckets[index] = hashNode;
}

Incident *searchRecord(HashTable *ht, int id)
{
    int index = id % TABLE_SIZE;
    HashNode *node = ht->buckets[index];

    while (node != NULL && node->data.id != id)
        node = node->next;

    return &node->data;
}

void deleteRecord(HashTable *ht, int id)
{
    int index = id % TABLE_SIZE;

    if (ht->buckets[index] == NULL)
    {
        printf("Bu ID ile olay bulunamadi!\n");
        return;
    }

    if (ht->buckets[index]->data.id == id)
    {
        HashNode *temp = ht->buckets[index];
        ht->buckets[index] = temp->next;
        free(temp);
        printf("Olay silindi.\n");
        return;
    }

    HashNode *node = ht->buckets[index];

    while (node->next != NULL && node->next->data.id != id)
        node = node->next;

    if (node->next == NULL)
    {
        printf("Bu ID ile olay bulunamadi!\n");
        return;
    }

    HashNode *temp = node->next;
    node->next = node->next->next;
    free(temp);
    printf("Olay silindi.\n");
}

void printHashTable(HashTable *ht)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        HashNode *temp = ht->buckets[i];
        while (temp != NULL)
        {
            printf("\n\nid: %d", temp->data.id);
            printf("\natanan ekip id: %d", temp->data.assignedTeamId);
            printf("\noncelik: %d", temp->data.priority);
            printf("\ntip: %d", temp->data.type);
            printf("\ndurum: %d", temp->data.status);
            printf("\nbolge id: %d", temp->data.regionId);
            temp = temp->next;
        }
    }
}

void freeHashTable(HashTable *ht)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        HashNode *temp = ht->buckets[i];
        while (temp != NULL)
        {
            HashNode *next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(ht);
}