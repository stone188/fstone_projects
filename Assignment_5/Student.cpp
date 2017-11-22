#include "Student.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <sstream>

using namespace std;

Student::Student(){
	identification = 0;
	name = "Unknown";
	level = "Unknown";
	mentor = 0;
	GPA = 0;
	major = "Unknown";
	assigned = 0;
}

Student::~Student(){
	
}

Student::Student(int me, double g, string ma){
	mentor = me;
	GPA = g;
	major = ma;
}

Student::Student(string dataRec){
	istringstream data(dataRec);
	data >> identification >> name >> level >> mentor >> GPA >> major >> assigned;
}

void Student::display(){
	cout << "\r\nStudent's ID: " << identification << "\r\n";
	cout << "Name: " << name << "\r\n";
	cout << "Major: " << major << "\r\n";
	cout << "year: " << level << "\r\n";
	cout << "Current GPA: " << GPA << "\r\n";
	cout << "Assigned mentor's ID: " << mentor << "\r\n";
}

string Student::ToString(){
	stringstream s;
	string sep = " ";
	s << identification << sep << name << sep << level << sep << mentor << sep << GPA << sep << major << sep << assigned << "\r\n";
	string result = s.str();
	return result;
}

bool Student::operator == (const Student &other){
	return this->identification == other.identification;
}

bool Student::operator != (const Student &other){
	return this->identification != other.identification;
}

bool Student::operator <  (const Student &other){
	return this->identification < other.identification;
}

bool Student::operator >  (const Student &other){
	return this->identification > other.identification;
}

bool Student::operator == (const int ID){
	return this->identification == ID;
}

bool Student::operator != (const int ID){
	return this->identification != ID;
}

bool Student::operator < (const int ID){
	return this->identification < ID;
}

bool Student::operator > (const int ID){
	return this->identification > ID;
}