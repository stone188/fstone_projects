#ifndef SORTPRAC_H
#define SORTPRAC_H
#include <iostream>
#include <string>

class SortPrac{
	public:
		SortPrac();
		~SortPrac();
		
		double *a;
		int s = 0;
		
		double* fillArray(std::string file);
		double* duplicateArray(double arr[], double arr2[], int size);
		void quickSort(double arr[], int right, int left);
		void insertSort(double arr[], int size);
		void shellSort(double arr[], int size);
		void print(double arr[], int size);
		int getSize();
};
#endif