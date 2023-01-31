
// these two classes are edited versions of the static integer queue and dynamic integer queue in the lecture slides
#ifndef StaticInstructorQueue_H 
#define StaticStringQueue_H 

#include <string>
#include <vector>

using namespace std;

struct instructor{
	string name; // instructor name
	int ID; // instructor ID
	string f_name; // name of the requested function (service)

	// constructors
	instructor(string n, int i, string f){
		name = n;
		ID = i;
		f_name = f;
	}
	instructor()
	{}

};

// Static Instructor Queue
class StaticInstructorQueue{


private:
	int front;
	int rear;
	int num_items;

	instructor myqueue[5]; 


public:
	StaticInstructorQueue(); // constructor;
	bool isEmpty(); // checks whether the queue is empty or not
	void enqueue(instructor inst); // adds given student to the rear and updates the number of items
	void dequeue(instructor &inst); // deletes the first element and assign inst to this deleted element
};


// Dynamic Student Queue

struct student{
	string name;
	int ID;
	string f_name; // name of the requested function (service)
	student * next;

	// constructors
	student(string n, int i, string f, student* s = NULL){
		name = n;
		ID = i;
		f_name = f;
		next = s;
	}
	student()
	{}

};

class DynamicStudentQueue{

private:
	student * front;
	student * rear;


public:
	DynamicStudentQueue(); // constructor
	bool isEmpty(); // checks whether the queue is empty or not
	void enqueue(student stu); // adds given student to the rear
	void dequeue(student &stu); // deletes the front student, and assign stu to the front student (returns the deleted element using a reference parameter)
	void clear(); // it clears the data from the heap
};

#endif 
