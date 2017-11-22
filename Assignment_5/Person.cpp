#include "Person.h"
#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

Person::Person(){

}

Person::~Person(){
	
}

void Person::setValues(int id, string n, string l){
	identification = id;
	name = n;
	level = l;
}