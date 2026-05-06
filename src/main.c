#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{

    Graph *g = createGraph(10);

    addRegion(g, 0, "Merkez");
    addRegion(g, 1, "Kuzey");
    addRegion(g, 2, "Güney");
    addRegion(g, 3, "Dogu");
    addRegion(g, 4, "Bati");
    addRegion(g, 5, "Kuzeydogu");

    addRoad(g, 0, 1, 5);
    addRoad(g, 0, 2, 3);
    addRoad(g, 2, 4, 1);
    addRoad(g, 4, 5, 1);
    addRoad(g, 1, 3, 8);
    addRoad(g, 2, 4, 6);
    addRoad(g, 3, 4, 2);
    addRoad(g, 2, 5, 3);

    printGraph(g);

    dijkstra(g, 0, 5);

    return 0;
}