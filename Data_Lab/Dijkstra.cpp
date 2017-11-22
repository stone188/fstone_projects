#include "Dijkstra.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <stdio.h>

#define INF 999999

using namespace std;

Dijkstra::Dijkstra(int n){
	this->n = n;
}

Dijkstra::~Dijkstra(){
	
}

int Dijkstra::minDistance(int distance[], bool sptSet[]){
	int min = INF;
	int min_index;
	
	for(int i = 0; i < n; ++i){
		if(sptSet[i] == false && distance[i] <= min){
			min = distance[i];
			min_index = i;
		}
	}
	return min_index;
}

void Dijkstra::printSolution(int distance[]){
	cout << "Vertex               Distance from Source" << endl;
	cout << "======               ====================\r\n";
	for(int i = 1; i < n; ++i){
		cout << i << "                        " << distance[i] << endl;
	}
}

void Dijkstra::dijkstraRun(int** graph, int source){
	int distance[n];
	bool sptSet[n];
	
	for(int i = 0; i < n; ++i){
		distance[i] = INF;
		sptSet[i] = false;
	}
	distance[source] = 0;
	
	for(int j = 0; j < n - 1; ++j){
		int shortest = minDistance(distance, sptSet);
		sptSet[shortest] = true;
		
		for(int k = 0; k < n; ++k){
			if(!sptSet[k] && graph[shortest][k] && distance[shortest] != INF && distance[shortest]
				+ graph[shortest][k] < distance[k]){
					distance[k] = distance[shortest] + graph[shortest][k];
				}
		}
	}
	printSolution(distance);
}

