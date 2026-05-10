#include <stdio.h>
#include <stdlib.h>
#include "incident.h"

PriorityQueue *createPQ(int capacity)
{
    PriorityQueue *pq = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    pq->data = (Incident *)malloc(sizeof(Incident) * capacity);
    pq->size = 0;
    pq->capacity = capacity;
    return pq;
}

int isEmptyPQ(PriorityQueue *pq)
{
    if (pq->size == 0)
        return 1;
    else
        return 0;
}

Incident peekMin(PriorityQueue *pq)
{
    return pq->data[0];
}

void heapifyUp(PriorityQueue *pq, int index)
{
    while (index != 0 && pq->data[(index - 1) / 2].priority > pq->data[index].priority)
    {
        Incident temp = pq->data[(index - 1) / 2];
        pq->data[(index - 1) / 2] = pq->data[index];
        pq->data[index] = temp;
        index = (index - 1) / 2;
    }
}

void insertPQ(PriorityQueue *pq, Incident incident)
{
    pq->data[pq->size] = incident;
    pq->size++;
    heapifyUp(pq, pq->size - 1);
}

void heapifyDown(PriorityQueue *pq, int index)
{
    int l = index * 2 + 1;
    int r = index * 2 + 2;
    int smallest = index;

    if (l < pq->size && pq->data[l].priority < pq->data[smallest].priority)
        smallest = l;

    if (r < pq->size && pq->data[r].priority < pq->data[smallest].priority)
        smallest = r;

    if (smallest != index)
    {
        Incident temp = pq->data[index];
        pq->data[index] = pq->data[smallest];
        pq->data[smallest] = temp;
        heapifyDown(pq, smallest);
    }
}

Incident extractMin(PriorityQueue *pq)
{
    Incident temp = pq->data[0];
    pq->data[0] = pq->data[pq->size - 1];
    pq->size--;
    heapifyDown(pq, 0);
    return temp;
}

char *incidentTypeToString(IncidentType type)
{
    if (type == FIRE)
        return "Yangin";
    if (type == MEDICAL)
        return "Tibbi";
    return "Kurtarma";
}

char *incidentStatusToString(IncidentStatus status)
{
    if (status == WAITING)
        return "Bekliyor";
    if (status == ASSIGNED)
        return "Atandi";
    return "Tamamlandi";
}

void freePQ(PriorityQueue *pq)
{
    free(pq->data);
    free(pq);
}