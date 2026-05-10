#ifndef GRAPH_H
#define GRAPH_H

typedef struct Edge
{
    int target_id;
    int weight;
    struct Edge *next;
} Edge;

typedef struct Node
{
    int region_id;
    char region_name[50];
    struct Edge *head; // adjacency list başı
} Node;

typedef struct Graph
{
    struct Node *nodes;
    int node_count;
} Graph;

Graph *createGraph(int maxNodes);
void addRegion(Graph *graph, int id, char *name);
void addRoad(Graph *graph, int from, int to, int weight);
void printGraph(Graph *graph);
void dijkstra(Graph *graph, int start, int end);
void freeGraph(Graph *graph);

#endif