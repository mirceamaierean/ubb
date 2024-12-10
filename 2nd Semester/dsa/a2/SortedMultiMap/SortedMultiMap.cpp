#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

// Best Case: Theta(1), Worst Case: Theta(1), Average Case: Theta(1)
SortedMultiMap::SortedMultiMap(Relation r)
{
	this->rel = r;
	this->head = new Node;
	this->tail = new Node;
	this->length = 0;
}

// Best Case: Theta(1), Worst Case: Theta(n), Average Case: Theta(n)
void SortedMultiMap::addToHead(TKey c, TValue v)
{
	Node *newNode = new Node;
	newNode->elem = TElem(c, v);
	if (this->head->next == nullptr)
	{
		this->head->next = newNode;
		newNode->prev = this->head;
		newNode->next = this->tail;
		this->tail->prev = newNode;
	}
	else
	{
		Node *current = this->head->next, *previous = this->head;
		while (current != nullptr && this->rel(current->elem.first, c))
		{
			previous = current;
			current = current->next;
		}
		if (current == nullptr)
		{
			current = previous;
			current->next = newNode;
			newNode->prev = current;
			this->tail->prev = newNode;
		}
		else
		{
			newNode->next = current;
			newNode->prev = current->prev;
			current->prev->next = newNode;
			current->prev = newNode;
		}
	}
}

// Best Case: Theta(1), Worst Case: Theta(n), Average Case: Theta(n)
void SortedMultiMap::addToTail(TKey c, TValue v)
{
	Node *newNode = new Node;
	newNode->elem = TElem(c, v);
	if (this->tail->prev == nullptr)
	{
		this->tail->prev = newNode;
		newNode->next = this->tail;
		newNode->prev = this->head;
		this->head->next = newNode;
	}
	else
	{
		Node *current = this->tail->prev;
		while (current != this->head && this->rel(c, current->elem.first))
			current = current->prev;
		current->next->prev = newNode;
		newNode->next = current->next;
		current->next = newNode;
		newNode->prev = current;
	}
}

void SortedMultiMap::add(TKey c, TValue v)
{
	if (this->tail->elem.first <= c)
	{
		this->addToTail(c, v);
	}
	else
	{
		this->addToHead(c, v);
	}
	++this->length;
}

// Best Case: Theta(1), Worst Case: Theta(n), Average Case: Theta(n)
vector<TValue> SortedMultiMap::search(TKey c) const
{
	vector<TValue> values;
	Node *current = this->head->next;
	while (current != nullptr && this->rel(current->elem.first, c))
	{
		if (current->elem.first == c)
			values.push_back(current->elem.second);
		current = current->next;
	}
	return values;
}

// Best Case: Theta(1), Worst Case: Theta(n), Average Case: Theta(n)
bool SortedMultiMap::remove(TKey c, TValue v)
{
	Node *current = this->head->next;
	while (current != this->tail && this->rel(current->elem.first, c))
	{
		if (current->elem.first == c && current->elem.second == v)
		{
			Node *previous = current->prev, *next = current->next;
			previous->next = next;
			next->prev = previous;
			--this->length;
			return true;
		}
		current = current->next;
	}
	return false;
}

// Best Case: Theta(1), Worst Case: Theta(1), Average Case: Theta(1)
int SortedMultiMap::size() const
{
	return this->length;
}

// Best Case: Theta(1), Worst Case: Theta(1), Average Case: Theta(1)
bool SortedMultiMap::isEmpty() const
{
	return this->length == 0;
}

// Best Case: Theta(1), Worst Case: Theta(1), Average Case: Theta(1)
SMMIterator SortedMultiMap::iterator() const
{
	return SMMIterator(*this);
}

// Best Case: Theta(1), Worst Case: Theta(n), Average Case: Theta(n)
SortedMultiMap::~SortedMultiMap()
{
	Node *current = this->head->next;
	while (current != nullptr)
	{
		Node *next = current->next;
		delete current;
		current = next;
	}
	if (this->head != nullptr)
		delete this->head;
}
