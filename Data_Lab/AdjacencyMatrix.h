#ifndef ADJACENCYMATRIX_H
#define ADJACENCYMATRIX_H
#include <iostream>
#include <string>

class AdjacencyMatrix{
	private:
		int n;
		bool *visited;
		
	public:
		int **adjacent;
		
		AdjacencyMatrix(int n);
		~AdjacencyMatrix();
		
		void addEdge(int o, int d, int w);
		void printGraph();
		void DFS(int node);
};
#endif