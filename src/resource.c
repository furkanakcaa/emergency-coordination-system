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

ResourceNode *findById(ResourceList *list, int id)
{
    ResourceNode *temp = list->head;
    while (temp != NULL)
    {
        if (temp->data.id == id)
            return temp;
        temp = temp->next;
    }
    return NULL;
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
    {
        printf("Liste bo!\n");
        return;
    }

    if (list->head->data.id == id)
    {
        ResourceNode *silinecek = list->head;
        list->head = list->head->next;
        free(silinecek);
        list->count--;
        printf("Ekip silindi.\n");
        return;
    }

    ResourceNode *temp = list->head;
    while (temp->next != NULL && temp->next->data.id != id)
        temp = temp->next;

    if (temp->next == NULL)
    {
        printf("Bu ID ile ekip bulunamadi!\n");
        return;
    }

    ResourceNode *silinecek = temp->next;
    temp->next = temp->next->next;
    free(silinecek);
    list->count--;
    printf("Ekip silindi.\n");
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

char *resourceTypeToString(ResourceType type)
{
    if (type == ITFAIYE)
        return "Itfaiye";
    if (type == AMBULANS)
        return "Ambulans";
    return "Kurtarma";
}

void printList(ResourceList *list)
{
    if (list->head == NULL)
    {
        printf("Listede ekip yok!\n");
        return;
    }

    ResourceNode *temp = list->head;
    while (temp != NULL)
    {
        printf("\n\nid: %d", temp->data.id);
        printf("\nname: %s", temp->data.name);
        printf("\nmesgul mu: %d", temp->data.isBusy);
        printf("\ntip: %s", resourceTypeToString(temp->data.type));
        printf("\nbolge id: %d", temp->data.regionId);
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