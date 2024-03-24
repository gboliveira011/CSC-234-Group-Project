#include "CustomerList.h"


void CustomerList::AddCustomer(Customer& newCustomer) {
    if (!SearchCustomerByName(newCustomer.getCustomerName())) {
        insertLast(newCustomer);
    }
}

bool CustomerList::SearchCustomerByName(string name) const {
    nodeType<Customer>* current = first;
    bool found = false;

    while (current != nullptr && !found) {
        if (current->info.getCustomerName() == name) {
            found = true;
        }
        else {
            current = current->link;
        }
    }

    return found;
}

Customer CustomerList::getCustomerByName(string name) const {
    nodeType<Customer>* current = first;

    while (current != nullptr) {
        if (current->info.getCustomerName() == name) {
            return current->info;
        }
        else {
            current = current->link;
        }
    }

    // Return an empty customer if not found (you may want to handle this differently)
    return Customer();
}

void CustomerList::UpdateCustomer(Customer& updatedCustomer) {
    nodeType<Customer>* current = first;

    while (current != nullptr) {
        if (current->info == updatedCustomer) {
            current->info = updatedCustomer;
            return;
        }
        else {
            current = current->link;
        }
    }
}

ostream& operator<<(ostream& os, const CustomerList& customers)
{
    linkedListIterator<Customer> iter = customers.begin();

    while (iter != customers.end())
    {
        os << *iter << " ";
        ++iter;
    }
    return os;
}


void CustomerList::UpdateDataFile(ofstream& outFile) {
    nodeType<Customer>* current = first;

    while (current != nullptr) {
        outFile << "%" << current->info.getCustomerName() << endl;
        outFile << current->info.getAddress() << endl;
        outFile << current->info.getEmail() << endl;
        current->info.getOrders().UpdateDataFile(outFile);
        current = current->link;
    }
}

