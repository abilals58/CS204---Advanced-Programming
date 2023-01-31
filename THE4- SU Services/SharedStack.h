
// this class is the edited version of the dyanamic int stack which is in the lecture slides
#ifndef SharedStack_H 
#define SharedStack_H

#include <iostream>
#include <string>

using namespace std;


struct StackNode // it is the struct for the nodes of the shared stack including all the info and a pointer to another stack node to form the linked list
{
	string f_name;
	string command;
	string value;
	StackNode *next;

	StackNode(string f, string c, string v, StackNode* n = NULL){ // constructor
		f_name = f;
		command = c;
		value = v;
		next = n;
	}
	StackNode()
	{}

};

class SharedStack{
private:
	StackNode *top;

public:
	SharedStack(); // constructor
	void push(StackNode node); // it adds the given element to the top of the linked list
	void pop( StackNode &node); // it deletes the element in the top and assign the node to this element (returns the deleted element using a reference parameter)
	bool isEmpty(); // check whether the stack is empty or not
	void print_stack(); // it prints the stack in a reverse order (as wanted in the homework)
	void clear_stack(string function_name); // after finishing a funtion, this funtion clears its data from the stack
};

#endif
