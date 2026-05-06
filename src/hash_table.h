#include "incident.h"

#define TABLE_SIZE 50

typedef struct HashNode
{
    Incident data;
    struct HashNode *next;
} HashNode;

typedef struct HashTable
{
    HashNode *buckets[TABLE_SIZE];
} HashTable;

HashTable *createHashTable();
void insertRecord(HashTable *ht, Incident incident);
Incident *searchRecord(HashTable *ht, int id);
void deleteRecord(HashTable *ht, int id);
void printHashTable(HashTable *ht);
void freeHashTable(HashTable *ht);