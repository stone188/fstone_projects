#include "SortPrac.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

SortPrac::SortPrac(){
	
}

SortPrac::~SortPrac(){
	s = 0;
	delete a;
}

double* SortPrac::fillArray(string file){
	const char* user_file = file.c_str();
	string line;
	int array_size;
	
	ifstream ifs(user_file);
	
	if(!ifs.is_open()){
		cout << "ERROR: Could not open file\r\n";
	}
	
	else{
		getline(ifs, line);
		array_size = stoi(line);
		a = new double[array_size];
		
		while(!ifs.eof()){
			for(int i = 0; i < array_size; ++i){
				getline(ifs, line);
				a[i] = stod(line);
				++s;
			}
		}
		ifs.close();
	}
	return a;
}

double* SortPrac::duplicateArray(double arr[], double arr2[], int size){
	for(int i = 0; i < size; ++i){
		arr[i] = arr2[i];
	}
	return arr;
} 

void SortPrac::quickSort(double arr[], int left, int right){
	int i = left;
	int j = right;
	double tmp;
	double pivot = arr[(left + right) / 2];
	
	while(i <= j){
		while(arr[i] < pivot){
			++i;
		}
		
		while(arr[j] > pivot){
			--j;
		}
		
		if(i <= j){
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			++i;
			--j;
		}
	}
	if(left < j){
		quickSort(arr, left, j);
	}
	
	if(i < right){
		quickSort(arr, i, right);
	}
}

void SortPrac::insertSort(double arr[], int size){
	int j;
	double tmp;
	
	for(int i = 0; i < size; ++i){
		j = i;
		
		while(j > 0 && arr[j] < arr[j-1]){
			tmp = arr[j];
			arr[j] = arr[j-1];
			arr[j-1] = tmp;
			--j;
		}
	}
}

void SortPrac::shellSort(double arr[], int size){
	int gap, i, j;
	double tmp;
	
	for(gap = size / 2; gap > 0; gap /= 2){
		for(i = gap; i < size; ++i){
			for(j = i - gap; j >= 0 && arr[j] > arr[j + gap]; j -= gap){
				tmp = arr[j];
				arr[j] = arr[j + gap];
				arr[j + gap] = tmp;
			}
		}
	}
}

void SortPrac::print(double arr[], int size){
	for(int i = 0; i < size; ++i){
		cout << arr[i] << " ";
	}
	cout << endl;
}

int SortPrac::getSize(){
	return s;
}