#include "SortPrac.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

void methodHead(string method){
	cout << method << endl;
	cout << "===========\r\n";
}

int main(int argc, char** argv){
	double *a;
	double *b;
	double *c;
	
	clock_t timestamp;
	SortPrac sort;
	
	if(argc != 2){
		cout << "USAGE: " << argv[0] << " <FILENAME>\r\n";		
	}
	
	else{
		a = sort.fillArray(argv[1]);
	}
	int n = sort.getSize();
	b = new double[n];
	sort.duplicateArray(b, a, n);
	
	c = new double[n];
	sort.duplicateArray(c, a, n);
	
	methodHead("\r\nQuick Sort");
	timestamp = clock();
	sort.quickSort(a, 0, n - 1);
	timestamp = clock() - timestamp;
	//sort.print(a, n);
	cout << "Time (s): " << ((float)timestamp) / (CLOCKS_PER_SEC) << "\r\n";
	
	methodHead("\r\nInsert Sort");
	timestamp = clock();
	sort.insertSort(b, n);
	timestamp = clock() - timestamp;
	//sort.print(b, n);
	cout << "Time (s): " << ((float)timestamp) / (CLOCKS_PER_SEC) << "\r\n";
	
	methodHead("\r\nShell Sort");
	timestamp = clock();
	sort.shellSort(c, n);
	timestamp = clock() - timestamp;
	//sort.print(c, n);
	cout << "Time (s): " << ((float)timestamp) / (CLOCKS_PER_SEC) << endl;
	
	return 0;
}