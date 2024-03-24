#include "Customer.h"

Customer::Customer() {
    name = "";
    address = "";
    email = "";
    orders = OrderList();
}

Customer::Customer(string n, string addr, string _email, OrderList ord) {
    name = n;
    address = addr;
    email = _email;
    orders = ord;
}

OrderList Customer::getOrders() {
    return orders;
}

void Customer::AddOrder(Order newOrder) {
    orders.AddOrder(newOrder);
}

void Customer::UpdateOrders(string title, int newQuantity) {
    orders.UpdateOrder(title, newQuantity);
}

void Customer::CancelOrder(string title) {
    orders.CancelOrder(title);
}

string Customer::getCustomerName() {
    return name;
}

string Customer::getAddress() {
    return address;
}

string Customer::getEmail() {
    return email;
}

double Customer::checkoutOrders() {
    return orders.CalculateSubtotal();
}

bool Customer::operator==(const Customer& other) const {
    return (name == other.name && address == other.address && email == other.email);
}

bool Customer::operator!=(const Customer& other) const {
    return !(*this == other);
}

ostream& operator<<(ostream& os, const Customer& customer)
{
    os << "\nName: " << customer.name << "\nAddress: " << customer.address << "\nEmail: " << customer.email << endl << customer.orders << endl;

    return os;
}
