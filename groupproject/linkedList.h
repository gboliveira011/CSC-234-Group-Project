#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
#include <cassert>
using namespace std;

template <class Type>
struct nodeType
{
    Type info;
    nodeType<Type>* link;
};

template <class Type>
class linkedListIterator
{
public:
    linkedListIterator();
    linkedListIterator(nodeType<Type>* ptr);
    Type operator*();
    linkedListIterator<Type> operator++();
    bool operator==(const linkedListIterator<Type>& right) const;
    bool operator!=(const linkedListIterator<Type>& right) const;
private:
    nodeType<Type>* current;
};

template <class Type>
linkedListIterator<Type>::linkedListIterator()
{
    current = nullptr;
}

template <class Type>
linkedListIterator<Type>::linkedListIterator(nodeType<Type>* ptr)
{
    current = ptr;
}

template <class Type>
Type linkedListIterator<Type>::operator*()
{
    return current->info;
}

template <class Type>
linkedListIterator<Type> linkedListIterator<Type>::operator++()
{
    current = current->link;
    return *this;
}

template <class Type>
bool linkedListIterator<Type>::operator==(const linkedListIterator<Type>& right) const
{
    return (current == right.current);
}

template <class Type>
bool linkedListIterator<Type>::operator!=(const linkedListIterator<Type>& right) const
{
    return (current != right.current);
}


//*****************  class linkedListType   ****************

template <class Type>
class linkedListType
{
public:
    const linkedListType<Type>& operator=(const linkedListType<Type>&);
    void initializeList();
    bool isEmptyList() const;
    void print() const;
    int length() const;
    void destroyList();
    Type front() const;
    Type back() const;
    bool search(const Type& searchItem) const;
    void insertFirst(const Type& newItem);
    void insertLast(const Type& newItem);
    void deleteNode(const Type& deleteItem);
    linkedListIterator<Type> begin() const;
    linkedListIterator<Type> end() const;
    linkedListType();
    linkedListType(const linkedListType<Type>& otherList);
    ~linkedListType();
protected:
    int count;
    nodeType<Type>* first;
    nodeType<Type>* last;
private:
    void copyList(const linkedListType<Type>& otherList);
};

template <class Type>
bool linkedListType<Type>::isEmptyList() const
{
    return (first == nullptr);
}

template <class Type>
linkedListType<Type>::linkedListType()
{
    first = nullptr;
    last = nullptr;
    count = 0;
}

template <class Type>
void linkedListType<Type>::destroyList()
{
    nodeType<Type>* temp;
    while (first != nullptr)
    {
        temp = first;
        first = first->link;
        delete temp;
    }
    last = nullptr;
    count = 0;
}

template <class Type>
void linkedListType<Type>::initializeList()
{
    destroyList();
}

template <class Type>
void linkedListType<Type>::print() const
{
    nodeType<Type>* current;
    current = first;
    while (current != nullptr)
    {
        cout << current->info << " ";
        current = current->link;
    }
}

template <class Type>
int linkedListType<Type>::length() const
{
    return count;
}

template <class Type>
Type linkedListType<Type>::front() const
{
    assert(first != nullptr);
    return first->info;
}

template <class Type>
Type linkedListType<Type>::back() const
{
    assert(last != nullptr);
    return last->info;
}

template <class Type>
bool linkedListType<Type>::search(const Type& searchItem) const
{
    nodeType<Type>* current;
    bool found = false;
    current = first;
    while (current != nullptr && !found)
        if (current->info == searchItem)
            found = true;
        else
            current = current->link;
    return found;
}

template <class Type>
void linkedListType<Type>::insertFirst(const Type& newItem)
{
    nodeType<Type>* newNode;
    newNode = new nodeType<Type>;
    newNode->info = newItem;
    newNode->link = first;
    first = newNode;
    count++;
    if (last == nullptr)
        last = newNode;
}

template <class Type>
void linkedListType<Type>::insertLast(const Type& newItem)
{
    nodeType<Type>* newNode;
    newNode = new nodeType<Type>;
    newNode->info = newItem;
    newNode->link = nullptr;
    if (first == nullptr)
    {
        first = newNode;
        last = newNode;
        count++;
    }
    else
    {
        last->link = newNode;
        last = newNode;
        count++;
    }
}

template <class Type>
void linkedListType<Type>::deleteNode(const Type& deleteItem)
{
    nodeType<Type>* current;
    nodeType<Type>* trailCurrent;
    bool found;
    if (first == nullptr)
        cout << "Cannot delete from an empty list." << endl;
    else
    {
        if (first->info == deleteItem)
        {
            current = first;
            first = first->link;
            count--;
            if (first == nullptr)
                last = nullptr;
            delete current;
        }
        else
        {
            found = false;
            trailCurrent = first;
            current = first->link;
            while (current != nullptr && !found)
            {
                if (current->info != deleteItem)
                {
                    trailCurrent = current;
                    current = current->link;
                }
                else
                    found = true;
            }
            if (found)
            {
                trailCurrent->link = current->link;
                count--;
                if (last == current)
                    last = trailCurrent;
                delete current;
            }
            else
                cout << "The item to be deleted is not in "
                << "the list." << endl;
        }
    }
}
template <class Type>
linkedListIterator<Type> linkedListType<Type>::begin() const
{
    linkedListIterator<Type> temp(first);
    return temp;
}

template <class Type>
linkedListIterator<Type> linkedListType<Type>::end() const
{
    linkedListIterator<Type> temp(nullptr);
    return temp;
}

template <class Type>
void linkedListType<Type>::copyList(const linkedListType<Type>& otherList)
{
    nodeType<Type>* newNode;
    nodeType<Type>* current;
    if (first != nullptr)
        destroyList();
    if (otherList.first == nullptr)
    {
        first = nullptr;
        last = nullptr;
        count = 0;
    }
    else
    {
        current = otherList.first;
        count = otherList.count;
        first = new nodeType<Type>;
        first->info = current->info;
        first->link = nullptr;
        last = first;
        current = current->link;
        while (current != nullptr)
        {
            newNode = new nodeType<Type>;
            newNode->info = current->info;
            newNode->link = nullptr;
            last->link = newNode;
            last = newNode;
            current = current->link;
        }
    }
}

template <class Type>
linkedListType<Type>::~linkedListType()
{
    destroyList();
}

template <class Type>
linkedListType<Type>::linkedListType(const linkedListType<Type>& otherList)
{
    first = nullptr;
    copyList(otherList);
}

template <class Type>
const linkedListType<Type>& linkedListType<Type>::operator=(const linkedListType<Type>& otherList)
{
    if (this != &otherList)
    {
        copyList(otherList);
    }
    return *this;
}
#endif
