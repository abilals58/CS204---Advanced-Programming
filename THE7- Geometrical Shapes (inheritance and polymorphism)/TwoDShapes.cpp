#include <iostream>
#include <string>
#include "TwoDShapes.h"

using namespace std;

/*****************TwoDShape class************/

TwoDShape::TwoDShape(string name):shape(name) // constructor
{
}

float TwoDShape::volume(){ // returns the volume for TwoDShape objects 0

	return 0;
}

/*****************rectangle class************/

rectangle::rectangle(float w, float l,string name):TwoDShape(name){ // constructor

	width = w;
	length = l;
}

float rectangle::perimeter(){ // virtual perimeter function that calculates the perimeter of the rectangles within a propar way

	return 2 * (width+ length);

}

float rectangle::area(){ // vitual area function that calculates area of the rectangles in a proper way

	return width * length;
}