#include "Set.h"
#include "SetIterator.h"
#include <string.h>
#include <iostream>

Set::Set()
{
	this->elements = new bool[1];
	for (int i = 0; i < 1; ++i)
		this->elements[i] = false;
	this->maxElem = NULL_TELEM;
	this->minElem = NULL_TELEM;
	this->nrOfElements = 0;
}

/// best case: theta(1) (when the element is between the the minimum and the maximum), worst case theta(max - elem/elem - min)(when we insert a new element, and we have to reconstruct the array), average case: theta(elem)
bool Set::add(TElem elem)
{
	// TODO - Implementation
	if (elem >= this->minElem && elem <= this->maxElem)
	{
		int positionOfElem = elem - this->minElem;
		if (this->elements[positionOfElem])
			return false;
		this->elements[positionOfElem] = true;
		this->nrOfElements++;
		return true;
	}

	if (elem > this->maxElem)
	{
		bool *newElements = new bool[elem - this->minElem + 1];
		for (int i = 0; i <= elem - this->minElem; ++i)
			newElements[i] = 0;
		for (int i = 0; i <= this->maxElem - this->minElem; ++i)
			newElements[i] = this->elements[i];

		delete[] this->elements;
		this->elements = newElements;

		if (this->minElem == NULL_TELEM)
			this->minElem = elem;

		this->elements[elem - this->minElem] = true;
		this->nrOfElements++;
		this->maxElem = elem;

		return true;
	}

	bool *newElements = new bool[this->maxElem - elem + 1];
	for (int i = 0; i <= this->maxElem - elem; ++i)
		newElements[i] = 0;
	for (int i = 0; i <= this->maxElem - this->minElem; ++i)
		newElements[i + this->minElem - elem] = this->elements[i];
	delete[] this->elements;
	this->elements = newElements;
	this->elements[0] = true;
	this->nrOfElements++;
	this->minElem = elem;

	return true;
}

/// best case: theta(1) (when the element is between the the minimum and the maximum), worst case theta(max - elem/elem - min)(we have to resize our array), average case: theta(max - elem/elem - min)
bool Set::remove(TElem elem)
{
	if (elem > this->minElem && elem < this->maxElem)
	{
		int positionOfElem = elem - this->minElem;
		if (!this->elements[positionOfElem])
			return false;
		this->elements[positionOfElem] = false;
		this->nrOfElements--;
		return true;
	}

	if (elem == this->minElem)
	{
		if (this->minElem == this->maxElem)
		{
			delete[] this->elements;
			this->elements = new bool[1];
			this->nrOfElements = 0;
			this->minElem = NULL_TELEM;
			this->maxElem = NULL_TELEM;
			return true;
		}
		int secondSmallestElem = 1;
		while (!this->elements[secondSmallestElem])
			++secondSmallestElem;
		bool *newElements = new bool[this->maxElem - this->minElem - secondSmallestElem + 1];
		for (int i = 0; i <= this->maxElem - this->minElem - secondSmallestElem; ++i)
			newElements[i] = 0;
		for (int i = secondSmallestElem; i <= this->maxElem - this->minElem; ++i)
			newElements[i - secondSmallestElem] = this->elements[i];
		delete[] this->elements;
		this->elements = newElements;
		this->minElem += secondSmallestElem;
		this->nrOfElements--;
		return true;
	}

	if (elem == this->maxElem)
	{
		int secondBiggestElem = this->maxElem - this->minElem - 1;
		while (!this->elements[secondBiggestElem])
			--secondBiggestElem;
		bool *newElements = new bool[secondBiggestElem + 1];
		for (int i = 0; i <= secondBiggestElem; ++i)
			newElements[i] = 0;
		for (int i = 0; i <= secondBiggestElem; ++i)
			newElements[i] = this->elements[i];
		delete[] this->elements;
		this->elements = newElements;
		this->maxElem = this->minElem + secondBiggestElem;
		this->nrOfElements--;
		return true;
	}

	return false;
}

/// best case: theta(1), worst case theta(1), average case: theta(1)
bool Set::search(TElem elem) const
{
	if (elem >= this->minElem && elem <= this->maxElem)
	{
		int positionOfElem = elem - this->minElem;
		return this->elements[positionOfElem];
	}
	return false;
}

/// best case: theta(1), worst case theta(1), average case: theta(1)
int Set::size() const
{
	return this->nrOfElements;
}

/// best case: theta(1), worst case theta(1), average case: theta(1)
bool Set::isEmpty() const
{
	return this->nrOfElements == 0;
}
// Best Case: Theta(1) (when the minimum is equal to the maximum), Worst Case: Theta(max - min) (when we have to resize the array), Average Case: Theta(max - min)
void Set::filter(Condition cond)
{
	if (this->maxElem == NULL_TELEM)
		throw std::exception();
	for (int i = 0; i <= this->maxElem - this->minElem; ++i)
		if (this->elements[i] && !cond(this->minElem + i))
		{
			this->elements[i] = false;
			this->nrOfElements--;
		}
}

Set::~Set()
{
	delete[] this->elements;
}

SetIterator Set::iterator() const
{
	return SetIterator(*this);
}
