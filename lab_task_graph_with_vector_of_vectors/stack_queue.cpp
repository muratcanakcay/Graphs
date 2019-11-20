#include <iostream>
#include "stack_queue.h"

using namespace std;

Stack::Stack() //constructor
{
	//stack starts empty, i.e. top points to NULL
	top = NULL;
}
Stack::~Stack() //deconstructor
{
	while (!isEmpty())
	{
		pop();
	}
}
void Stack::push(int x)
{
	// create a Node to store x
	Node* current = new Node;
	current->data = x;

	if (isEmpty())
	{
		current->next = NULL;
		top = current;
	}
	else
	{
		current->next = top; // current points to old top
		top = current; // current is the new top
	}
}
int Stack::pop()
{
	if (!isEmpty())
	{
		int data = top->data;
		Node* oldtop = top;
		top = oldtop->next;
		delete oldtop;
		return data;
	}
	cout << "Stack is empty." << endl;
	return(NULL);
}
string Stack::contents()
{
	string result = "(top) <- ";
	if (isEmpty())
		result += "NULL";
	else
	{
		Node* current = top; //we don't want to lose front
		while (current != NULL)
		{
			result = result + to_string(current->data) + " <- ";
			current = current->next;
		}
		result += "(bottom)";
	}

	return result;
}

Queue::Queue() //constructor
{
	//queue starts empty, i.e. front and rear points to NULL
	front = NULL;
	rear = NULL;
}
Queue::~Queue() //deconstructor
{
	while (!isEmpty())
	{
		dequeue();
	}
}
void Queue::enqueue(int x)
{
	// create a Node to store x
	Node* current = new Node;
	current->data = x;
	current->next = NULL;

	if (isEmpty())
	{
		front = current;
		rear = current;
	}
	else
	{
		rear->next = current; // old rear's next points to current
		rear = current; // current is the new rear
	}
}
int Queue::dequeue()
{
	if (!isEmpty())
	{
		int val = front->data;
		Node* oldfront = front;
		front = oldfront->next;
		delete oldfront;
		return val;
	}
	cout << "Queue is empty." << endl;
	return(NULL);
}
string Queue::contents()
{
	string result = "(front) <- ";
	if (isEmpty())
		result += "NULL";
	else
	{
		Node* current = front; //we don't want to lose front
		while (current != NULL)
		{
			result = result + to_string(current->data) + " <- ";
			current = current->next;
		}
		result += "(rear)";
	}

	return result;
}
