// Ahmet Bilal Yildiz
#ifndef Car_H
#define Car_H

using namespace std;

class Car {

private:

	double fuel_level; // fuel level of the car
	double fuel_max; // maximum fuel level of the car (will be used in fullfuel)
	double insurance_fee; // insurance fee (initialized with 1000$)
	int total_distance; // total distance that car has travelled (initialized with 5000km)

public:
	// constructor
	Car(double, double, int);

	// member funtions

	void display(); // displays the car info(privates)

	// helpers (used in the driver class member functions)
	double max_fuel(); // it returns the max fuel level
	double& fuel(); // it returns the reference of fuel level 
	double& insure(); // it returns the reference of insurance level
	int& distance(); // it returns the references of total distance

};


#endif
