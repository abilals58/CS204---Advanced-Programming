#include <iostream>
#include "SharedStack.h"
using namespace std;

// constructor

SharedStack::SharedStack()
{
	top = NULL; 
}

// member functions

bool SharedStack::isEmpty(){

	if(top == NULL){
		return true;
	}
	return false;
}

void SharedStack::push(StackNode node){
	// forming and adding new element to the top of the linked list
	StackNode* temp = new StackNode(node);
	temp->next = top;
	top = temp;
}

void SharedStack::pop(StackNode &node){
	// keeping the top value
	node = StackNode(top->f_name, top->command, top->value, top->next);
	StackNode* temp = top->next;
	delete top;
	top = temp;
}

void SharedStack::print_stack(){

	cout << "PRINTING THE STACK TRACE:" << endl;
	if(isEmpty()){
		cout << "The stack is empty" << endl;
	}
	else{
		SharedStack temp_stack;
		StackNode *ptr = top;
		StackNode node;
		while(ptr != NULL){
			node = StackNode(ptr->f_name, ptr->command, ptr->value, ptr->next);
			temp_stack.push(node);
			ptr = ptr->next;
		}
		while(!temp_stack.isEmpty()){
			temp_stack.pop(node);
			cout << node.f_name << ": " << node.command << " " << node.value << endl;
		}
	}
}


void SharedStack::clear_stack(string function_name){
	// after a function done, deleting its memory from the stack;
	// deleting items of a specifi function from the stack;

	StackNode * ptr; 
	while(!isEmpty() && top->f_name == function_name){// if there are elements belongs to this function deletes them

		ptr = top->next;
		delete top;
		top = ptr;

	}
}
