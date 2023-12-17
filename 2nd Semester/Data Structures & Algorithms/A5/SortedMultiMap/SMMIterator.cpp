#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>

// Best case: Theta(1), Worst case: Theta(n), Average case: Theta(n)
void SMMIterator::DFS(Node *node)
{
	if (node == NULL)
		return;

	this->DFS(node->left);

	for (int i = 0; i < node->size; ++i)
		this->elements[this->numberOfElements++] = TElem(node->key, node->values[i]);

	this->DFS(node->right);
}

// Best case: Theta(1), Worst case: Theta(n), Average case: Theta(n)
SMMIterator::SMMIterator(const SortedMultiMap &d) : map(d)
{
	this->capacity = this->map.sizeOfBST;
	this->elements = new TElem[this->capacity];
	this->currentElement = 0;
	this->numberOfElements = 0;
	this->DFS(this->map.root);
}

// Best case: Theta(1), Worst case: Theta(1), Average case: Theta(1)
void SMMIterator::first()
{
	this->currentElement = 0;
}

// Best case: Theta(1), Worst case: Theta(1), Average case: Theta(1)
void SMMIterator::next()
{
	if (!this->valid())
		throw std::exception();
	this->currentElement++;
}

// Best case: Theta(1), Worst case: Theta(1), Average case: Theta(1)
bool SMMIterator::valid() const
{
	return this->currentElement < this->numberOfElements;
}

// Best case: Theta(1), Worst case: Theta(1), Average case: Theta(1)
TElem SMMIterator::getCurrent() const
{
	if (!this->valid())
		throw std::exception();
	return this->elements[this->currentElement];
}

// Best case: Theta(1), Worst case: Theta(1), Average case: Theta(1)
SMMIterator::~SMMIterator()
{
	delete[] this->elements;
}