#pragma once

#include <iostream>

#include "OrientedGraph.h"
#include "GetGraph.h"

using namespace std;

int Comparer(int weight1, int weight2)
{
	if (weight1 > weight2)
		return 1;
	if (weight1 < weight2)
		return -1;
	return 0;
}

int Add(int weight1, int weight2)
{
	return weight1 + weight2;
}



void GraphTasks()
{
	OrientedGraph<int, int>* graph = GetGraph();

	int length = 0;
	Sequence<Vertex<int, int>*>* path = nullptr;
	

	for (int i = 0; i < graph->GetVertexCount(); i++)
	{
		for (int j = 0; j < graph->GetVertexCount(); j++)
		{
			if (i == j)
				continue;
			try
			{
				graph->Dijkstra(i, j, Comparer, Add, length, path);

				cout << "Rout from vertex-" << i << " to vertex-" << j << endl;
				cout << "LENGTH: " << length << endl;
				cout << "ROUTE: " << path->Get(0)->GetKey();
				for (int k = 1; k < path->GetLength(); k++)
				{
					cout << "-" << path->Get(k)->GetKey();
				}
				cout << endl << endl;
			}
			catch (Exception error)
			{ }
		}
	}
}