// using a hashtable with coalesced chaining
#include "SortedSet.h"
#include "SortedSetIterator.h"
#include <iostream>

void SortedSet::resize(int newCapacity)
{
	int oldCapacity = this->capacity;
	this->capacity = newCapacity;
	this->firstEmpty = 0;
	int *newNext = new int[newCapacity];
	TElem *newElements = new TElem[newCapacity];

	for (int i = 0; i < this->capacity; ++i)
	{
		newNext[i] = -1;
		newElements[i] = NULL_TELEM;
	}

	for (int i = 0; i < oldCapacity; ++i)
	{
		if (this->elements[i] != NULL_TELEM)
		{
			int position = this->hashFunction(this->elements[i]);
			if (newElements[position] == NULL_TELEM)
				newElements[position] = this->elements[i];
			else
			{
				while (newNext[position] != -1)
					position = newNext[position];
				newElements[this->firstEmpty] = this->elements[i];
				newNext[position] = this->firstEmpty;
			}
			while (this->firstEmpty < this->capacity && newElements[this->firstEmpty] != NULL_TELEM)
				++this->firstEmpty;
		}
	}

	delete[] this->next;
	delete[] this->elements;
	this->next = newNext;
	this->elements = newElements;
}

SortedSet::SortedSet(Relation r)
{
	this->rel = r;
	this->capacity = INITIAL_CAPACITY;
	this->nrElements = 0;
	this->next = new int[this->capacity];
	this->elements = new TElem[this->capacity];
	this->firstEmpty = 0;
	for (int i = 0; i < this->capacity; ++i)
	{
		this->next[i] = -1;
		this->elements[i] = NULL_TELEM;
	}
}

bool SortedSet::add(TComp elem)
{
	if (this->search(elem))
		return false;

	++this->nrElements;

	if (this->requiresResize())
		this->resize(this->capacity * 2);

	int position = this->hashFunction(elem);

	if (this->elements[position] == NULL_TELEM)
		this->elements[position] = elem;
	else
	{
		while (this->next[position] != -1)
			position = this->next[position];

		this->elements[this->firstEmpty] = elem;
		this->next[position] = this->firstEmpty;
	}
	while (this->firstEmpty < this->capacity && this->elements[firstEmpty] != NULL_TELEM)
		++this->firstEmpty;

	return true;
}

bool SortedSet::remove(TComp elem)
{
	if (!this->search(elem))
		return false;

	--this->nrElements;

	int position = this->hashFunction(elem);
	int prevPosition = -1;
	while (this->elements[position] != elem)
	{
		prevPosition = position;
		position = this->next[position];
	}
	if (prevPosition == -1)
	{
		this->elements[position] = NULL_TELEM;
		this->next[position] = -1;
	}
	else
	{
		this->elements[position] = NULL_TELEM;
		this->next[prevPosition] = this->next[position];
		this->next[position] = -1;
	}

	if (position < this->firstEmpty)
		this->firstEmpty = position;

	if (this->requireDownsize())
		this->resize(this->capacity / 2);

	return true;
}

bool SortedSet::search(TElem elem) const
{
	int position = this->hashFunction(elem);
	while (position != -1 && this->elements[position] != elem)
		position = this->next[position];
	if (position == -1)
		return false;
	if (this->elements[position] == elem)
		return true;
	return true;
}

int SortedSet::size() const
{
	return this->nrElements;
	return 0;
}

bool SortedSet::isSubset(const SortedSet &s) const
{
	SortedSetIterator it(s);
	while (it.valid())
	{
		if (!this->search(it.getCurrent()))
			return false;
		it.next();
	}
	return true;
}

bool SortedSet::isEmpty() const
{
	return this->nrElements == 0;
	return false;
}

SortedSetIterator SortedSet::iterator() const
{
	SortedSetIterator it(*this);
	return it;
}

SortedSet::~SortedSet()
{
	delete[] this->elements;
	delete[] this->next;
}
