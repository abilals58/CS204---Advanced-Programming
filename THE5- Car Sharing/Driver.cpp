#include <iostream>
#include <string>
#include "Car.h"
// Ahmet Bilal Yildiz
#include "Driver.h"

using namespace std;

// constructor

Driver::Driver(Car& s_car, double budg)
	:sharedCar(s_car) , budget(budg) 
{}

// member functions

void Driver::drive(int t_distance){
	// updating the total distance
	sharedCar.distance() += t_distance;

	// updating the fuel
	// reducing the fuel level 0.25$ per km

	sharedCar.fuel() -= (t_distance * 0.25);

}

void Driver::repairCar(string accidentType){

	if(accidentType == "SMALL"){
		// displaying a message
		cout << "50$ is reduced from the driver's budget because of the SMALL accident" << endl;
		budget -= 50;
		sharedCar.insure() += (sharedCar.insure() * 0.05);

	}
	else if(accidentType == "MEDIUM"){
		// displaying a message
		cout << "150$ is reduced from the driver's budget because of the MEDIUM accident" << endl;
		budget -= 150;
		sharedCar.insure() += (sharedCar.insure() * 0.1);
	}
	else { // if accident type is LARGE
		// displaying a message
		cout << "300$ is reduced from the driver's budget because of the LARGE accident" << endl;
		budget -= 300;
		sharedCar.insure() += (sharedCar.insure() * 0.2);
	}

	cout << "Yearly insurance fee is increased to " << sharedCar.insure() <<" because of the " << accidentType <<" accident" << endl; 

}

void Driver::display(){

	cout << "Driver Budget: " << budget <<  endl;

}

void Driver::fullFuel(){
	// decreasing the budget
	double fuel_cost = sharedCar.max_fuel() - sharedCar.fuel();
	budget -= fuel_cost;

	// updating the fuel_level 
	sharedCar.fuel() = sharedCar.max_fuel();

	//displaying a message
	cout << endl;
	cout << "Fuel is full" << endl;
	cout << endl;
}