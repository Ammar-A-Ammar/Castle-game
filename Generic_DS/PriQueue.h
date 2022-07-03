#pragma once

#include"Generic_DS\Node.h"


template <typename T>
class PriQueue
{
private:
	Node<T>* backPtr;
	Node<T>* frontPtr;
public:

	PriQueue()
	{
		backPtr = nullptr;
		frontPtr = nullptr;
	}
	bool isEmpty() const
	{
		if (frontPtr == nullptr)
		{
			return true;
		}
		return false;
	}
	bool enqueue(const T& newEntry, int priority)
	{
		if (isEmpty())
		{
			Node<T>* newNodePtr = new Node<T>(newEntry, nullptr, priority);
			frontPtr = newNodePtr;
			backPtr = newNodePtr;
			return true;
		}
		else
		{

			if (frontPtr->getpriority() < priority)
			{
				Node<T>* newNodePtr = new Node<T>(newEntry, frontPtr, priority);
				newNodePtr->setNext(frontPtr);
				frontPtr = newNodePtr;
				return true;
			}
			else if (frontPtr->getpriority() > priority && frontPtr == backPtr)
			{
				Node<T>* newNodePtr = new Node<T>(newEntry, nullptr, priority);
				newNodePtr->setNext(nullptr);
				backPtr = newNodePtr;
				frontPtr->setNext(backPtr);
				return true;
			}
			else
			{
				Node<T>* ptr = frontPtr;
				while (ptr->getNext())
				{
					if (ptr->getNext()->getpriority() < priority)
					{
						Node<T>* newNodePtr = new Node<T>(newEntry, ptr->getNext(), priority);
						ptr->setNext(newNodePtr);
						return true;
					}
					ptr = ptr->getNext();
				}
				Node<T>* newNodePtr = new Node<T>(newEntry, nullptr, priority);

				ptr->setNext(newNodePtr);

				backPtr = newNodePtr;
			}

		}
		return true;
	}

	bool dequeue(T& frntEntry)
	{
		if (isEmpty())
			return false;

		Node<T>* nodeToDeletePtr = frontPtr;
		frntEntry = frontPtr->getItem();
		frontPtr = frontPtr->getNext();
		if (nodeToDeletePtr == backPtr)
			backPtr = nullptr;
		delete nodeToDeletePtr;


		return true;
	}

	bool peekFront(T& frntEntry)  const
	{
		if (isEmpty())
			return false;

		frntEntry = frontPtr->getItem();
		return true;
	}


	T* toArray(int& count)
	{
		count = 0;

		if (!frontPtr)
			return nullptr;
		//counting the no. of items in the Queue
		Node<T>* p = frontPtr;
		while (p)
		{
			count++;
			p = p->getNext();
		}


		T* Arr = new T[count];
		p = frontPtr;
		for (int i = 0; i < count;i++)
		{
			Arr[i] = p->getItem();
			p = p->getNext();
		}
		return Arr;
	}

};