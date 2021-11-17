//Lab 8 ORTIZ, KATIE TH 
//(Priority Queue)

#include <iostream>
#include <iomanip>
#define SIZE 1000
using namespace std;

//Struct for the widgets
struct Widget {
	int quantity;
	double cost;
	Widget *next;
};

//Struct for orders
struct OrderStruct{
	//Function for OrderStruct
	OrderStruct();
	

	int quantity;
	int rushStatus;
	int orderNumber;
};




//Struct for the Heap
template <class Order>
struct Heap {
	//int elements;


	//Functions to sort the heap
	void ReheapDownSortOrders(int root, int end);
	void ReheapUpSortOrders(int root, int end);




	//Array for the orders with the class Order
	Order arroforders[300];

};


//Stack class
class Stack{
private:
	Widget *top;
	int processedWidgets, capacity, size;

public:
	//Constructor
	Stack();
	//Destructor
	~Stack();
	//Function to pop from the stack
	void PopStack();
	//Function to push to the stack 
	void PushStack();
	//Function to peek the stack
	Widget *PeekStack();
	//Function to check if the stack is empty 
	bool isEmpty();
	//Function to check if the stack is full
	bool isFull();
	//Function to print the inventory
	void PrintInventory();
	//Function to empty the stack
	void EmptyStack();

};

class Queue {
private:
	int processedOrders, length, size;
	Heap<OrderStruct> HeapOrders;

public:
	//Constructor
	Queue();
	//Destructor
	~Queue();
	//Function to check if the queue is empty 
	bool isEmpty();
	//Function to check if the queue is full
	bool isFull();
	//Function to empty the queue
	void EmptyQueue();
	//Function to remove from the queue
	void DequeueQueue(OrderStruct &order);
	//Function to add to the queue
	void EnqueueQueue(Stack &widgetItem);
	//Function to print the orders
	void PrintOrders();
	//Function to check the inventory
	bool CheckInventory(Stack &widgetItem, bool check, int quantity);

};

//Function to fulfill the orders
void FulfilledOrders(Queue &customerOrders, Stack &widgetItem);


//Rush options are enumerated
enum Rush{ 
	Standard = 1, Expedited, Extreme
};