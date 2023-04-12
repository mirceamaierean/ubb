#include "SMMIterator.h"
#include "SortedMultiMap.h"

// Best Case: Theta(1), Worst Case: Theta(1), Average Case: Theta(1)
SMMIterator::SMMIterator(const SortedMultiMap &d) : map(d)
{
	this->current = nullptr;
}

SMMIterator &SMMIterator::operator=(const SMMIterator &other)
{
	this->current = other.current;
	return *this;
}

// Best Case: Theta(1), Worst Case: Theta(1), Average Case: Theta(1)
void SMMIterator::first()
{
	this->current = map.head->next;
}

void SMMIterator::last()
{
	this->current = map.tail->prev;
}

// Best Case: Theta(1), Worst Case: Theta(1), Average Case: Theta(1)
void SMMIterator::next()
{
	if (map.isEmpty())
		throw exception();
	if (this->current == nullptr)
	{
		this->first();
		return;
	}
	if (this->current == map.tail)
		throw exception();
	this->current = this->current->next;
}

void SMMIterator::previous()
{
	if (map.isEmpty())
		throw exception();
	if (this->current == nullptr)
	{
		this->last();
		return;
	}
	if (map.isEmpty() || this->current == map.head)
		throw exception();
	this->current = this->current->prev;
}

// Best Case: Theta(1), Worst Case: Theta(1), Average Case: Theta(1)
bool SMMIterator::valid() const
{
	return (map.size() && this->current != map.tail && this->current != map.head);
}

// Best Case: Theta(1), Worst Case: Theta(1), Average Case: Theta(1)
TElem SMMIterator::getCurrent()
{
	if (map.isEmpty())
		throw exception();
	if (this->current == nullptr)
	{
		this->first();
		return this->current->elem;
	}
	if (map.isEmpty() || this->current == map.tail)
		throw exception();
	return this->current->elem;
}
