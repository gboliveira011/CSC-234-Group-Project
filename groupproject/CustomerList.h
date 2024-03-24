#pragma once
#include"Customer.h"
#include"linkedList.h"
#include<fstream>

class CustomerList :public linkedListType<Customer>
{
	friend ostream& operator<<(ostream&, const CustomerList&);
public:
	void AddCustomer(Customer&);
	bool SearchCustomerByName(string) const;
	Customer getCustomerByName(string) const;
	void UpdateCustomer(Customer&);
	void UpdateDataFile(ofstream&);
};