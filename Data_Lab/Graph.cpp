#include "AdjacencyMatrix.h"
#include "Dijkstra.h"
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int main(){
	int nodes, origin, destination, weight, max_edges;
	string proceed;
	
	cout << "\r\nWeighted, Directed Graph Input Tool" << endl;
	cout << "====================================\r\n";
	cout << " ---------------------------------------------------- " << endl;
	cout << "|1. Enter number of nodes.                           |" << endl;
	cout << "|2. Enter each edge.                                 |" << endl;
	cout <<	"|>format = (Start, Finish, Weight) all as integers.  |" << endl;
	cout << " ---------------------------------------------------- \r\n";
	
	cout << "Please enter the number of nodes for entry: " << endl;
	cin >> nodes;
	
	max_edges = nodes * (nodes - 1);
	AdjacencyMatrix weightedDirectedGraph(nodes);
	
	for(int i = 0; i < max_edges; ++i){
		cout << "Please enter edge (-1 -1 0 to exit): " << endl;
		cin >> origin >> destination >> weight;
		
		if(origin == -1 && destination == -1 && weight == 0){
			break;
		}
		
		else{
			weightedDirectedGraph.addEdge(origin, destination, weight);
		}
	}
	cout << "\r\n";
	weightedDirectedGraph.printGraph();
	
	cout << "\r\nWould you like to apply Dijkstra's algorithm? [y/n]: " << endl;
	cin >> proceed;
	
	if(proceed == "y"){
		Dijkstra dijkstra(nodes);
		dijkstra.dijkstraRun(weightedDirectedGraph.adjacent, 0);
	}
	
	else if(proceed == "n"){
		cout << "Good Bye." << endl;
	}
	
	else{
		cout << "ERROR: System exit due to invalid entry.";
	}
	return 0;
}