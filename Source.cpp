//Lab 8 ORTIZ, KATIE TH 
//(Priority Queue)

#include "Header.h"


int main() {
	int userInput = 0;
	Stack widgetItem;
	Queue customerOrders;
	cout << "Welcome to the Warehouse!" << endl;
	widgetItem.PushStack(); //Adds a quantity of 300 widgets at $6.50 per to the inventory. This is the fixed inventory.

	do {
		cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "\n1) Print the current inventory.\n"
			<< "2) Print outstanding orders.\n" 
			<< "3) Add a new order.\n"
			<< "4) End the day and process the outstanding orders. \n"
			<< "5) Quit. \n";			
		cin >> userInput;
		while (cin.fail() || userInput > 5 || userInput < 1) {
			cout << "Error: Input must be a number between 1 and 5." << endl;
			cin.ignore(200, '\n');
			cin.clear();
			cin >> userInput;
		}

		switch (userInput) {
		case 1:
			widgetItem.PrintInventory();		
			break;
		case 2:
			customerOrders.PrintOrders();
			break;
		case 3:
			customerOrders.EnqueueQueue(widgetItem);
			break;
		case 4:
			FulfilledOrders(customerOrders, widgetItem);
			break;
		case 5:
			cout << "Closing the program. Goodbye." << endl;
			system("pause");
			exit(0);
		}

	} while (userInput != 5);

	system("pause");
	return 0;
}





//Function to check if inventory is empty or if the requested orders are more than what is in stock
bool Queue::CheckInventory(Stack &widgetItem, bool check, int quantity) {
	int i = -1;

	int checkStockQuantity = 100;
	int checkOrderQuantity = 0;
	if (widgetItem.isEmpty()) {

		cout << "Orders cannot be fulfilled since the inventory is empty.\n";
		check = false;
	}

	do {
		
		checkOrderQuantity = quantity + HeapOrders.arroforders[i].quantity; //Adds total of amount of widgets in orders to variable.
		i++;

	} while (length > i);

		if (checkOrderQuantity > checkStockQuantity) { 

			cout << "Orders placed are more than the widgets currently in stock. This order cannot be fulfilled. "
				<< "It is suggested to close the day and process the outstanding orders. \n";
			check = false;			
		
		}	
	
	return check;
}


//Function to fulfill orders 
void FulfilledOrders(Queue &customerOrders, Stack &widgetItem) {
	OrderStruct order;
	int shippedQuantity = 0;
	double costWarehouse = 0, costCustomer = 0, totalProfit = 0, totalMarkup = 0;
	int i = 0, j = 0;
	int totalQt = 0;
	int quantity = 0, orderNumber;
	cout << setprecision(2) << fixed << showpoint;



	if (customerOrders.isEmpty()) {
		cout << "There were no orders for this day.\nClosing the program. Goodbye.\n" << endl;
		system("pause");
		exit(0);
	}
	if (!customerOrders.isEmpty() && widgetItem.isEmpty()) {
		cout << "\nError: There are more orders than widgets and widgets cannot be put on hold.\nClosing the program. Goodbye.\n" << endl;
		system("pause");
		exit(0);
	}
	while (!customerOrders.isEmpty() || j == 0) {
		if (i == 0) {
			customerOrders.DequeueQueue(order);
			shippedQuantity = 0, totalQt = 0;
			costWarehouse = 0, costCustomer = 0, totalProfit = 0;


		}
		if (widgetItem.isEmpty()) {
			cout << "\nThere are no more widgets in the inventory. The following amount of orders cannot be processed: " << order.quantity << endl;
			cout << "Returning back to the main menu.\n";
			break;
		}
		if (widgetItem.PeekStack()->quantity >= order.quantity) {

			shippedQuantity = order.quantity;
			totalQt += shippedQuantity;
			if (order.rushStatus == 3) {
				totalProfit = costCustomer + 1.5 * widgetItem.PeekStack()->cost * shippedQuantity - (costWarehouse + shippedQuantity * widgetItem.PeekStack()->cost);
			}
			else if (order.rushStatus == 2) {
				totalProfit = costCustomer + 1.2 * widgetItem.PeekStack()->cost * shippedQuantity - (costWarehouse + shippedQuantity * widgetItem.PeekStack()->cost);
			}
			else if (order.rushStatus == 1) {
				totalProfit = costCustomer + 1.1 * widgetItem.PeekStack()->cost * shippedQuantity - (costWarehouse + shippedQuantity * widgetItem.PeekStack()->cost);
			}
			cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			cout << "Shipment Receipt for Order #" << order.orderNumber << endl;
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;
			cout << "Qty. Ordered" << right << setw(26) << totalQt << endl;
			cout << "Qty. Shipped" << right << setw(26) << totalQt << endl;
			if (order.rushStatus == 3) {
				cout << "Rush Status" << right << setw(27) << "Extreme" << endl;
				cout << "% of Markup" << right << setw(27) << "50%" << endl;
				cout << "Amount of Markup per Widget" << right << setw(7) << "$" << widgetItem.PeekStack()->cost * 1.5 << endl;
				totalMarkup = (costCustomer + 1.5 * widgetItem.PeekStack()->cost * shippedQuantity) - (costWarehouse + shippedQuantity * widgetItem.PeekStack()->cost);

			}
			else if (order.rushStatus == 2) {
				cout << "Rush Status" << right << setw(27) << "Expedited" << endl;
				cout << "% of Markup" << right << setw(27) << "20%" << endl;
				cout << "Amount of Markup per Widget" << right << setw(7) << "$" << widgetItem.PeekStack()->cost * 1.2 << endl;
				totalMarkup = (costCustomer + 1.2 * widgetItem.PeekStack()->cost * shippedQuantity) - (costWarehouse + shippedQuantity * widgetItem.PeekStack()->cost);
			}
			else if (order.rushStatus == 1) {
				cout << "Rush Status" << right << setw(27) << "Standard" << endl;
				cout << "% of Markup" << right << setw(27) << "10%" << endl;
				cout << "Amount of Markup per Widget" << right << setw(7) << "$" << widgetItem.PeekStack()->cost * 1.1 << endl;
				totalMarkup = (costCustomer + 1.1 * widgetItem.PeekStack()->cost * shippedQuantity) - (costWarehouse + shippedQuantity * widgetItem.PeekStack()->cost);
			}


			cout << "Total Markup Amount" << right << setw(15) << "$" << totalMarkup << endl;
			cout << "Total Cost to Warehouse" << right << setw(11) << "$" << costWarehouse + shippedQuantity * widgetItem.PeekStack()->cost << endl;

			if (order.rushStatus == 3) {
				cout << "Total Cost to Customer" << right << setw(12) << "$" << costCustomer + 1.5 * widgetItem.PeekStack()->cost * shippedQuantity << endl;
			}
			else if (order.rushStatus == 2) {
				cout << "Total Cost to Customer" << right << setw(12) << "$" << costCustomer + 1.2 * widgetItem.PeekStack()->cost * shippedQuantity << endl;
			}
			else if (order.rushStatus == 1) {
				cout << "Total Cost to Customer" << right << setw(12) << "$" << costCustomer + 1.1 * widgetItem.PeekStack()->cost * shippedQuantity << endl;
			}
			cout << "Profit from Shipment" << right << setw(14) << "$" << totalProfit << endl;
			cout << "Profit to Warehouse" << right << setw(15) << "$" << totalProfit << endl;

			cout << "Remaining widgets in stock: " << right << setw(10) << widgetItem.PeekStack()->quantity - shippedQuantity << endl;

			widgetItem.PeekStack()->quantity = widgetItem.PeekStack()->quantity - shippedQuantity;
			if (widgetItem.PeekStack()->quantity == 0) {
				widgetItem.PopStack();
			}
			i = 0;
			quantity = 0;
			if (customerOrders.isEmpty()) {
				j = 1;
			}


		}
	}
}

//Function to print inventory
void Stack::PrintInventory() {
	cout << "\nAvailable Inventory\n" << endl;

	Widget *temp = top;

	cout << setprecision(2) << fixed << showpoint;

	if (temp != nullptr) {
		cout <<  setw(16) << "Unit Price" << setw(20) << "Total in Stock" << endl;
	} 
	else {
		cout << "There is nothing in the inventory.\n";
	}
	
	while (temp != nullptr) {
		if (temp->cost != 0) {
			cout << right << setw(12) << "$" << temp->cost << setw(18) << temp->quantity << endl;
		}
		temp = temp->next;
	}
}

//Function to print the orders
void Queue::PrintOrders() {
	int i = 0;
	cout << "\nOutstanding Orders";
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	if (length == 0) {

		cout << "\nThere are no outstanding orders.\n";
		return;
	}
	while(i != length) {
		
	
		cout << "\nOrder #" << HeapOrders.arroforders[i].orderNumber << endl;
		cout << "Amount of widgets in the order: " << HeapOrders.arroforders[i].quantity << endl;

		if (HeapOrders.arroforders[i].rushStatus == 1) {

			cout << "Rush status of order: Standard" << endl;

		}

		else if (HeapOrders.arroforders[i].rushStatus == 2) {

			cout << "Rush status of order: Expedited" << endl;
		}


		else if (HeapOrders.arroforders[i].rushStatus == 3) {

			cout << "Rush status of order: Extreme" << endl;

		}

		i++;
		
	}

}




//Functions to sort the heap
template <class Order>
void Heap<Order>::ReheapDownSortOrders(int root, int bottom) {
	int max, right, left;
	max = left = root * 2;
	right = left + 1;

	if (left < bottom) {
		if (arroforders[max].rushStatus < arroforders[right].rushStatus) {
			max = right;
		}
		else if (arroforders[max].rushStatus == arroforders[right].rushStatus) {

			if (arroforders[max].orderNumber > arroforders[right].orderNumber) {
				max = right;
			}
		}
	}
	if (max <= bottom) {

		if (arroforders[root].rushStatus < arroforders[max].rushStatus) {
			
			Swap(arroforders[root], arroforders[max]);
		
			ReheapDownSortOrders(max, bottom);
		}
		else if (arroforders[root].rushStatus == arroforders[max].rushStatus) {

			if (arroforders[root].orderNumber > arroforders[max].orderNumber) {


				Swap(arroforders[root], arroforders[max]);

				ReheapDownSortOrders(max, bottom);
			}

		}

	}
}

template <class Order>
void Heap<Order>::ReheapUpSortOrders(int root, int end) {
	if (end != root) {
		int source = end / 2;
		if (arroforders[source].rushStatus < arroforders[end].rushStatus) {
			
			Swap(arroforders[source], arroforders[end]);
		
			ReheapUpSortOrders(root, source);
		}
	}
}


//Function to swap orders in the heap
void Swap(OrderStruct &swone, OrderStruct &swtwo) {
	OrderStruct tmp = swone;
	swone = swtwo;
	swtwo = tmp;

}

//Function to push to the stack
void Stack::PushStack() {

	processedWidgets++;
	double cost;
	int quantity;
	quantity = 300;
	cost = 6.50;
	Widget *newWidgetItem = new (nothrow) Widget;

	if (newWidgetItem == nullptr) {
		cout << "Error: There is insufficient memory. Item was not created." << endl;
		EmptyStack();
		system("pause");
		exit(1);
	}
	if (isFull()) {

		cout << "Overflow.\nExiting...\n";
		system("pause");
		exit(EXIT_FAILURE);

	}

	else {
		newWidgetItem->cost = cost;
		newWidgetItem->quantity = quantity;
		newWidgetItem->next = top;
		top = newWidgetItem;
		capacity++;
	}
}

//Function to add to the queue
void Queue::EnqueueQueue(Stack &widgetItem) {
	processedOrders++;
	int orderNumber, rushStatus, quantity;
	bool check = true;
	orderNumber = processedOrders + 1000;
	cout << "\nOrder #" << orderNumber;

	cout << "\nPlease enter the amount of widgets: ";
	cin >> quantity;
	while (quantity < 1 || cin.fail()) {
		cout << "Error: Widgets must be a positive number and greater than 0. Please try again." << endl;
		cout << "Please enter the amount of widgets: ";
		cin >> quantity;
		cin.clear();
		cin.ignore(200, '\n');
	}

	check = CheckInventory(widgetItem, check, quantity);

	if (check == true) {

		cout << "\nOptions for Rush Status\n"
			<< "1) Standard rush (Please note that it will be a 10% markup)"
			<< "\n2) Expedited rush (Please note that it will be a 20% markup)"
			<< "\n3) Extreme rush (Please note that it will be a 50% markup)";
		cout << "\nPlease select a rush status: ";
		cin >> rushStatus;

		while (rushStatus != Standard && rushStatus != Expedited && rushStatus != Extreme) {
			cout << "Error: Rush status must have a value of 1, 2, or 3. Please try again." << endl;
			cout << "Please select a rush status: ";
			cin >> rushStatus;
			cin.clear();
			cin.ignore(200, '\n');
		}
		cout << endl;
		OrderStruct *newOrderItem = new (nothrow) OrderStruct;
		if (newOrderItem == nullptr) {
			cout << "Error: There is insufficient memory. Item was not created." << endl;
			EmptyQueue();
			system("pause");
			exit(1);
		}

		if (isFull()) {
			cout << "The queue is full.\nExiting...\n";
			system("pause");
			exit(EXIT_FAILURE);
		}


		newOrderItem->quantity = quantity;
		newOrderItem->rushStatus = rushStatus;
		newOrderItem->orderNumber = orderNumber;

		length++;
		HeapOrders.arroforders[length - 1] = *newOrderItem;
		HeapOrders.ReheapUpSortOrders(0, length - 1);
	}
}



//Function to pop from the stack
void Stack::PopStack() {
	
	if (isEmpty()) {

		cout << "Underflow.\nExiting...\n";
		system("pause");
		exit(EXIT_FAILURE);
	}
	
	
	else if (top != nullptr) {
		Widget * temp = new Widget;
		temp = top;
		top = top->next;
		delete temp;
		temp = nullptr;
		capacity--;
	}

}



//Function to remove from the queue
void Queue::DequeueQueue(OrderStruct & order) {
	
	if (isEmpty()) {
		cout << "The queue is empty.\nExiting...\n";
		system("pause");
		exit(EXIT_FAILURE);
	}
	
	
	order = HeapOrders.arroforders[0];
	HeapOrders.arroforders[0] = HeapOrders.arroforders[length - 1];
	length--;
	HeapOrders.ReheapDownSortOrders(0, length - 1);
}



//Function to peek the stack
Widget *Stack::PeekStack() {

	if (!isEmpty()) {
		return top;
	}
	else {
		cout << "There was an error when peeking the stack.\nExiting...\n";
		system("pause");
		exit(EXIT_FAILURE);
	}

}

//Function to check if stack is empty
bool Stack::isEmpty() {

	return (top == nullptr);
}

//Function to check if the stack is full
bool Stack::isFull() {

	return capacity == size;


}

//Function to check if queue is empty 
bool Queue::isEmpty() {
	return (length == 0);
}



//Function to check if the queue is full 
bool Queue::isFull() {

	return length == size;

}

//Constructors
OrderStruct::OrderStruct() {
	int quantity = 0;
	int rushStatus = 0;
	int orderNumber = 0;
	OrderStruct *leftChild = nullptr;
	OrderStruct *rightChild = nullptr;
}

//Constructor for class Queue
Queue::Queue() {

	length = 0;
	processedOrders = 0;
	size = SIZE;
}


//Constructor for class Stack
Stack::Stack() {
	capacity = 0;
	size = SIZE;
	top = nullptr;
	processedWidgets = 0;
}



//Destructor for class queue
Queue::~Queue() {
	size = 0;
	length = 0;
	EmptyQueue();
}

//Function to empty queue
void Queue::EmptyQueue() {
	processedOrders = 0;
	length = 0;

}

//Destructor for class Stack
Stack::~Stack() {

	processedWidgets = 0;
	size = 0;
	capacity = 0;
	EmptyStack();
}


//Function to empty stack
void Stack::EmptyStack() {
	while (top != nullptr) {
		PopStack();
	}
	top = nullptr;
}


/*

Lab 8 Test Plan:
-> Select option 3 each time to add the following orders in this order:
Order 1001:
1. Quantity - 10
2. Rush Status - (1) Standard

Order 1002:
1. Quantity - 5
2. Rush Status - (3) Extreme

Order 1003:
1. Quantity - 2
2. Rush Status - (2) Expedited

Order 1004:
1. Quantity - 1
2. Rush Status - (2) Expedited

Order 1005:
1. Quantity - 6
2. Rush Status - (3) Extreme

Order 1006:
1. Quantity - 5
2. Rush Status - (1) Standard

Order 1007:
1. Quantity - 4
2. Rush Status - (2) Expedited

Order 1008:
1. Quantity - 3
2. Rush Status - (1) Standard

Order 1009:
1. Quantity - 7
2. Rush Status - (3) Extreme

Order 1010:
1. Quantity - 8
2. Rush Status - (1) Standard

Order 1011:
1. Quantity - 9
2. Rush Status - (2) Expedited

Order 1012:
1. Quantity - 4
2. Rush Status - (3) Extreme

Order 1013:
1. Quantity - 10
2. Rush Status - (1) Standard

Order 1014:
1. Quantity - 2
2. Rush Status - (2) Expedited

Order 1015:
1. Quantity - 5
2. Rush Status - (3) Extreme


-> After adding all these orders, select the option 2 to print the outstanding orders

-> Select option 4 to end the day and process orders.

-> Verify that order of the orders are fulfilled in the following order:
Expected Shipment Receipt Order:
1st Rush Status: Extreme
1. Order 1002 - Extreme Rush Status
2. Order 1005 - Extreme Rush Status
3. Order 1009 - Extreme Rush Status
4. Order 1012 - Extreme Rush Status
5. Order 1015 - Extreme Rush Status

2nd Rush Status: Expedited
6. Order 1003 - Expedited Rush Status
7. Order 1004 - Expedited Rush Status
8. Order 1007 - Expedited Rush Status
9. Order 1011 - Expedited Rush Status
10. Order 1014 - Expedited Rush Status

3rd Rush Status: Standard
11. Order 1001 - Standard Rush Status
12. Order 1006 - Standard Rush Status
13. Order 1008 - Standard Rush Status
14. Order 1010 - Standard Rush Status
15. Order 1013 - Standard Rush Status

-> Quit the program




Lab 8 Test Data:

Welcome to the Warehouse!

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

1) Print the current inventory.
2) Print outstanding orders.
3) Add a new order.
4) End the day and process the outstanding orders.
5) Quit.
3

Order #1001
Please enter the amount of widgets: 10

Options for Rush Status
1) Standard rush (Please note that it will be a 10% markup)
2) Expedited rush (Please note that it will be a 20% markup)
3) Extreme rush (Please note that it will be a 50% markup)
Please select a rush status: 1


~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

1) Print the current inventory.
2) Print outstanding orders.
3) Add a new order.
4) End the day and process the outstanding orders.
5) Quit.
3

Order #1002
Please enter the amount of widgets: 5

Options for Rush Status
1) Standard rush (Please note that it will be a 10% markup)
2) Expedited rush (Please note that it will be a 20% markup)
3) Extreme rush (Please note that it will be a 50% markup)
Please select a rush status: 3


~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

1) Print the current inventory.
2) Print outstanding orders.
3) Add a new order.
4) End the day and process the outstanding orders.
5) Quit.
3

Order #1003
Please enter the amount of widgets: 2

Options for Rush Status
1) Standard rush (Please note that it will be a 10% markup)
2) Expedited rush (Please note that it will be a 20% markup)
3) Extreme rush (Please note that it will be a 50% markup)
Please select a rush status: 2


~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

1) Print the current inventory.
2) Print outstanding orders.
3) Add a new order.
4) End the day and process the outstanding orders.
5) Quit.
3

Order #1004
Please enter the amount of widgets: 1

Options for Rush Status
1) Standard rush (Please note that it will be a 10% markup)
2) Expedited rush (Please note that it will be a 20% markup)
3) Extreme rush (Please note that it will be a 50% markup)
Please select a rush status: 2


~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

1) Print the current inventory.
2) Print outstanding orders.
3) Add a new order.
4) End the day and process the outstanding orders.
5) Quit.
3

Order #1005
Please enter the amount of widgets: 6

Options for Rush Status
1) Standard rush (Please note that it will be a 10% markup)
2) Expedited rush (Please note that it will be a 20% markup)
3) Extreme rush (Please note that it will be a 50% markup)
Please select a rush status: 3


~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

1) Print the current inventory.
2) Print outstanding orders.
3) Add a new order.
4) End the day and process the outstanding orders.
5) Quit.
3

Order #1006
Please enter the amount of widgets: 5

Options for Rush Status
1) Standard rush (Please note that it will be a 10% markup)
2) Expedited rush (Please note that it will be a 20% markup)
3) Extreme rush (Please note that it will be a 50% markup)
Please select a rush status: 1


~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

1) Print the current inventory.
2) Print outstanding orders.
3) Add a new order.
4) End the day and process the outstanding orders.
5) Quit.
3

Order #1007
Please enter the amount of widgets: 4

Options for Rush Status
1) Standard rush (Please note that it will be a 10% markup)
2) Expedited rush (Please note that it will be a 20% markup)
3) Extreme rush (Please note that it will be a 50% markup)
Please select a rush status: 2


~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

1) Print the current inventory.
2) Print outstanding orders.
3) Add a new order.
4) End the day and process the outstanding orders.
5) Quit.
3

Order #1008
Please enter the amount of widgets: 3

Options for Rush Status
1) Standard rush (Please note that it will be a 10% markup)
2) Expedited rush (Please note that it will be a 20% markup)
3) Extreme rush (Please note that it will be a 50% markup)
Please select a rush status: 1


~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

1) Print the current inventory.
2) Print outstanding orders.
3) Add a new order.
4) End the day and process the outstanding orders.
5) Quit.
3

Order #1009
Please enter the amount of widgets: 7

Options for Rush Status
1) Standard rush (Please note that it will be a 10% markup)
2) Expedited rush (Please note that it will be a 20% markup)
3) Extreme rush (Please note that it will be a 50% markup)
Please select a rush status: 3


~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

1) Print the current inventory.
2) Print outstanding orders.
3) Add a new order.
4) End the day and process the outstanding orders.
5) Quit.
3

Order #1010
Please enter the amount of widgets: 8

Options for Rush Status
1) Standard rush (Please note that it will be a 10% markup)
2) Expedited rush (Please note that it will be a 20% markup)
3) Extreme rush (Please note that it will be a 50% markup)
Please select a rush status: 1


~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

1) Print the current inventory.
2) Print outstanding orders.
3) Add a new order.
4) End the day and process the outstanding orders.
5) Quit.
3

Order #1011
Please enter the amount of widgets: 9

Options for Rush Status
1) Standard rush (Please note that it will be a 10% markup)
2) Expedited rush (Please note that it will be a 20% markup)
3) Extreme rush (Please note that it will be a 50% markup)
Please select a rush status: 2


~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

1) Print the current inventory.
2) Print outstanding orders.
3) Add a new order.
4) End the day and process the outstanding orders.
5) Quit.
3

Order #1012
Please enter the amount of widgets: 4

Options for Rush Status
1) Standard rush (Please note that it will be a 10% markup)
2) Expedited rush (Please note that it will be a 20% markup)
3) Extreme rush (Please note that it will be a 50% markup)
Please select a rush status: 3


~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

1) Print the current inventory.
2) Print outstanding orders.
3) Add a new order.
4) End the day and process the outstanding orders.
5) Quit.
3

Order #1013
Please enter the amount of widgets: 10

Options for Rush Status
1) Standard rush (Please note that it will be a 10% markup)
2) Expedited rush (Please note that it will be a 20% markup)
3) Extreme rush (Please note that it will be a 50% markup)
Please select a rush status: 1


~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

1) Print the current inventory.
2) Print outstanding orders.
3) Add a new order.
4) End the day and process the outstanding orders.
5) Quit.
3

Order #1014
Please enter the amount of widgets: 2

Options for Rush Status
1) Standard rush (Please note that it will be a 10% markup)
2) Expedited rush (Please note that it will be a 20% markup)
3) Extreme rush (Please note that it will be a 50% markup)
Please select a rush status: 2


~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

1) Print the current inventory.
2) Print outstanding orders.
3) Add a new order.
4) End the day and process the outstanding orders.
5) Quit.
3

Order #1015
Please enter the amount of widgets: 5

Options for Rush Status
1) Standard rush (Please note that it will be a 10% markup)
2) Expedited rush (Please note that it will be a 20% markup)
3) Extreme rush (Please note that it will be a 50% markup)
Please select a rush status: 3


~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

1) Print the current inventory.
2) Print outstanding orders.
3) Add a new order.
4) End the day and process the outstanding orders.
5) Quit.
2

Outstanding Orders
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Order #1002
Amount of widgets in the order: 5
Rush status of order: Extreme

Order #1005
Amount of widgets in the order: 6
Rush status of order: Extreme

Order #1009
Amount of widgets in the order: 7
Rush status of order: Extreme

Order #1015
Amount of widgets in the order: 5
Rush status of order: Extreme

Order #1003
Amount of widgets in the order: 2
Rush status of order: Expedited

Order #1012
Amount of widgets in the order: 4
Rush status of order: Extreme

Order #1007
Amount of widgets in the order: 4
Rush status of order: Expedited

Order #1004
Amount of widgets in the order: 1
Rush status of order: Expedited

Order #1001
Amount of widgets in the order: 10
Rush status of order: Standard

Order #1010
Amount of widgets in the order: 8
Rush status of order: Standard

Order #1006
Amount of widgets in the order: 5
Rush status of order: Standard

Order #1011
Amount of widgets in the order: 9
Rush status of order: Expedited

Order #1013
Amount of widgets in the order: 10
Rush status of order: Standard

Order #1014
Amount of widgets in the order: 2
Rush status of order: Expedited

Order #1008
Amount of widgets in the order: 3
Rush status of order: Standard

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

1) Print the current inventory.
2) Print outstanding orders.
3) Add a new order.
4) End the day and process the outstanding orders.
5) Quit.
4

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Shipment Receipt for Order #1002
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Qty. Ordered                         5
Qty. Shipped                         5
Rush Status                    Extreme
% of Markup                        50%
Amount of Markup per Widget      $9.75
Total Markup Amount              $16.25
Total Cost to Warehouse          $32.50
Total Cost to Customer           $48.75
Profit from Shipment             $16.25
Profit to Warehouse              $16.25
Remaining widgets in stock:        295

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Shipment Receipt for Order #1005
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Qty. Ordered                         6
Qty. Shipped                         6
Rush Status                    Extreme
% of Markup                        50%
Amount of Markup per Widget      $9.75
Total Markup Amount              $19.50
Total Cost to Warehouse          $39.00
Total Cost to Customer           $58.50
Profit from Shipment             $19.50
Profit to Warehouse              $19.50
Remaining widgets in stock:        289

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Shipment Receipt for Order #1009
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Qty. Ordered                         7
Qty. Shipped                         7
Rush Status                    Extreme
% of Markup                        50%
Amount of Markup per Widget      $9.75
Total Markup Amount              $22.75
Total Cost to Warehouse          $45.50
Total Cost to Customer           $68.25
Profit from Shipment             $22.75
Profit to Warehouse              $22.75
Remaining widgets in stock:        282

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Shipment Receipt for Order #1012
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Qty. Ordered                         4
Qty. Shipped                         4
Rush Status                    Extreme
% of Markup                        50%
Amount of Markup per Widget      $9.75
Total Markup Amount              $13.00
Total Cost to Warehouse          $26.00
Total Cost to Customer           $39.00
Profit from Shipment             $13.00
Profit to Warehouse              $13.00
Remaining widgets in stock:        278

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Shipment Receipt for Order #1015
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Qty. Ordered                         5
Qty. Shipped                         5
Rush Status                    Extreme
% of Markup                        50%
Amount of Markup per Widget      $9.75
Total Markup Amount              $16.25
Total Cost to Warehouse          $32.50
Total Cost to Customer           $48.75
Profit from Shipment             $16.25
Profit to Warehouse              $16.25
Remaining widgets in stock:        273

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Shipment Receipt for Order #1003
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Qty. Ordered                         2
Qty. Shipped                         2
Rush Status                  Expedited
% of Markup                        20%
Amount of Markup per Widget      $7.80
Total Markup Amount              $2.60
Total Cost to Warehouse          $13.00
Total Cost to Customer           $15.60
Profit from Shipment             $2.60
Profit to Warehouse              $2.60
Remaining widgets in stock:        271

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Shipment Receipt for Order #1004
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Qty. Ordered                         1
Qty. Shipped                         1
Rush Status                  Expedited
% of Markup                        20%
Amount of Markup per Widget      $7.80
Total Markup Amount              $1.30
Total Cost to Warehouse          $6.50
Total Cost to Customer           $7.80
Profit from Shipment             $1.30
Profit to Warehouse              $1.30
Remaining widgets in stock:        270

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Shipment Receipt for Order #1007
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Qty. Ordered                         4
Qty. Shipped                         4
Rush Status                  Expedited
% of Markup                        20%
Amount of Markup per Widget      $7.80
Total Markup Amount              $5.20
Total Cost to Warehouse          $26.00
Total Cost to Customer           $31.20
Profit from Shipment             $5.20
Profit to Warehouse              $5.20
Remaining widgets in stock:        266

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Shipment Receipt for Order #1011
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Qty. Ordered                         9
Qty. Shipped                         9
Rush Status                  Expedited
% of Markup                        20%
Amount of Markup per Widget      $7.80
Total Markup Amount              $11.70
Total Cost to Warehouse          $58.50
Total Cost to Customer           $70.20
Profit from Shipment             $11.70
Profit to Warehouse              $11.70
Remaining widgets in stock:        257

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Shipment Receipt for Order #1014
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Qty. Ordered                         2
Qty. Shipped                         2
Rush Status                  Expedited
% of Markup                        20%
Amount of Markup per Widget      $7.80
Total Markup Amount              $2.60
Total Cost to Warehouse          $13.00
Total Cost to Customer           $15.60
Profit from Shipment             $2.60
Profit to Warehouse              $2.60
Remaining widgets in stock:        255

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Shipment Receipt for Order #1001
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Qty. Ordered                        10
Qty. Shipped                        10
Rush Status                   Standard
% of Markup                        10%
Amount of Markup per Widget      $7.15
Total Markup Amount              $6.50
Total Cost to Warehouse          $65.00
Total Cost to Customer           $71.50
Profit from Shipment             $6.50
Profit to Warehouse              $6.50
Remaining widgets in stock:        245

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Shipment Receipt for Order #1006
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Qty. Ordered                         5
Qty. Shipped                         5
Rush Status                   Standard
% of Markup                        10%
Amount of Markup per Widget      $7.15
Total Markup Amount              $3.25
Total Cost to Warehouse          $32.50
Total Cost to Customer           $35.75
Profit from Shipment             $3.25
Profit to Warehouse              $3.25
Remaining widgets in stock:        240

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Shipment Receipt for Order #1008
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Qty. Ordered                         3
Qty. Shipped                         3
Rush Status                   Standard
% of Markup                        10%
Amount of Markup per Widget      $7.15
Total Markup Amount              $1.95
Total Cost to Warehouse          $19.50
Total Cost to Customer           $21.45
Profit from Shipment             $1.95
Profit to Warehouse              $1.95
Remaining widgets in stock:        237

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Shipment Receipt for Order #1010
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Qty. Ordered                         8
Qty. Shipped                         8
Rush Status                   Standard
% of Markup                        10%
Amount of Markup per Widget      $7.15
Total Markup Amount              $5.20
Total Cost to Warehouse          $52.00
Total Cost to Customer           $57.20
Profit from Shipment             $5.20
Profit to Warehouse              $5.20
Remaining widgets in stock:        229

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Shipment Receipt for Order #1013
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Qty. Ordered                        10
Qty. Shipped                        10
Rush Status                   Standard
% of Markup                        10%
Amount of Markup per Widget      $7.15
Total Markup Amount              $6.50
Total Cost to Warehouse          $65.00
Total Cost to Customer           $71.50
Profit from Shipment             $6.50
Profit to Warehouse              $6.50
Remaining widgets in stock:        219

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

1) Print the current inventory.
2) Print outstanding orders.
3) Add a new order.
4) End the day and process the outstanding orders.
5) Quit.
5
Closing the program. Goodbye.
Press any key to continue . . .


*/