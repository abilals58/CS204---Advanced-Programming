#ifndef Shape_H
#define Shape_H

using namespace std;

class shape // shape class is the base class of other classes which will be inherited from TwoDShapes and ThreeDshapes classes
{

protected: 
	string myName; // name of the shape object

public:

	shape(string); // constructor

	virtual float perimeter() = 0; // peirmeter function of shape
	virtual float area() = 0;	// area function for shape
	virtual float volume() = 0;	// colume function for shape
	string getName(); // function that returns the name of the shape object


};

#endif