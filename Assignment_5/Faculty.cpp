#include "Faculty.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <sstream>

using namespace std;

Faculty::Faculty(){
	identification = 0;
	name = "Unknown";
	level = "Unknown";
	department = "Unknown";
}

Faculty::~Faculty(){
	
}

Faculty::Faculty(vector<int> m, string dep){
	mentee = m;
	department = dep;
}

Faculty::Faculty(string dataRec){
	istringstream data(dataRec);
    int num_students;
    data >> identification >> name >> level >> department >> title >> num_students;
    for (int i = 0; i < num_students; i++) {
		int student_id;
        data >> student_id;
        mentee.push_back(student_id);
    }
}

void Faculty::display(){
	cout << "\r\nFaculty member's ID: " << identification << "\r\n";
	cout << "Name: " << name << "\r\n";
	cout << "Department: " << department << "\r\n";
	cout << "level: " << level << "\r\n";
	cout << "Assigned mentor's IDs: \r\n";
	for (int i = 0; i < mentee.size(); i++){
		int pos = mentee[i];
		cout << " | " << pos << " | " << "\r\n";
	}
}

string Faculty::ToString(){
	stringstream s;
	string sep = " ";
	s << identification << sep << name << sep << level << sep << department << sep << title << sep << mentee.size() << sep;
	
	for(int i = 0; i < mentee.size(); i++){
		s << mentee[i] << sep;
	}
	s << '\n';
	string result = s.str();
	return result;
}

bool Faculty::operator == (const Faculty &other){
	return this->identification == other.identification;
}

bool Faculty::operator != (const Faculty &other){
	return this->identification != other.identification;
}

bool Faculty::operator <  (const Faculty &other){
	return this->identification < other.identification;
}

bool Faculty::operator >  (const Faculty &other){
	return this->identification > other.identification;
}

bool Faculty::operator == (const int ID){
	return this->identification == ID;
}

bool Faculty::operator != (const int ID){
	return this->identification != ID;
}

bool Faculty::operator < (const int ID){
	return this->identification < ID;
}

bool Faculty::operator > (const int ID){
	return this->identification > ID;
}