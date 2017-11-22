#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include "AdjacencyMatrix.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <stdio.h>

class Dijkstra{
	public:
		int n;
		
		Dijkstra(int n);
		~Dijkstra();
		
		int minDistance(int distance[], bool sptSet[]);
		void printSolution(int distance[]);
		void dijkstraRun(int** graph, int source);
};
#endif