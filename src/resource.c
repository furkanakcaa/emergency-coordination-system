#include <stdio.h>
#include <stdlib.h>
#include "resource.h"

ResourceList *createList()
{
    ResourceList *rl = (ResourceList *)malloc(sizeof(ResourceList));
    if (rl == NULL)
    {
        printf("\nbellek hatasi");
        exit(1);
    }
    rl->head = NULL;
    rl->count = 0;
    return rl;
}

void addResource(ResourceList *list, Resource resource)
{
    ResourceNode *node = (ResourceNode *)malloc(sizeof(ResourceNode));
    node->data = resource;
    node->next = list->head;
    list->head = node;
    list->count++;
}

void removeResource(ResourceList *list, int id)
{
    if (list->head == NULL)
        return;

    if (list->head->data.id == id)
    {
        ResourceNode *silinecek = list->head;
        list->head = list->head->next;
        free(silinecek);
        list->count--;
        return;
    }

    ResourceNode *temp = list->head;
    while (temp->next != NULL && temp->next->data.id != id)
        temp = temp->next;

    if (temp->next == NULL)
        return;

    ResourceNode *silinecek = temp->next;
    temp->next = temp->next->next;
    free(silinecek);
    list->count--;
}

ResourceNode *findAvailable(ResourceList *list, ResourceType type)
{
    ResourceNode *temp = list->head;
    while (temp != NULL)
    {
        if (temp->data.isBusy == 0 && temp->data.type == type)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

void printList(ResourceList *list)
{
    ResourceNode *temp = list->head;
    while (temp != NULL)
    {
        printf("\nid: %d", temp->data.id);
        printf("\nname: %s", temp->data.name);
        printf("\nmesgul mu: %d", temp->data.isBusy);
        printf("\tip: %d", temp->data.type);
        printf("\bolge id: %d", temp->data.regionId);
        temp = temp->next;
    }
}

void freeList(ResourceList *list)
{
    ResourceNode *temp = list->head;

    while (temp != NULL)
    {
        ResourceNode *next = temp->next;
        free(temp);
        temp = next;
    }

    free(list);
}