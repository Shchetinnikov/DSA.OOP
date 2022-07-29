#pragma once

#include <string>

#include "Vertex.h"
#include "OrientedGraph.h"

OrientedGraph<int, int>* GetGraph()
{
    //string locality[7] = {"Medvedka", "Pirogovo", "Sosnovka", "Balezino", "Belyany", "Vasenki", "Gordino"};
   /* for (int i = 0; i < 7; i++)
    {
        Vertex<string, int>* vertex = new Vertex<string, int>(locality[i]);
        graph->AddVertex(locality[i], vertex);
    }*/

    /* graph->AddEdge("Medvedka", "Pirogovo", 4);
     graph->AddEdge("Medvedka", "Balezino", 6);
     graph->AddEdge("Medvedka", "Sosnovka", 10);
     graph->AddEdge("Pirogovo", "Balezino", 1);
     graph->AddEdge("Pirogovo", "Vasenki", 8);
     graph->AddEdge("Pirogovo", "Belyany", 9);
     graph->AddEdge("Sosnovka", "Belyany", 7);
     graph->AddEdge("Sosnovka", "Vasenki", 3);
     graph->AddEdge("Sosnovka", "Gordino", 5);
     graph->AddEdge("Balezino", "Belyany", 6);
     graph->AddEdge("Belyany", "Gordino", 3);
     graph->AddEdge("Vasenki", "Gordino", 7);*/


    OrientedGraph<int, int>* graph = new OrientedGraph<int, int>();

#if 0

    for (int i = 0; i < 7; i++)
    {
        Vertex<int, int>* vertex = new Vertex<int, int>(i);
        graph->AddVertex(i, vertex);
    }

    graph->AddEdge(0, 1, 4);
    graph->AddEdge(0, 3, 6);
    graph->AddEdge(0, 2, 10);
    graph->AddEdge(1, 3, 1);
    graph->AddEdge(1, 5, 8);
    graph->AddEdge(1, 4, 9);
    graph->AddEdge(2, 4, 7);
    graph->AddEdge(2, 5, 3);
    graph->AddEdge(2, 6, 5);
    graph->AddEdge(3, 4, 6);
    graph->AddEdge(4, 6, 3);
    graph->AddEdge(5, 6, 7);

#endif

#if 1

    for (int i = 0; i < 11; i++)
    {
        Vertex<int, int>* vertex = new Vertex<int, int>(i);
        graph->AddVertex(i, vertex);
    }

    graph->AddEdge(0, 1, 3);
    graph->AddEdge(0, 2, 6);
    graph->AddEdge(0, 2, 5);
    graph->AddEdge(0, 3, 11);
    graph->AddEdge(0, 4, 2);
    graph->AddEdge(0, 5, 14);

    graph->AddEdge(2, 0, 4);
    graph->AddEdge(2, 3, 9);
    graph->AddEdge(2, 7, 6);

    graph->AddEdge(1, 0, 3);

    graph->AddEdge(3, 0, 10);
    graph->AddEdge(3, 2, 4);

    graph->AddEdge(4, 5, 3);

    graph->AddEdge(5, 6, 2);

    graph->AddEdge(6, 7, 1);
    graph->AddEdge(6, 9, 2);
    graph->AddEdge(6, 10, 3);

    graph->AddEdge(7, 8, 4);
    graph->AddEdge(8, 10, 6);
    graph->AddEdge(9, 10, 3);
    graph->AddEdge(10, 9, 3);
#endif

    return graph;
}
