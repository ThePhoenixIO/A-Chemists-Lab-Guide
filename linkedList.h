#pragma once
#include "node.h"

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

	node<type>* getFirst();

	node<type>* getLast();

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
inline node<type>* linkedList<type>::getFirst()
{
	return first;
}

template<typename type>
inline node<type>* linkedList<type>::getLast()
{
	return last;
}

#endif // !LINKEDLIST