#include <string>

using namespace std;

// declare a node struct
struct Node
{
	int data;
	Node* next;
};

// declare stack class
class Stack
{
private:
	Node* top;
public:
	Stack(); //constructor
	~Stack(); //deconstructor
	void push(int x); //pushes a node with data=x to the top of the stack
	int pop(); //removes the top node and returns its data value
	int peek() { if (!isEmpty()) return top->data; }  
	string contents(); //prints the contents of the stack
	bool isEmpty() { return top == NULL; } //inline definition - returns 1 if stack is empty
};

// declare queue class
class Queue
{
private:
	Node* front;
	Node* rear;
public:
	Queue(); //constructor
	~Queue(); //deconstructor
	void enqueue(int x); //enqueues a node with data=x to the rear of the queue
	int dequeue(); //removes the front node and returns its data value
	string contents(); //prints the contents of the queue
	bool isEmpty() { return front == NULL; } //inline definition - returns 1 if queue is empty
};
