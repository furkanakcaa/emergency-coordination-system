#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "graph.h"

Graph *createGraph(int maxNodes)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));

    if (graph == NULL)
    {
        printf("Bellek Hatasi!\n");
        exit(1);
    }

    graph->node_count = 0;
    graph->nodes = (Node *)malloc(sizeof(Node) * maxNodes);

    return graph;
}

void addRegion(Graph *graph, int id, char *name)
{
    graph->nodes[id].head = NULL;
    graph->nodes[id].region_id = id;
    strcpy(graph->nodes[id].region_name, name);

    graph->node_count++;
}

void addRoad(Graph *graph, int from, int to, int weight)
{
    Edge *edge = (Edge *)malloc(sizeof(Edge));
    edge->target_id = to;
    edge->weight = weight;
    edge->next = graph->nodes[from].head;
    graph->nodes[from].head = edge;

    Edge *edgeReverse = (Edge *)malloc(sizeof(Edge));
    edgeReverse->target_id = from;
    edgeReverse->weight = weight;
    edgeReverse->next = graph->nodes[to].head;
    graph->nodes[to].head = edgeReverse;
}

void printGraph(Graph *graph)
{
    for (int i = 0; i < graph->node_count; i++)
    {
        printf("\n-- bolge --\n");
        printf("bolge id: %d\n", graph->nodes[i].region_id);
        printf("bolge adi: %s\n", graph->nodes[i].region_name);

        printf("\n-- yollar --\n");

        Edge *edge = graph->nodes[i].head;
        while (edge != NULL)
        {
            printf("target id: %d\n", edge->target_id);
            printf("target agirlik: %d\n", edge->weight);
            edge = edge->next;
        }
    }
}

void freeGraph(Graph *graph)
{
    for (int i = 0; i < graph->node_count; i++)
    {
        Edge *edge = graph->nodes[i].head;
        while (edge != NULL)
        {
            Edge *next = edge->next;
            free(edge);
            edge = next;
        }
    }
    free(graph->nodes);
    free(graph);
}

int minDistance(int dist[], int visited[], int node_count)
{
    int minDist = INT_MAX, index = -1;
    for (int i = 0; i < node_count; i++)
    {
        if (visited[i] != 0)
            continue;
        else
        {
            if (dist[i] < minDist)
            {
                minDist = dist[i];
                index = i;
            }
        }
    }
    return index;
}

void dijkstra(Graph *graph, int start, int end)
{
    int n = graph->node_count;
    int dist[n], visited[n], prev[n];

    for (int i = 0; i < n; i++)
    {
        dist[i] = INT_MAX;
        visited[i] = 0;
        prev[i] = -1;
    }
    dist[start] = 0;

    for (int i = 0; i < n; i++)
    {
        int current = minDistance(dist, visited, n);
        if (current == -1)
            break;
        visited[current] = 1;

        Edge *edge = graph->nodes[current].head;
        while (edge != NULL)
        {
            int neighbor = edge->target_id;
            int newDist = dist[current] + edge->weight;

            if (!visited[neighbor] && newDist < dist[neighbor])
            {
                dist[neighbor] = newDist;
                prev[neighbor] = current;
            }
            edge = edge->next;
        }
    }

    int path[n], pathLen = 0;
    int cur = end;

    while (cur != -1)
    {
        path[pathLen++] = cur;
        cur = prev[cur];
    }

    printf("\n\nyol: ");
    for (int i = pathLen - 1; i >= 0; i--)
        printf("%d ", path[i]);
    printf("\nToplam mesafe: %d\n", dist[end]);
}
