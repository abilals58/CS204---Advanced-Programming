#include <iostream>
#include <string>
#include "Shape.h"

using namespace std;

// constructor

shape::shape(string name){
	myName = name;
}

// member functions

string shape::getName(){ // it returns the name of the shape

	return myName;
}


