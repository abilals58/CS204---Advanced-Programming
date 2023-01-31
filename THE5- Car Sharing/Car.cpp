// Ahmet Bilal Yildiz
#include <iostream>
#include "Car.h"

using namespace std;

// constructor

Car::Car(double fuel, double insurance, int distance){
	fuel_level = fuel;
	insurance_fee = insurance;
	total_distance = distance;
	fuel_max = fuel; // storing the max level of the fuel
}

// member fucntions

void Car::display(){
	// displaying the car info

	cout << "Fuel Level: " << fuel_level << endl
		<< "Insurance Fee: " << insurance_fee << endl
		<< "Total distance that the car has travelled: " << total_distance << endl;
}


// helper member functions Which are used in the Driver member functions 
double Car::max_fuel(){

	return fuel_max;
}

double& Car::fuel(){

	return fuel_level;
}

double& Car::insure(){

	return insurance_fee;
}

int& Car::distance(){

	return total_distance;

}
