#include <iostream>
#include "DynamicAndStaticQueue.h"

using namespace std;

// static instructor queue

//constructor
StaticInstructorQueue::StaticInstructorQueue(){
	front = -1;
	rear = -1;
	num_items = 0;
}

// member functions 

bool StaticInstructorQueue::isEmpty(){
	if (num_items == 0){
		return true;
	}
	return false;
	
}

void StaticInstructorQueue::enqueue(instructor inst ){
	rear += 1; // rear is the position to adding new item
	myqueue[rear] = inst; //adding the new item 

	num_items++; // updating number of items

}

void StaticInstructorQueue::dequeue(instructor &inst){

	front+= 1; // front is index of deleting element(first element)
	
	inst = myqueue[front]; // keeping deleting item as inst
	num_items--; // updating number of items

}


// dyanmic student queue

//constructor

DynamicStudentQueue::DynamicStudentQueue(){
	// initializing the linked list
	front = NULL;
	rear = NULL;

}

// functions

bool DynamicStudentQueue::isEmpty(){

	if(front == NULL){
		return true;
	}
	return false;

}
	
void DynamicStudentQueue::enqueue(student stu){
	// adding stu to the linked list
	student * temp = new student(stu);
	if(isEmpty()){ // if queue is empty adding the first element
		front = temp;
		rear = front; // updating rear
	}
	else{ // adding other elements
		temp->next = rear->next;
		rear->next = temp;
		rear = rear->next; // updating the rear;

	}

}

void DynamicStudentQueue::dequeue(student& stu){

	// keeping the deleting item as stu;
	student s(front->name, front->ID, front->f_name, front->next);
	stu = s;

	// deleting the first item
	student* temp = front->next;
	delete front;
	front = temp;

}

void DynamicStudentQueue::clear(){

	// deleting all items from the heap;
	student* ptr;
	while(!isEmpty()){
		ptr = front->next;
		delete front;
		front = ptr;
	}
}

