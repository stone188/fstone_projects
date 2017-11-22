#ifndef PERSON_H
#define PERSON_H
#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

class Person{
	public:
		Person();
		~Person();
		
		int identification;
		string name;
		string level;
		
		void setValues(int id, string n, string l);
};

#endif