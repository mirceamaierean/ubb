#include "SetIterator.h"
#include "Set.h"
#include <iostream>

SetIterator::SetIterator(const Set &m) : set(m)
{
	this->index = 0;
}

/// best case: theta(1), worst case theta(1), average case: theta(1)
void SetIterator::first()
{
	this->index = 0;
}

/// best case: theta(1), worst case theta(max-min), average case: theta(elem)
void SetIterator::next()
{
	if (this->set.nrOfElements == 0 || this->index == -1)
		throw std::exception();
	this->index++;
	if (this->index >= this->set.maxElem - this->set.minElem + 1)
		this->index = -1;
	else
	{
		while (this->index <= this->set.maxElem - this->set.minElem && !this->set.elements[this->index])
			this->index++;

		if (this->index >= this->set.maxElem - this->set.minElem + 1)
			this->index = -1;
	}
}

/// best case: theta(1), worst case theta(1), average case: theta(1)
TElem SetIterator::getCurrent()
{
	if (this->set.nrOfElements == 0 || this->index == -1)
		throw std::exception();
	return this->index + this->set.minElem;
}

/// best case: theta(1), worst case theta(1), average case: theta(1)
bool SetIterator::valid() const
{
	if (this->set.nrOfElements == 0)
		return false;
	return this->index != -1;
}
