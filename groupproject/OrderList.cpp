#include "OrderList.h"

ostream& operator<<(ostream& os, const OrderList& orderList)
{
    linkedListIterator<Order> iter = orderList.begin();


    os << "\n--------------- Book Orders ---------------\n";
    while (iter != orderList.end())
    {
        os << *iter << " ";
        ++iter;
    }
    return os;
}

void OrderList::AddOrder(Order& order)
{
    insertLast(order);
}

void OrderList::UpdateOrder(string title, int num)
{
    bool found = false;
    nodeType<Order>* location;

    SearchOrderList(title, found, location);

    if (found)
    {
        location->info.setNumber(num);
    }
    else
    {
        cout << "Book title not found.\n";
    }
}

void OrderList::CancelOrder(string title)
{
    bool found = false;
    nodeType<Order>* location;

    SearchOrderList(title, found, location);

    if (found)
    {
        deleteNode(location->info);
    }
    else
    {
        cout << "Book title not found.\n";
    }
}

double OrderList::CalculateSubtotal()
{
    double subtotal = 0.0;
    double price = 0.0;
    int number = 0;
    nodeType<Order>* current = first;

    while (current != nullptr) {
        price = current->info.getPrice();
        number = current->info.getNumber();
        subtotal += price * number;
        current = current->link;
    }
    return subtotal;
}

void OrderList::UpdateDataFile(ofstream& outFile)
{
    nodeType<Order>* current = first;

    while (current != nullptr) {
        outFile << current->info.getTitle() << endl;
        outFile << fixed << setprecision(2) << current->info.getPrice() << endl;
        outFile << current->info.getNumber() << endl;
        current = current->link;
    }
}

void OrderList::SearchOrderList(string title, bool& found, nodeType<Order>*& current) const
{
    found = false;

    current = first;

    while (current != nullptr && !found)
    {
        if (current->info.checkTitle(title))
        {
            found = true;
        }
        else
        {
            current = current->link;
        }
    }
}
