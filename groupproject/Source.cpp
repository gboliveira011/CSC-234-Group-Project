#include"Customer.h"
#include"CustomerList.h"
#include"Order.h"
#include"OrderList.h"
#include<iostream>
#include<fstream>
#include<string>


using namespace std;

void LoadCustomers(ifstream& infile, CustomerList& customers);
int selectMenu();
void PlaceOrder(CustomerList& customers);
void UpdateOrder(CustomerList& customers);
void CancelOrder(CustomerList& customers);
void PrintOrders(CustomerList& customers);
void CheckoutOrders(CustomerList& customers);
void UpdateDatafile(CustomerList& customers);

int main()
{
	// Display doubles with two decimal places
	cout << fixed << showpoint << setprecision(2);

	ifstream infile;
	ofstream outfile;
	CustomerList customers;

	infile.open("BookOrders.txt", ios::in);
	if (!infile)
	{
		cout << "No file found";
		return 1;
	}
	LoadCustomers(infile, customers);
	infile.close();

	cout << "Welcome to Wake Bookstore!\nAll customers and orders are loaded.\n";
	int choice = selectMenu();
	while (choice != 6)
	{
		switch (choice)
		{
		case 1: // Place an order
			PlaceOrder(customers);
			UpdateDatafile(customers);
			break;

		case 2: // Update an order
			UpdateOrder(customers);
			UpdateDatafile(customers);
			break;

		case 3: // Cancel all orders
			CancelOrder(customers);
			UpdateDatafile(customers);
			break;

		case 4: // Print all orders
			PrintOrders(customers);
			break;

		case 5: // Checkout orders
			CheckoutOrders(customers);
			break;

		case 6: // Quit
			break;

		default:
			cout << "Invalid selection." << endl;
		}
		choice = selectMenu();
	}
	cout << "Thanks for shopping at Wake Bookstore!";
    return 0;
}

void LoadCustomers(ifstream& infile, CustomerList& customers)
{
	string line;
	string name;
	string address;
	string email;
	string bookTitle;
	double bookPrice;
	int number;

	getline(infile, name);
	while (infile)
	{
		name.erase(0, 1);
		getline(infile, address);
		getline(infile, email);

		OrderList orderList;

		while (getline(infile, line) && line.front() != '%')
		{
			bookTitle = line;
			infile >> bookPrice >> number;


			Order order(bookTitle, bookPrice, number);
			orderList.AddOrder(order);
			getline(infile, line);
		}
		Customer user(name, address, email, orderList);
		name = line;
		customers.AddCustomer(user);
	}
}

int selectMenu()
{
	int choice;
	cout << "Please select one of the following actions: "
		<< "\n1: Place an order"
		<< "\n2: Update an order"
		<< "\n3: Cancel an order"
		<< "\n4: Print all orders"
		<< "\n5: Checkout orders"
		<< "\n6: Exit\n";

	cin >> choice;

	return choice;
}

void PlaceOrder(CustomerList& customers)
{
	string customerName;
	string address;
	string email;
	string choice = "y";
	string title;
	double price;
	int number;

	while (choice == "y")
	{
		cout << "Enter customer name: ";
		cin.ignore();
		getline(cin, customerName);

		bool found = customers.SearchCustomerByName(customerName);
		if (found) {
			cout << "Existing Customer.\n";

			cout << "Enter book title: ";
			getline(cin, title);
			cout << "Enter book price: ";
			cin >> price;
			cout << "Enter quantity: ";
			cin >> number;

			Order order(title, price, number);
			Customer customer = customers.getCustomerByName(customerName);
			customer.AddOrder(order);
			customers.UpdateCustomer(customer);
			cout << "New order is added for customer " << customerName << endl;
			cout << "Place another order (y or n)?";
			cin >> choice;
		}
		else {
			cout << "New Customer.\n" << "Enter customer address: ";
			getline(cin, address);
			cout << "Enter customer email: ";
			cin >> email;
			cout << "Enter book title: ";
			cin.ignore();
			getline(cin, title);
			cout << "Enter book price: ";
			cin >> price;
			cout << "Enter quantity: ";
			cin >> number;
			OrderList orderList;
			Customer newCustomer(customerName, address, email, orderList);
			Order order(title, price, number);
			newCustomer.AddOrder(order);
			customers.AddCustomer(newCustomer);
			cout << "New order is added for customer " << customerName << endl;
			cout << "Place another order (y or n)?";
			cin >> choice;
		}
	}
}

void UpdateOrder(CustomerList& customers)
{
	string customerName;
	cout << "Enter customer name: ";
	cin.ignore();
	getline(cin, customerName);

	bool found = customers.SearchCustomerByName(customerName);

	if (found) {
		cout << "Customer found.\n";
		string bookTitle;
		int number;
		cout << "Enter book title to update: ";
		getline(cin, bookTitle);
		cout << "Enter the number of books to be updated: ";
		cin >> number;

		Customer customer = customers.getCustomerByName(customerName);
		customer.UpdateOrders(bookTitle, number);
		customers.UpdateCustomer(customer);
		
		cout << "The order is updated.\n\n";
	}
	else {
		cout << "Customer does not exist.\n\n";
	}
}

void CancelOrder(CustomerList& customers)
{
	string customerName;
	cout << "Enter customer name: ";
	cin.ignore();
	getline(cin, customerName);

	bool found = customers.SearchCustomerByName(customerName);

	if (found) {
		string bookTitle;
		cout << "Enter book title to cancel: ";
		getline(cin, bookTitle);
		
		Customer customer = customers.getCustomerByName(customerName);
		customer.CancelOrder(bookTitle);
		customers.UpdateCustomer(customer);
		cout << "The order is canceled.\n\n";
	}
	else {
		cout << "Customer does not exist.\n\n";
	}
}

void PrintOrders(CustomerList& customers)
{
	linkedListIterator<Customer> iter = customers.begin();
	iter = customers.begin();
	while (iter != customers.end())
	{
		cout << *iter;
		++iter;
	}
}

void CheckoutOrders(CustomerList& customers)
{
	string customerName;
	cout << "Enter customer name: ";
	cin.ignore();
	getline(cin, customerName);

	bool found = customers.SearchCustomerByName(customerName);

	if (found) {
		double subtotal = customers.getCustomerByName(customerName).checkoutOrders();
		double tax = subtotal * 0.07;
		double total = subtotal + tax;
		cout << "******************************************************************" << endl;
		cout << "Name: " << customerName << endl;
		cout << "Address: " << customers.getCustomerByName(customerName).getAddress() << endl;
		cout << "Email: " << customers.getCustomerByName(customerName).getEmail() << endl;
		cout << customers.getCustomerByName(customerName).getOrders() << endl;
		cout << "******************************************************************" << endl;
		cout << "Subtotal: $" << subtotal << endl;
		cout << "Tax: $" << fixed << setprecision(2) << tax << endl;
		cout << "Total payment: $" << fixed << setprecision(2) << total << endl;
		cout << "******************************************************************" << endl;
	}
}

void UpdateDatafile(CustomerList& customers)
{
	ofstream outFile;
	outFile.open("BookOrders.txt", ios::out);

	customers.UpdateDataFile(outFile);
}
