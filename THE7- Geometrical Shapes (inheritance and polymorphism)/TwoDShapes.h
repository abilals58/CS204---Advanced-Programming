#ifndef TwoDShapes_H
#define TwoDShapes_H

#include "Shape.h"
using namespace std;

/*****************TwoDShape class************/

class TwoDShape: public shape // TwoDShape class is the base class for rectangle and publicly inherits the shape class
{

public:

	TwoDShape(string);  // constructor
	virtual float volume(); // virtual volume function that returns the volume as 0 for TwoDShape objects

};

/*****************rectangle class************/

class rectangle :public TwoDShape // rectangle class publicly inherits the TwoDShape class
{
private:

	float width;  // private variable width for rectangle objects
	float length;// private variable length for rectangle objects

public:

	rectangle(float, float, string); // constructor

	virtual float perimeter(); // virtual perimeter function that calculates the perimeter of the rectangles within a propar way
	virtual float area(); // vitual area function that calculates area of the rectangles in a proper way

};

#endif