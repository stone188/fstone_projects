#ifndef STUDENT_H
#define STUDENT_H
#include "Person.h"
#include "TreeNode.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <sstream>

class Student : public Person{
	public:
		std::string major;
		int mentor, assigned;
		double GPA;
		
		Student();
		~Student();
		Student(int me, double g, std::string ma);
		Student(string dataRec);
		
		void display();
		virtual std::string ToString();
		
		bool operator == (const Student &other);
		bool operator != (const Student &other);
		bool operator <  (const Student &other);
		bool operator >  (const Student &other);
		
		bool operator == (const int ID);
		bool operator != (const int ID);
		bool operator < (const int ID);
		bool operator > (const int ID);
};

#endif