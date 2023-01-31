#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "strutils.h"
using namespace std;

struct courseNode{

	string courseCode, courseName;
	vector<int> studentsAttendingIDs;
	courseNode * next;

	courseNode::courseNode()
	{}; 

};
// check functions;
bool in_list(courseNode *&head, string c_code); // in_list() checks whether the courseCode in the linked list or not;
bool in_vector(vector<int> vector, int ID); // in vector checks whether ID in the vector or not;

// print functions;
void print_node(courseNode* node); // it prints one node in the suitable format;
void print_list(courseNode* node); // it prints whole linked list;

// add functions;
void Add_Vector(vector<int> &vector, int ID); // it adds ID to the vector in a sorted manner;
void add_new_node(courseNode*& head, courseNode*& temp); // it adds temp(as new node) to the linked list in a sorted manner;
void ADD(courseNode *&head, courseNode *&temp, string c_code, string c_name,int ID);// it do the ADD operation;

// drop functions;
void Drop_Vector(vector<int> &vector, int ID); // it deletes the ID from the vector in a sorted manner;
void DROP(courseNode*& head, courseNode*& temp,string c_code,string c_name, int ID); // it do the DROP operation;

// delete function;
void Delete(courseNode*& head); // it deletes the linked list(dynamically allocated memory) from the heap;


int main(){
	// getting filename;
	string filename;
	cout << "Please enter file name: ";
	cin >> filename;

	// opening file and intialize the program;
	ifstream file;
	string line;

	courseNode *head = NULL, *temp = NULL; 

	file.open(filename.c_str());
	while(getline(file, line)){
		istringstream info(line);
		string c_code, c_name;
		int ID;
		info >> c_code >> c_name >> ID;
	
		if(head == NULL){ // adding the first node to the linked list without any check;
			//forming temp
			temp = new courseNode();
			temp->courseCode = c_code;
			temp->courseName = c_name;
			temp->studentsAttendingIDs.push_back(ID);
			temp->next = NULL;
			// adding temp to the linked list as the first element;
			temp->next = head;
			head = temp;
		
		}
		else if(in_list(head, c_code)){ // adding student ID  to the existing course;
			courseNode *pos = head;
			while(pos != NULL){
				if(pos->courseCode == c_code){
					if(! in_vector(pos->studentsAttendingIDs, ID)){ // add the new ID to the vector;
						Add_Vector(pos->studentsAttendingIDs, ID);
					}
				}
				pos = pos->next;
			}
		}
		else{ // adding new node;
			//forming temp
			temp = new courseNode();
			temp->courseCode = c_code;
			temp->courseName = c_name;
			temp->studentsAttendingIDs.push_back(ID);
			temp->next = NULL;

			add_new_node(head, temp);
		
		}
	
	}
	file.close();

	cout << "Successfully opened file " << filename << endl;
	cout << "The linked list is created. " << endl;
	cout << "The initial list is: " << endl;
	print_list(head);
	/////// ADD-DROP////////

	// displaying menu and getting option;
	cout << endl << "Please select one of the choices:" << endl << "1. Add to List" << endl <<  "2. Drop from List" << endl << "3. Display List" << endl << "4. Finish Add/Drop and Exit" << endl;
	int option;
	cin >> option;

	while(option != 4){
		if(option == 1){ //ADD
			string add_info;
			cout << "Give the student ID and the course names and course codes that he/she wants to add:" << endl;
			cin.ignore();
			getline(cin, add_info); // get user input as a line;

			istringstream info(add_info);
			string c_code, c_name, word;
			int ID;
			info >> c_code >> c_name;
			while(info >> word){

				if(char('0') <= int(word[0]) && int(word[0]) <= char('9')){ // if word is an ID;
					ID = atoi(word);
					ADD(head, temp, c_code, c_name, ID); // add operation;

				}
				else{
					c_code = word;
					info >> word;
					c_name = word;
			
				}
			}
		}
		else if(option == 2){ // DROP
			string drop_info;
			cout << "Give the student ID and the course names and course codes that he/she wants to drop:" << endl;
			cin.ignore();
			getline(cin, drop_info); // get user input as a line;
		
			istringstream info(drop_info);
			string c_code, c_name, word;
			int ID;
			info >> c_code >> c_name;
			while(info >> word){

				if(int('0') <= int(word[0]) && int(word[0]) <= int('9')){ // if word is an ID;
					ID = atoi(word);
					DROP(head, temp, c_code, c_name, ID); // DROP operation;

				}
				else{
					c_code = word;
					info >> word;
					c_name = word;
			
				}
			}
		}
		else if(option == 3){ // printing the linked list;
			cout << "The current list of course and the students attending them:" << endl;
			print_list(head);
		
		}
	
		// displaying menu and getting option;
		cout << endl << "Please select one of the choices:" << endl << "1. Add to List" << endl <<  "2. Drop from List" << endl << "3. Display List" << endl << "4. Finish Add/Drop and Exit" << endl;
		cin >> option;
	}

	// out of the loop meaning that the option 4 is chosen;
	cout << "The add/drop period is finished. Printing the final list of courses and students attending them. " << endl;
	cout << "NOTE: Courses with less than 3 students will be closed this semester. " << endl;
	// printing the list with appropriate messages;
	courseNode *print = head;
	while(print != NULL){
		if(print->studentsAttendingIDs.size() < 3){
			// print_node() without ":";
			cout << print->courseCode << " " << print->courseName << " ";
			for(int i=0; i < print->studentsAttendingIDs.size(); i++){
				cout << print->studentsAttendingIDs[i] << " ";
			}
			cout << "-> This course will be closed" << endl;
		}
		else{
			print_node(print);
			cout << endl;
		}
		print = print->next;
	}
	// Deleting the dynamicaly allocated memory from the heap;
	Delete(head);

	system("Pause");
	return 0;
}

bool in_list(courseNode *&head, string c_code){
	courseNode *pos = head;
	while(pos != NULL){
		if(pos->courseCode == c_code){
			return true;
		}
		pos = pos->next;
	}
	return false;
}

bool in_vector(vector<int> vector, int ID){
	for(int i= 0; i < vector.size(); i++){
		if(ID == vector[i]){
			return true;
		}
	}
	return false;
}

void print_node(courseNode* node){
	cout << node->courseCode << " " << node->courseName << ": ";
	for(int i=0; i < node->studentsAttendingIDs.size(); i++){
		cout << node->studentsAttendingIDs[i] << " ";
	}
}

void print_list(courseNode* node){
	while(node != NULL){
		print_node(node);
		cout << endl;
		node = node->next;
	}
}

void Add_Vector(vector<int> &vector, int ID){
	// finding index to add new ID;
	int add_index = -1; // it is not change if ID is the biggest;
	for(int i= 0; i < vector.size(); i++){
		if(ID < vector[i]){
			add_index = i;
			break;
		}
	}
	// adding new ID to add_index;
	if(add_index == -1){
		vector.push_back(ID); // ID added at the end of the vector;
	}
	else{
		vector.push_back(ID);
		for(int i = vector.size()-2; i >= add_index; i--){
			vector[i+1] = vector[i];
		}
		vector[add_index] = ID;
	}
}

void add_new_node(courseNode*& head, courseNode*& temp){

	if(temp->courseName < head->courseName){ // adding new node to the beginning of the linked list;
		temp->next = head;
		head = temp;
	}
	else{
		courseNode *pos = head;
		while(pos->next != NULL){// adding new node to the middle parts of the linked list;
			if(temp->courseName > pos->courseName && temp->courseName < pos->next->courseName){
				temp->next = pos->next;
				pos->next = temp;
				break;
			}
			pos = pos->next;
		}
		if(pos->next == NULL){ // adding new node to the end of the linked list;
			temp->next = pos-> next;
			pos->next = temp;
		}
	}
}

void ADD(courseNode*& head, courseNode*& temp,string c_code,string c_name, int ID){
	if(in_list(head, c_code)){
		courseNode *pos = head;
		while(pos != NULL){
			if(pos->courseCode == c_code){
				if(! in_vector(pos->studentsAttendingIDs, ID)){ // add the new ID to the vector;
					Add_Vector(pos->studentsAttendingIDs, ID);
					cout << "Student with id " << ID << " is enrolled to " << c_code << "." << endl;
					break;
				}
				else{ // if the ID already in the vectory;
					cout <<"Student with id " << ID << " already is enrolled to " << c_code << ". No action taken." << endl;
					break;
				}
			}
		pos = pos->next;
		}
					
	}
	else{ // adding new node;
		temp = new courseNode();
		temp->courseCode = c_code;
		temp->courseName = c_name;
		temp->studentsAttendingIDs.push_back(ID);
		temp->next = NULL;
						
		add_new_node(head, temp);
		cout << c_code << " does not exist in the list of Courses. It is added up." << endl;
		cout << "Student with id " << ID << " is enrolled to " << c_code << "." << endl;

	}
}

void Drop_Vector(vector<int> &vector, int ID){
	// finding the index;
	int myindex;
	for (int i =0; i < vector.size(); i++){
		if(vector[i] == ID){
			myindex = i;
			break;
		}
	}
	// deleting to the vector;
	if(myindex == vector.size()-1){ // deleting the last element of the vector;
		vector.pop_back();
	}
	else{
		for(int i = myindex; i < vector.size()-1; i++){
			vector[i] = vector[i+1];
		}
		vector.pop_back();
	}
}

void DROP(courseNode*& head, courseNode*& temp,string c_code,string c_name, int ID){
	if(in_list(head,c_code)){
		courseNode *pos = head;
		while(pos != NULL){
			if(pos->courseCode == c_code){
				if(in_vector(pos->studentsAttendingIDs, ID)){
					Drop_Vector(pos->studentsAttendingIDs, ID);
					cout << "Student with id " << ID << " has dropped " << c_code << "." << endl;
					break;
				}
				else{
					cout << "Student with id " << ID <<" is not enrolled to "<< c_code << ", thus he can't drop that course." << endl;
					break;
				}
			}
			pos = pos->next;
		}
	}
	else{
		cout << "The " << c_code << " course is not in the list, thus student with id " << ID << " can’t be dropped." << endl;

	}

}

void Delete(courseNode*& head){
	courseNode *temp;
	while(head!= NULL){
		temp = head->next;
		delete head;
		head = temp;
	}
}

