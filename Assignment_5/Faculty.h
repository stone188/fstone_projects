#ifndef FACULTY_H
#define FACULTY_H
#include "Person.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <sstream>

class Faculty : public Person{
	public:
		std::vector<int> mentee;
		std::string department, title;
		
		Faculty();
		~Faculty();
		Faculty(std::vector<int> m, std::string dep);
		Faculty(string dataRec);
		
		void display(); 
		virtual std::string ToString();
		
		bool operator == (const Faculty &other);
		bool operator != (const Faculty &other);
		bool operator <  (const Faculty &other);
		bool operator >  (const Faculty &other);
		
		bool operator == (const int ID);
		bool operator != (const int ID);
		bool operator < (const int ID);
		bool operator > (const int ID);
};

#endif