// Ahmet Bilal  Yildiz

#include<iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "BusLib.h" // BusLib.h is the library of operations which has definitions of structs and storage class whose private is the head and publics are the operations which are used in the main cpp;

using namespace std;

//functions
void processMainMenu(); // it process the main menu, calls functions due to the user chooses;
void printMainMenu(); // it prints the main menu;
bool consistencyCheck(); // it checks the consistancy of doubly linked list;

// global variables that will be used in the functions;
busLine * head = NULL;
storage mydata(head);
int main(){
	// opening the file and stroing the data;
	string filename = "busLines.txt";
	ifstream file;
	string lines;
	file.open(filename.c_str());

	busLine* b_line_tail = NULL;
	while(getline(file,lines)){
		istringstream info(lines);
		string b_line, b_stop;
		info >> b_line;
		b_line = b_line.substr(0, b_line.size()-1); // not include the ":";

		busStop* b_stop_head = NULL;
		busStop* b_stop_tail = NULL;
		while(info >> b_stop){
			// forming the doubly linked list of busStops
			mydata.add_stop(b_stop_head, b_stop_tail, b_stop);
			
		}
		// forming the linked list of busLines
		mydata.add_line(b_line_tail, b_line, b_stop_head);
	}
	file.close();
	// processing the main menu;
	processMainMenu();




	return 0;
}


void processMainMenu() {
	char input;
	do
	{
		if(!consistencyCheck()) {
		cout << "There are inconsistencies. Exit." << endl;
		return;
		}
		printMainMenu();
		cout << "Please enter your option " << endl;
		cin >> input;
		switch (input) {
			case '0':
			cout << "Thanks for using our program" << endl;
			// deleting the dynamicaly allocated memory from the heap;
			mydata.DeleteAll();
			return;
			case '1':
				mydata.printBusLines();
				break;
			case '2':
				mydata.addBusLine();
				break;
			case '3':
				mydata.addBusStop();
				break;
			case '4':
				mydata.deleteBusLine();
				break;
			case '5':
				mydata.deleteBusStop();
				break;
			case '6':
				mydata.pathfinder();
				break;
			default:
			cout << "Invalid option: please enter again" << endl;
		} //switch
	} while(true);
}//processMainMenu

void printMainMenu() {
	cout << endl;
	cout <<"I***********************************************I"<<endl
	<<"I 0 - EXIT PROGRAM I"<<endl
	<<"I 1 - PRINT LINES I"<<endl
	<<"I 2 - ADD BUS LINE I"<<endl
	<<"I 3 - ADD BUS STOP I"<<endl
	<<"I 4 - DELETE BUS LINE I"<<endl
	<<"I 5 - DELETE BUS STOP I"<<endl
	<<"I 6 - PATH FINDER I"<<endl
	<<"I***********************************************I"<<endl
	<<">>";
	cout << endl;
}

bool consistencyCheck() {
	busLine* currBL = head; //a global variable
	while(currBL) {
		busStop* currBS = currBL->busStops;
		while(currBS) {
			busStop* rightBS = currBS->right;
			if(rightBS && rightBS->left != currBS) {
				cout << "Inconsistency for " << currBL->busLineName << " " << currBS->busStopName << endl;
				return false;
			}
			currBS = currBS->right;
		}
		currBL = currBL->next;
	}
	return true;
}

