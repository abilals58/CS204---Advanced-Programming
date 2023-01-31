#include <iostream>
#include <string>
#include <vector>
#include "BusLib.h"

using namespace std;

// This .cpp file is a hybrid approach which consists of the member functions of storage class and non-member(helper) functions which are used in the member functions.

// non-member functions (only used in this cpp file)
bool in_lines(busLine * line_head, string b_line); // this function checks whether the given line_name is in the line_list or not;
bool in_stops(busStop* stop_head, string b_stop_name); // this function checks whether the given stop_name in a busline or not;
bool in_vector(vector<string> vector, string stop_name); // this function checks whether the given stop_name in the vector or not;
void print_line(busLine *b_line); // this function prints a busLine with its stops;
void print_bus_lines(busLine *head); // this function prints all busLines meaningly the whole data;
busLine* find_busline(busLine * head, string line_name); // this function returns a specific busLine in the busLine_list;
busStop* find_busstop(busStop* stop_head, string stop_name); // this function returns a specific busstop in a busLine doubly linked list;
// functions used while solving bonus;
void bonusPath(string stop1, string stop2, busLine* head); // it prints a path with an interchange;
bool onleft(busStop * head, busStop* stop, string stop3); // returns true if stop2 is on the left of stop3


// member functions 
void storage::add_stop(busStop *& stop_head, busStop *& tail, string stop_name){;

	busStop *temp;
	temp = new busStop(stop_name); 

	if(stop_head == NULL){ // adding the first element;
		temp->right = stop_head;
		stop_head = temp;
		tail = temp;
	}
	else{

		temp->right = tail->right;
		temp->left = tail;
		tail->right = temp;
		tail = temp;
	}
}

void storage::add_line(busLine *& tail, string line_name, busStop* stops){
	busLine *temp;
	temp = new busLine(line_name,stops);

	if(head == NULL){ // adding the first element;
		temp->next = head;
		head = temp;
		tail = temp;
	}
	else{
		temp->next = tail->next;
		tail->next = temp;
		tail = temp;
	}
}

void storage::printBusLines(){
	
	print_bus_lines(head);
}

void storage::addBusLine(){
	string busline_name;
	cout << "Enter the name of the new bus line (0 for exit to main menu)." << endl;
	cin >> busline_name;
	if (busline_name == "0"){
		// return the main menu
	}
	else{ 
		

		while(in_lines(head, busline_name)){
			cout << "Bus line already exists: enter a new one (0 for exit)" << endl;
			cin >> busline_name;
			if(busline_name == "0"){
				// return main menu
				break;
			}
		}
		if(busline_name != "0"){
			
			// if busline not in the list, add new busline;
			string b_stop;
			vector<string> v_stops;
			// getting the stops names
			cout << "Enter the name of the next bus stop (enter 0 to complete)" << endl;
			cin >> b_stop;
			while(b_stop != "0"){
				if(!in_vector(v_stops, b_stop)){
					v_stops.push_back(b_stop);

				}
				else{
					cout << "Bus stop already exists in the line" << endl;
			
				}
				cout << "Enter the name of the next bus stop (enter 0 to complete)" << endl;
				cin >> b_stop;
			
			}
			if(v_stops.size() == 0){
				cout <<"You are not allowed to add an empty bus line"<< endl;
			
			}
			else{
				// printing the bus line that user wants to add;
				cout << "The bus line information is shown below" << endl;
				cout << busline_name << ": ";
				for(int i = 0; i < v_stops.size()-1; i++){
					cout << v_stops[i] << " <-> ";
				}
				cout << v_stops[v_stops.size()-1] << endl;
				// confirmation
				string confirm;
				cout << "Are you sure? Enter (y/Y) for yes (n/N) for no?" << endl;
				cin>> confirm;
				if(confirm == "y" || confirm == "Y"){
					//add the bus line to the list;
					busLine * temp = new busLine(busline_name);
					busStop * stop, *tail;
					for(int i = 0; i< v_stops.size(); i++){
						stop = new busStop(v_stops[i]);
						if(temp->busStops == NULL){
							// adding the first busStop;
							stop->right = temp->busStops;
							temp->busStops = stop;
							tail = temp->busStops;
						}
						else{
							stop->right = tail->right;
							stop->left = tail;
							tail->right = stop;
							tail = stop;
						}
					}
					// adding new busline to the beginning of the list;
					temp->next = head;
					head = temp;
					// printing the busline;
					print_bus_lines(head);
				}
			}
		}
	}
}

void storage::addBusStop(){
	string line_name;
	cout <<"Enter the name of the bus line to insert a new bus stop (0 for main menu)" << endl;
	cin >> line_name;

	if(line_name == "0"){
		// return to the main;
	}
	else if (!in_lines(head, line_name)){
		cout << "Bus line cannot be found. Going back to previous menu." << endl;
	}
	else{ // if a valid busLine entered by the user;
		// showing the busLine info;
		cout << "The bus line information is shown below" << endl;
		// finding the busLine
		busLine* b_line = find_busline(head, line_name);
		print_line(b_line);

		string stop_name;
		cout << "Enter the name of the new bus stop" << endl;
		cin >> stop_name;
		if(in_stops(b_line->busStops, stop_name)){
			cout << "Bus stop already exists. Going back to previous menu." << endl;
		}
		else{
			string pre_stop_name;
			cout << "Enter the name of the previous bus stop to put the new one after it (0 to put the new one as the first bus stop)" << endl;
			cin >> pre_stop_name;
			if (pre_stop_name == "0"){
				busStop * temp = new busStop(stop_name);
				//adding the new element to the beginning;
				temp->right = b_line->busStops;
				temp->left = b_line->busStops->left;
				b_line->busStops->left = temp;
				b_line->busStops = temp;
				print_bus_lines(head);
			}
			else{

				while(! in_stops(b_line->busStops, pre_stop_name)){
					cout << "Bus stop does not exist. Typo? Enter again (0 for main menu)" << endl;
					cin >> pre_stop_name;
					if(pre_stop_name == "0"){
						// return to the previous menu
						break;
					}
				}
				if(pre_stop_name != "0"){
					// adding the new stop;
					busStop * temp = new busStop(stop_name);
					busStop * pre_stop = find_busstop(b_line->busStops, pre_stop_name);
					// finding the pre_stop_name in the list;
					if(pre_stop->right == NULL){
						// adding the element to the end of the list;
						temp->right = pre_stop->right;
						temp->left = pre_stop;
						pre_stop->right = temp;

					}
					else{
						// adding element to the middle;
						temp->right = pre_stop->right;
						temp->left = pre_stop;
						pre_stop->right->left = temp;
						pre_stop->right = temp;
					
					}
					print_bus_lines(head);
				}
			}
		}
	
	}
}

void storage::deleteBusLine(){
	string line_name;
	cout << "Enter the name of the bus line to delete" << endl;
	cin >> line_name;
	if (! in_lines(head,line_name)){
		cout << "Bus line cannot be found. Going back to the previous (main) menu." << endl;
		// go to previos menu
	
	}
	else{
		// delete the busLine
		
		busLine *delete_line = find_busline(head, line_name);
		busLine *temp_line = NULL;
		busLine * before = NULL;

		// deleting all the stops in that line;
		busStop * curr_stop = delete_line->busStops;
		busStop* temp;
		while(curr_stop != NULL){
			temp = curr_stop->right;
			delete curr_stop;
			curr_stop = temp;
		}
		// deleting the busLine
		
		if(delete_line == head){
			// deleting the first element
			temp_line = head->next;
			delete head;
			head = temp_line;
		}
		else{
			// finding before element of the deleting element
			busLine *curr_line = head;
			while(curr_line != NULL){
				if(curr_line->next->busLineName == line_name){
					before =curr_line;
					break;
				}

				curr_line = curr_line->next;
			}
			//deleting the elements different than first element
			before->next = delete_line->next;
			delete delete_line;
		}	
		
		print_bus_lines(head);	
	}	
}

void storage::deleteBusStop(){
	string line_name;
	cout << "Enter the name of the bus line to delete" << endl;
	cin >> line_name;
	if (! in_lines(head,line_name)){
		cout << "Bus line cannot be found. Going back to the previous (main) menu." << endl;
		// go to previos menu
	
	}
	else{
		// showing the busLine info;
		// finding busline due to the given name
		busLine * b_line = find_busline(head, line_name);

		// printing this busline
		print_line(b_line);

		// getting stop_name to delete
		string stop_name;
		cout << "Enter the name of the bus stop to delete (0 for main menu)" << endl;
		cin >> stop_name;
		if (stop_name == "0"){
			cout << "Going back to the menu" << endl;
			// return to main menu	
		}
		else{
			while(!in_stops(b_line->busStops, stop_name)){
				cout << "Bus stop cannot be found. Enter the name of the bus stop to delete (0 for main menu)" << endl;
				cin >> stop_name;
				if(stop_name == "0"){
					cout << "Going back to the menu" << endl;
					break;
				}
			}
			if(stop_name != "0"){
				// deleting the stop;
				busStop * delete_stop = find_busstop(b_line->busStops, stop_name);
				busStop * before = delete_stop->left;
				busStop * after = delete_stop->right;
				if(before == NULL){
					// deleting the first element
					b_line->busStops = delete_stop->right;
					b_line->busStops->left = delete_stop->left;
					delete delete_stop;
				}
				else if(after == NULL){
					// deleting the last element
					before->right = after;
					delete delete_stop;
				}
				else{
					// deleting elements different than first element;
					before->right = after;
					after->left = before;
					delete delete_stop;
				}
				print_bus_lines(head);
			}
		
		}

	}
}

void storage::pathfinder(){
	string stop1, stop2;
	cout << "Where are you now?" << endl;
	cin >> stop1;
	cout << "Where do you want to go?" << endl;
	cin >> stop2;

	// checking whether there is stop1 or stop2 in the lines;
	busLine * curr_line = head;
	bool check1 = false;
	bool check2 = false;
	while(curr_line != NULL){
		if(in_stops(curr_line->busStops, stop1)){
			check1 = true;
			break;
		}
		curr_line = curr_line->next;
	}
	curr_line = head;
	while(curr_line != NULL){
		if(in_stops(curr_line->busStops, stop2)){
			check2 = true;
			break;
		}
		curr_line = curr_line->next;
	}
	if(!(check1 && check2)){ // if at least one of the stops does not in the list, give an error message;
		cout << "Bus stop does not exist in the table. Going back to previous menu." << endl;
	
	}
	else if(stop1 == stop2){ // if two stops are same, give a message; 
		cout << "You are already at that bus stop. Going back to the previous menu." << endl;
	
	}
	else{
		// searching for the path;
		curr_line = head;
		while(curr_line != NULL){
			if(in_stops(curr_line->busStops, stop1)){
				if(in_stops(curr_line->busStops, stop2)){
					// printing the path
					busStop *b_stop1 = find_busstop(curr_line->busStops, stop1); 
					busStop *b_stop2 = find_busstop(curr_line->busStops, stop2);

					// finding the path
					bool isleft = true;
					busStop * temp_stop = b_stop1;
					while(temp_stop != NULL){
						if(temp_stop->busStopName == stop2){
							isleft = false;
						}
						temp_stop = temp_stop->right;
					}

					if(isleft){
						//printing the path
						cout << "You can go there by " << curr_line->busLineName << ": "; 
						while(b_stop1 != b_stop2){
							cout << b_stop1->busStopName << "->";
							b_stop1 = b_stop1->left;
						}
						cout << b_stop1->busStopName << endl;
					}
					else{
						cout << "You can go there by " << curr_line->busLineName << ": ";
						while(b_stop1 != b_stop2){
							cout << b_stop1->busStopName << "->";
							b_stop1 = b_stop1->right;
						}
						cout << b_stop1->busStopName << endl;
					}

				}
				else{
					bonusPath(stop1, stop2, head);
				}
			}
			curr_line = curr_line->next;
		}
	
	}
}
// BONUS//
void bonusPath(string stop1, string stop2, busLine* head){
	busLine * curr_line = head;
	busLine* b_line1; 
	busLine* b_line2; 
	// find the line of stop1
	while(curr_line != NULL){
		if(in_stops(curr_line->busStops, stop1)){
			b_line1 = curr_line;
			break;
		}
		curr_line = curr_line->next;
	}

	// find the line of stop2
	curr_line = head;
	while(curr_line != NULL){
		if(in_stops(curr_line->busStops, stop2)){
			b_line2 = curr_line;
			break;
		}
		curr_line = curr_line->next;
	}
	// finding the stop3 as a interchange stop
	busStop* stop1_head = b_line1->busStops;
	busStop* stop2_head = b_line2->busStops;
	string stop3 = "no_stop";
	while(stop1_head != NULL){
		stop2_head = b_line2->busStops;
		while(stop2_head != NULL){
			if(stop1_head->busStopName == stop2_head->busStopName){
				stop3 = stop1_head->busStopName;
				break;
			}
		
			stop2_head = stop2_head->right;
		}
	
		stop1_head = stop1_head->right;
	}
	// error message if there is no path
	if (stop3 == "no_stop"){
		cout << "Sorry no path from " << stop1 << " to " << stop2 << "could be found." << endl;
	
	}
	else{

		// finding the busstops
		busStop *b_stop1 = find_busstop(b_line1->busStops, stop1);
		busStop * b_stop2 = find_busstop(b_line2->busStops, stop2);
		busStop * b_stop3 = find_busstop(b_line2->busStops, stop3);
		// printing the route

		if(onleft(stop1_head, b_stop1, stop3)){
			cout << "You can go there by " << endl << b_line1->busLineName << ": ";
			while(b_stop1->busStopName != stop3){
				cout << b_stop1->busStopName << "->";
				b_stop1 = b_stop1->right;
			}
			cout << b_stop1->busStopName << endl;
			if(onleft(stop2_head, b_stop2, stop3)){
				cout << b_line2->busLineName << ": ";
				while(b_stop3->busStopName != stop2){
					cout << b_stop3->busStopName << "->";
					b_stop3 = b_stop3->left;
				}
				cout << b_stop3->busStopName << endl;
			}
			else{
				cout << b_line2->busLineName << ": ";
				while(b_stop3->busStopName != stop2){
					cout << b_stop3->busStopName << "->";
					b_stop3 = b_stop3->right;
				}
				cout << b_stop3->busStopName << endl;
			}
		}
		else{
			cout << "You can go there by " << endl << b_line1->busLineName << ": ";
			while(b_stop1->busStopName != stop3){
				cout << b_stop1->busStopName << "->";
				b_stop1 = b_stop1->left;
			}
			cout << b_stop1->busStopName << endl;
			if(onleft(stop2_head, b_stop2, stop3)){
				cout << b_line2->busLineName << ": ";
				while(b_stop3->busStopName != stop2){
					cout << b_stop3->busStopName << "->";
					b_stop3 = b_stop3->left;
				}
				cout << b_stop3->busStopName << endl;
			}
			else{
				cout << b_line2->busLineName << ": ";
				while(b_stop3->busStopName != stop2){
					cout << b_stop3->busStopName << "->";
					b_stop3 = b_stop3->right;
				}
				cout << b_stop3->busStopName << endl;
			}
	
		}
	}


}

void storage::DeleteAll(){
	busLine* ptr = head;
	while(head!= NULL){
		ptr = head->next;
		// first dleeting the whole busStops in that line;
		busStop* ptr2 = head->busStops;
		busStop* tempptr2;
		while(ptr2!= NULL){
			tempptr2 = ptr2->right;
			delete ptr2;
			ptr2 = tempptr2;
		
		}
		// deleting the busLine head(current busLine);
		delete head;
		head = ptr;
	}
}


// non_memebr(helper) functions
bool in_lines(busLine * line_head, string b_line){
	while (line_head != NULL){
		if(line_head->busLineName == b_line){
			return true;
		}
		line_head = line_head->next;
	}
	return false;
}

bool in_stops(busStop* stop_head, string b_stop_name){
	while(stop_head != NULL){
		if(stop_head->busStopName == b_stop_name){
			return true;
		}
		stop_head = stop_head->right;
	}
	return false;

}

bool in_vector(vector<string> vector, string stop_name){
		for(int i = 0; i<vector.size(); i++ ){
			if(vector[i] == stop_name){
				return true;
			}
		
		}
		return false;
}

void print_line(busLine * b_line){
	cout << b_line->busLineName << ": ";
	busStop * b_stop_head = b_line->busStops;
	while(b_stop_head->right != NULL){
		cout << b_stop_head->busStopName << " <-> ";
		b_stop_head = b_stop_head->right;
	}
	cout << b_stop_head->busStopName << endl;
}

void print_bus_lines(busLine* head){
	cout << endl;
	while(head != NULL){
		print_line(head);
		head = head->next;
	}
}

busLine* find_busline(busLine * head, string line_name){
	while(head != NULL){
		if(head->busLineName == line_name){
			return head;
		}
		head = head->next;
	}
}

busStop* find_busstop(busStop* stop_head, string stop_name){
	while(stop_head != NULL){
		if(stop_head->busStopName == stop_name){
			return stop_head;
		}
		stop_head = stop_head->right;
	}
}

bool onleft(busStop * head, busStop* stop, string stop3){ // returns true if stop is on the left of stop3
	

	//checking whether stop3 is on left or not
	while(stop != NULL){
		if(stop->busStopName == stop3){
			return true;
		}
		stop = stop->right;
	}
	return false;
}

