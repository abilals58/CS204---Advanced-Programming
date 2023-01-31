// Ahmet Bilal Yildiz
#ifndef Driver_H
#define Driver_H

using namespace std;

class Driver{

private:
	Car& sharedCar;
	double budget; // budgets of drivers(initialize with 1000$)

public:
	// constructor
	Driver(Car&, double); // gets shared car, and budget (initially 1000$)
	// member functions

	void drive (int); // it drives the car given km and updates the total distance and fuel level
	void repairCar(string); // it repairs the car depending on given accident type and update the budget and insurance level
	void display(); // it displays the driver budget
	void fullFuel(); // it full the fuel and update the budget

};


#endif
