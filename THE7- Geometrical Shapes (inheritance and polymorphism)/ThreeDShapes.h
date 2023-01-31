#ifndef ThreeDShapes_H
#define ThreeDShapes_H

#include "Shape.h"
using namespace std;


/*****************ThreeDShape class************/

class ThreeDShape: public shape // ThreeDShape class is a base class for box and it publicly inherits the shape class 
{

public:

	ThreeDShape(string); // constructor
	virtual float perimeter(); // virtual perimeter function that returns perimeter 0 for ThreeDShape objects

};

/*****************box class************/

class box :public ThreeDShape // box class publicly inherits the ThreeDShape object
{

private:

	float width; // private variable width for box object
	float length; // private variable length for box object
	float height; // private variable height for box object

public:

	box(float, float, float, string); // constructor

	virtual float area(); // virtual area function that calculates area of box in a propar way
	virtual float volume(); // virtual volume function that calculates area of box in a propar way


};

#endif