#pragma once

#ifndef NODE
#define NODE
#define NULL 0

// Minimalist node class with public data attributes.
template <class type>
class node
{
public:
	// default constructor initializes data value to '?'
	// and next pointer to NULL
	node();

	// constructor initializes data value to given value 
	// and next pointer to NULL
	node(type input);

	// A node HAS-A value and next pointer.

	// Integer data value.
	type data;

	// pointer to node that follows this node. Value is NULL if none.
	node* next;

	// pinter to node that came before this node. Value in NULL if none.
	node* previous;
};

// default constructor initializes data value to '?'
// and next pointer to NULL
template <class type>
node<type>::node() {
	this->next = NULL;
	this->previous = NULL;
}

// constructor initializes data value to given value 
// and next pointer to NULL
template <class type>
node<type>::node(type input) {
	this->data = input;
	this->next = NULL;
	this->previous = NULL;
}

#endif // !NODE