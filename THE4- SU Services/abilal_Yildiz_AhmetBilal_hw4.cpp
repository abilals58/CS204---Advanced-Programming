// Ahmet Bilal Yildiz

// existing librarys and classes
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

// libraries created for this homework (their .h, and .cpp files are also uploeded.)
#include "DynamicAndStaticQueue.h" // this include both static queue class for instructors (StaticInstructorQueue), and  dynamic queue class for students (DynamicStudenQueue)
#include "SharedStack.h" // this is the class of shared stack

using namespace std;

struct command{ // this is the struct for commands including the info(define a, call function_1, print stack e.t.c) and pointer to another command which is usd in the linked list of commands
	string info;
	command* next;

	command(string i, command* n = NULL){
		info = i;
		next = n;
	}
};

struct service{ // this is the struct for services including the service name, a service pointer (to make a linked list of services), and pointer to a command (to form the data of linked list of linked lists)
	string name;
	service* right;
	command* commands;

	service(string n, service* ptr = NULL, command* c = NULL){
		name = n;
		right = ptr;
		commands = c;
	}
};

//global variables
service * service_head = NULL; // service head is a global varible which is the head of the data structure to reach all the data
StaticInstructorQueue instructorsQueue; // static queue for instructors request 
DynamicStudentQueue studentsQueue; // dynamic queue for student request
string functionName; // this is always the function name which is given by the user of the program(an instructor or student function info) 
SharedStack sharedStack; // shared stack is used while processing 
// functions
void add_service(service *&service_last, string &f_name, command *&c_head ); // it forms a linked list of services and adds new services to this linked list of linked lists
void add_command(command *&c_head , command *&c_last, string &word); // it forms a linked list of commands and adds new commands to it (the head of this command list is a component of a spesific service(function))
void print(); // it prints the whole data of the services and its commands
void processARequest(); // this function is taken from the homework document, and edited
void processARequest(string functionName); // this function is taken from the homework document, and edited

void addInstructorRequest(); // it takes and adds instructor request to the instructors queue
void addStudentRequest(); // it takes and adds student request to the students queue

bool in_service(); // it returns true if user given functionName is in the service list (the linked list of services), otherwise returns false
service* find_service(string function_name); // it returns the searched function which is in the service list

int main(){
	ifstream input;
	string option; // user choose y or n;
	string file_name; // user gives the filename
	string f_name, word; // variables to get file lines
	service* service_last; // the last element of the service linked list it is used while adding a new service to the list;
	cout << "If you want to open a service (function) defining file,\nthen press (Y/y) for 'yes', otherwise press any single key" << endl;
	cin >> option;

	while(option == "y" || option == "Y" ){
		cout << "Enter the input file name: ";
		cin >> file_name;
		input.open(file_name.c_str());
		if(input.fail()){ // if file cannot be opened, exiting to the program
			cout << file_name << " could not be opened, exiting to the program " << endl;
			exit(0);
		}
		// adding data of input file to the linked list data structure
		getline(input, f_name);
		f_name = f_name.substr(0, f_name.size()-1); // get rid of ":"
		//forming the command list
		command* c_head = NULL;
		command* c_last = NULL;
		while(getline(input, word)){
			word = word.substr(0, word.size()-1); // get rid of ";"
			add_command(c_head, c_last, word);
		}
		// adding the new service to the linked list with its command list
		add_service(service_last, f_name, c_head);
		// closing and clearing the fstream
		input.close();
		input.clear();
		// getting the option
		cout << "Do you want to open another service defining file?\nPress (Y/y) for 'yes', otherwise press any single key" << endl;
		cin >> option;
	}
	// displaying the data;
	print();

	// processing the main menu // codes are taken from the homework document;

	while (true){
		cout << endl; cout<<"**********************************************************************"<<endl
			<<"**************** 0 - EXIT PROGRAM *************"<<endl
			<<"**************** 1 - ADD AN INSTRUCTOR SERVICE REQUEST *************"<<endl
			<<"**************** 2 - ADD A STUDENT SERVICE REQUEST *************"<<endl
			<<"**************** 3 - SERVE (PROCESS) A REQUEST *************"<<endl
			<<"**********************************************************************"<<endl;
			cout << endl; 
			int option;
			cout << "Pick an option from above (int number from 0 to 3): ";
			cin>>option;
			switch (option) { 
				case 0:
					cout<<"PROGRAM EXITING ... "<<endl;
					system("pause");
					exit(0); 
				case 1:
					addInstructorRequest();
					break;
				case 2: 
					addStudentRequest();
					break;
				case 3:
					processARequest();
					break;
				default:
					cout<<"INVALID OPTION!!! Try again"<<endl;
			}//switch 
	}//while (true)

	return 0;
}


void add_service(service *&service_last, string &f_name, command *&c_head ){
	service * temp = new service(f_name, NULL, c_head);
	if(service_head == NULL){ // adding the first service
		service_head = temp;
		service_last = service_head;
	}
	else{ // adding other services
		service_last->right = temp;
		service_last = service_last->right;
	}
}

void add_command(command *&c_head , command *&c_last, string &word){
	command* temp = new command(word, NULL);
	if(c_head == NULL){ // adding the first command
		c_head = temp;
		c_last = c_head;
	}
	else{ // adding other commands
		c_last->next = temp;
		c_last = c_last->next;
	}
}

void print(){

	cout << "------------------------------------------------------------------"<< endl;
	cout << "PRINTING AVAILABLE SERVICES (FUNCTIONS) TO BE CHOSEN FROM THE USER"<< endl;
	cout << "------------------------------------------------------------------"<< endl;

	service * head = service_head;
	while(head!= NULL){
		cout << head->name <<":" << endl;
		command* c_head = head->commands;
		while(c_head->next != NULL){
			cout << c_head->info << ", ";

			c_head = c_head->next;
		}
		cout << c_head->info << "." << endl;
		
		head = head->right;
	}
}

void processARequest(){

	if (!instructorsQueue.isEmpty()){
		
		//if instructors queue is not empty, process the next request 
		// display a message about operation
		cout << "Processing instructors queue..." << endl;
		instructor temp_inst;
		instructorsQueue.dequeue(temp_inst);
		functionName = temp_inst.f_name;
		// displaying processing info
		cout << "Processing prof." << temp_inst.name << "'s request (with ID " << temp_inst.ID << ") of service (function): " << endl << temp_inst.f_name << endl;
		processARequest(functionName);
		// After processing done displaying that stack is empty
		cout << "The stack is empty." << endl;
		cout << "GOING BACK TO THE MAIN MENU" << endl;

	}
	else if (!studentsQueue.isEmpty()){
	
		//if instructors queue is empty and student’s not,
		//then process the next student request

		// display a message about operation
		cout << "Processing students queue..." << endl;
		student temp_stu;
		studentsQueue.dequeue(temp_stu);
		functionName = temp_stu.f_name;

		// displaying processing info
		cout << "Processing " << temp_stu.name << "'s request (with ID " << temp_stu.ID << ") of service (function): " << endl << temp_stu.f_name << endl;
		processARequest(functionName);
		// After processing done displaying that stack is empty
		cout << "The stack is empty." << endl;
		cout << "GOING BACK TO THE MAIN MENU" << endl;
	}
	else{
	
		// otherwise… 
		cout<<"Both instructor's and student's queue is empty.\nNo request is processed."<<endl
			<<"GOING BACK TO MAIN MENU"<<endl;
	}
}

void processARequest(string functionName){
	// finding the function in the linked list;

	command * commands = find_service(functionName)->commands; 
	string current_command, value;

	while (commands != NULL){

		istringstream get(commands->info);
		get >> current_command >> value;
		StackNode temp(functionName, current_command, value);

		if(current_command =="define"){
			//process the define command     /// addd messages to those places
			sharedStack.push(temp);
		}
		else if (current_command =="call"){

			// … // the recursion goes here
			// displaying the info message
			cout << "Calling " << value << " from " << functionName << endl;
			processARequest(value); 
		}
		else{
		//print the stack
			sharedStack.print_stack();
		} 
		commands = commands->next;
	}
	// delete this function’s data from the top of the stack
	cout << functionName << " is finished. Clearing the stack from it's data..." << endl;
	sharedStack.clear_stack(functionName);
	system("pause");
}

void addInstructorRequest(){
	// asking for the function name
	cout << "Add a service (function) that the instructor wants to use:" << endl;
	cin >> functionName;

	if(!in_service()){
		cout << "The requested service (function) does not exist." << endl;
		cout << "GOING BACK TO MAIN MENU" << endl;
	}
	else{
		// getting the instructor info
		string inst_name;
		int inst_ID;
		
		cout << "Give instructor's name: ";
		cin >> inst_name;

		cout << "Give instructor's ID (an int): ";
		cin >> inst_ID;

		// forming and adding new instructor to the instructorsQueue
		instructor inst(inst_name, inst_ID, functionName);
		instructorsQueue.enqueue(inst);
		
		// displaying a message
		cout << "Prof. " << inst_name << "'s service request of " << functionName << " has been put in the instructor's queue." << endl;
		cout << "Waiting to be served..." << endl;

	}
}


void addStudentRequest(){
	// asking for the function name
	cout << "Add a service (function) that the student wants to use:" << endl;
	cin >> functionName;

	if(!in_service()){
		cout << "The requested service (function) does not exist." << endl;
		cout << "GOING BACK TO MAIN MENU" << endl;
	}
	else{
		// getting the student info
		string stu_name;
		int stu_ID;

		cout << "Give student's name: ";
		cin >> stu_name;

		cout << "Give student's ID (an int): ";
		cin >> stu_ID;
	
		// forming and adding new student to the studentsQueue

		student stu(stu_name, stu_ID, functionName);
		studentsQueue.enqueue(stu);

		// displaying a message
		cout << stu_name <<"'s service request of " << functionName << " has been put in the student's queue." << endl;
		cout << "Waiting to be served..." << endl;
	}
}


bool in_service(){
	service * ptr = service_head;
	while(ptr != NULL){
		if(ptr->name == functionName){
			return true;
		}
		ptr = ptr->right; 
	}

	return false;
}


service* find_service(string function_name){
	service * ptr = service_head;
	while(ptr != NULL){
		if(ptr->name == function_name){
			return ptr;
		}
		ptr = ptr->right;
	}
}



