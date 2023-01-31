#include <iostream>
#include <string>
#include "ThreeDShapes.h"

using namespace std;

/*****************ThreeDShape class************/
ThreeDShape::ThreeDShape(string name):shape(name) // constructor
{
}

float ThreeDShape::perimeter() // it returns perimeter 0 for ThreeDShapes objects
{
	return 0;
}

/*****************box class************/

box::box(float w, float l, float h, string name) :ThreeDShape(name){ // constructor

	width = w;
	length = l;
	height = h;

}

float box::area(){ // virtual area function that calculates area of box in a propar way

	return 2*(width*length+width*height+length*height);
}

float box::volume(){ // virtual volume function that calculates area of box in a propar way

	return width * length * height;
}
