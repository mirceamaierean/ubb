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
	this->length = 0;
}

// Best Case: Theta(1), Worst Case: Theta(n), Average Case: Theta(n)
void SortedMultiMap::add(TKey c, TValue v)
{
	Node *newNode = new Node;
	newNode->elem = TElem(c, v);
	if (this->head->next == nullptr)
	{
		this->head->next = newNode;
		newNode->prev = this->head;
	}
	else
	{
		Node *current = this->head->next;
		while (current != nullptr && this->rel(current->elem.first, c))
			current = current->next;
		if (current == nullptr)
		{
			current = this->head;
			while (current->next != nullptr)
				current = current->next;
			current->next = newNode;
			newNode->prev = current;
		}
		else
		{
			newNode->next = current;
			newNode->prev = current->prev;
			current->prev->next = newNode;
			current->prev = newNode;
		}
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
	while (current != nullptr && this->rel(current->elem.first, c))
	{
		if (current->elem.first == c && current->elem.second == v)
		{
			current->prev->next = current->next;
			if (current->next != nullptr)
				current->next->prev = current->prev;
			delete current;
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
	return this->head->next == nullptr;
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
	delete this->head;
}
