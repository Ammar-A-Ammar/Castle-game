#pragma once
#pragma once

template < typename T>
class PriNode
{
private:
	T item; // A data item
	PriNode<T>* next;
	int priority; // Pointer to next node
public:
	PriNode();
	PriNode(const T& r_Item);	//passing by const ref.
	PriNode(const T& r_Item, PriNode<T>* nextNodePtr);
	void setItem(const T& r_Item);
	void setNext(PriNode<T>* nextNodePtr);
	T getItem() const;
	PriNode<T>* getNext() const;
	void setP(int P);
	int getP() const;
}; // end Node


template < typename T>
PriNode<T>::PriNode()
{
	next = nullptr;
}

template < typename T>
PriNode<T>::PriNode(const T& r_Item)
{
	item = r_Item;
	next = nullptr;
}

template < typename T>
PriNode<T>::PriNode(const T& r_Item, PriNode<T>* nextNodePtr)
{
	item = r_Item;
	next = nextNodePtr;
}
template < typename T>
void PriNode<T>::setItem(const T& r_Item)
{
	item = r_Item;
}

template < typename T>
void PriNode<T>::setNext(PriNode<T>* nextNodePtr)
{
	next = nextNodePtr;
}

template < typename T>
T PriNode<T>::getItem() const
{
	return item;
}

template < typename T>
PriNode<T>* PriNode<T>::getNext() const
{
	return next;
}
template < typename T>
void PriNode<T>::setP(int P)
{
	priority = P;
}
template < typename T>
int PriNode<T>::getP() const
{
	return priority;
}


