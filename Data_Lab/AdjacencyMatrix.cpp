#include "AdjacencyMatrix.h"
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

AdjacencyMatrix::AdjacencyMatrix(int n){
	this->n = n;
	visited = new bool [n];
	adjacent = new int* [n];
	
	for(int i = 0; i < n; ++i){
		adjacent[i] = new int [n];
		
		for(int j = 0; j < n; ++j){
			adjacent[i][j] = 0;
		}
	}
}

AdjacencyMatrix::~AdjacencyMatrix(){

}


void AdjacencyMatrix::addEdge(int o, int d, int w){
	if(o > n || d > n || o < 0 || d < 0){
		cout << "ERROR: Invalid edge\r\n";
	}
	
	else{
		adjacent[o - 1][d - 1] = w;
	}
}

void AdjacencyMatrix::printGraph(){
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			cout << adjacent[i][j] << "  ";
		}
		cout << endl;
	}
}

void AdjacencyMatrix::DFS(int node){
	visited[node] = 1;
	
	for(int i = 0; i < n; ++i){
		if(adjacent[i][node] && !visited[i]){
			DFS(i);
		}
	}
}





