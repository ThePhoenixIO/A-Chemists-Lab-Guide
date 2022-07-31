#pragma once
#include "node.h"
#include <iostream>

#ifndef LINKEDLIST
#define LINKEDLIST

template<typename type>
class linkedList
{
public:
	linkedList();

	linkedList(type data);

	linkedList(type dataArray[]);

	void append(type data);

	bool insert(type data);

	node<type>* getFirst();

	node<type>* getLast();

	void clear();

protected:
	node<type>* first;
	node<type>* last;
};

template<typename type>
linkedList<type>::linkedList()
{
	this->first = NULL;
	this->last = NULL;
}

template<typename type>
linkedList<type>::linkedList(type data)
{
	this->first = new node<type>(data);
	this->last = first;
	this->first->previous = NULL;
}

template<typename type>
linkedList<type>::linkedList(type dataArray[])
{
	this->first = new node<type>(dataArray[0]);
	this->last = first;
	this->first->previous = NULL;

	for (int n = 1; n < sizeof(dataArray); n++)
	{
		node<type>* temp = new node<type>(dataArray[n]);
		temp->previous = last;
		this->last->next = temp;
		this->last = temp;
	}
}

template<typename type>
inline void linkedList<type>::append(type data)
{
	node<type>* temp = new node<type>(data);
	temp->previous = last;
	if (last == NULL)
	{
		this->first = temp;
		this->last = temp;
	}
	else
	{
		this->last->next = temp;
		this->last = temp;
	}
}

template<typename type>
inline bool linkedList<type>::insert(type data)
{
	node<type>* current = first;

	do
	{
		if (current->next->data > data)
		{
			if (current->data != data)
			{
				node<type>* temp = new node<type>(data);

				// Connecting temp node to list
				temp->next = current->next;
				temp->previous = current;

				// Cleaning-up links
				current->next = temp;
				temp->next->previous = temp;

				temp = NULL;
				return true;
			}
			else
			{
				std::cout << "Equivalnce Point value was included in user volumes, and will be ignored." << std::endl;
				return false;
			}
		}
		current = current->next;
	} while (current != last);
}

template<typename type>
inline node<type>* linkedList<type>::getFirst()
{
	return first;
}

template<typename type>
inline node<type>* linkedList<type>::getLast()
{
	return last;
}

template<typename type>
inline void linkedList<type>::clear()
{
	node<type>* temp = NULL;
	node<type>* current = first;

	while (current != NULL)
	{
		temp = current;
		current = current->next;
		delete temp;
	}

	this->first = NULL;
	this->last = NULL;
}

#endif // !LINKEDLIST