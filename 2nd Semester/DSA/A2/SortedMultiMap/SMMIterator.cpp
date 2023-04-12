#include "SMMIterator.h"
#include "SortedMultiMap.h"

// Best Case: Theta(1), Worst Case: Theta(1), Average Case: Theta(1)
SMMIterator::SMMIterator(const SortedMultiMap &d) : map(d)
{
	this->current = map.head;
}

// Best Case: Theta(1), Worst Case: Theta(1), Average Case: Theta(1)
void SMMIterator::first()
{
	this->current = map.head;
}

// Best Case: Theta(1), Worst Case: Theta(1), Average Case: Theta(1)
void SMMIterator::next()
{
	if (this->current->next == nullptr)
		throw exception();
	this->current = this->current->next;
}

// Best Case: Theta(1), Worst Case: Theta(1), Average Case: Theta(1)
bool SMMIterator::valid() const
{
	if (this->current != nullptr && this->current->next != nullptr)
		return true;
	return false;
}

// Best Case: Theta(1), Worst Case: Theta(1), Average Case: Theta(1)
TElem SMMIterator::getCurrent() const
{
	if (this->current->next == nullptr)
		throw exception();
	return this->current->next->elem;
}
