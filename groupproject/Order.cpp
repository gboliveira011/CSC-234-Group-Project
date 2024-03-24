#include "Order.h"

Order::Order()
{
	bookTitle = "";
	unitPrice = 0.0;
	number = 0;
}

Order::Order(string _bookTitle, double _unitPrice, int _number)
{
	bookTitle = _bookTitle;
	unitPrice = _unitPrice;
	number = _number;
}

bool Order::checkTitle(string name)
{
	return(bookTitle == name);
}

double Order::CalculateCost()
{
	return (unitPrice * number);
}

void Order::setNumber(int num)
{
	number = num;
}

string Order::getTitle()
{
	return bookTitle;
}

double Order::getPrice()
{
	return unitPrice;
}

int Order::getNumber()
{
	return number;
}

bool Order::operator==(const Order& other) const
{
	return (bookTitle == other.bookTitle);
}

bool Order::operator!=(const Order& other) const
{
	return (bookTitle != other.bookTitle);
}

ostream& operator<<(ostream& os, const Order& order)
{
	os << endl;
	os << "Title: " << order.bookTitle
		<< "\nUnit Price: $" <<  fixed << setprecision(2) << order.unitPrice
		<< "\n Number: " << order.number;

	return os;
}
