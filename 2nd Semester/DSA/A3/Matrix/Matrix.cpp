#include "Matrix.h"
#include <exception>

// Best case: Theta(1), Worst case: Theta(1), Average case: Theta(1)
Matrix::Matrix(int nrLines, int nrCols)
{
	this->nrL = nrLines;
	this->nrC = nrCols;
	this->capacity = 1;
	this->triplets = new Triple[capacity];
	this->next = new int[capacity];
	this->first = 0;
	this->firstFree = 0;
	this->next[0] = -1;
	this->size = 1;
}

// Best case: Theta(1), Worst case: Theta(1), Average case: Theta(1)
int Matrix::nrLines() const
{
	return this->nrL;
	return 0;
}

// Best case: Theta(1), Worst case: Theta(1), Average case: Theta(1)
int Matrix::nrColumns() const
{
	return this->nrC;
	return 0;
}

// Best case: O(1), Worst case: O(capacity), Average case: O(capacity)
TElem Matrix::element(int i, int j) const
{
	if (i < 0 || i >= this->nrL || j < 0 || j >= this->nrC)
		throw std::exception();
	std::pair<int, int> p = {i, j};
	int current = this->first;
	do
	{
		if (this->triplets[current].first == p)
			return this->triplets[current].second;
		current = this->next[current];
	} while (current != -1);
	return NULL_TELEM;
}

// Best case: O(1), Worst case: O(capacity), Average case: O(capacity)
void Matrix::resize()
{
	this->capacity *= 2;
	Triple *newTriplets = new Triple[this->capacity];
	int *newNext = new int[this->capacity];
	for (int i = 0; i < this->size; ++i)
	{
		newTriplets[i] = this->triplets[i];
		newNext[i] = this->next[i];
	}
	for (int i = this->size; i < this->capacity; ++i)
		newNext[i] = i + 1;
	newNext[this->capacity - 1] = -1;
	delete[] this->triplets;
	delete[] this->next;
	this->triplets = newTriplets;
	this->next = newNext;
	this->firstFree = this->size;
}

// Best case: O(1), Worst case: O(capacity), Average case: O(size)
TElem Matrix::modify(int i, int j, TElem e)
{
	int oldValue = 0;
	if (i < 0 || i >= this->nrL || j < 0 || j >= this->nrC)
		throw std::exception();
	std::pair<int, int> p = {i, j};
	int current = this->first, previous = -1, indexOfLargestSmallest = -1;
	do
	{
		if (this->triplets[current].first == p)
		{
			oldValue = this->triplets[current].second;
			if (e == NULL_TELEM)
			{
				if (previous == -1)
					this->first = this->next[current];
				else
					this->next[previous] = this->next[current];
				this->next[current] = this->firstFree;
				this->firstFree = current;
				this->size--;
				return oldValue;
			}
			this->triplets[current].second = e;
			return oldValue;
		}
		indexOfLargestSmallest = current;
		previous = current;
		current = this->next[current];
	} while (current != -1 && this->triplets[current].first <= p);
	if (this->capacity == this->size)
		this->resize();
	if (this->size == this->capacity / 2 - 1)
		this->downsize();

	// Insert element to ensure that those are lexicographically ordered
	int nextFree = this->next[firstFree];
	if (indexOfLargestSmallest == -1)
	{
		this->next[this->firstFree] = this->first;
		this->first = this->firstFree;
	}
	else
	{
		this->next[this->firstFree] = this->next[indexOfLargestSmallest];
		this->next[indexOfLargestSmallest] = this->firstFree;
	}
	this->triplets[this->firstFree] = {p, e};
	this->size++;
	this->firstFree = nextFree;
	return NULL_TELEM;
}

// Best case: O(1), Worst case: O(capacity), Average case: O(size)
void Matrix::resizeToNewDimensions(int newNrL, int newNrC)
{
	if (newNrL <= 0 || newNrC <= 0)
		throw std::exception();
	if (newNrL >= this->nrL && newNrC >= this->nrC)
		return;
	std::pair<int, int> dimensions = {newNrL, newNrC};
	this->nrL = newNrL;
	this->nrC = newNrC;
	Triple *newTriplets = new Triple[this->capacity];
	int *newNext = new int[this->capacity];
	int current = this->first, i = 0;
	do
	{
		// std::cout << this->triplets[current].first.first << " " << this->triplets[current].first.second << " " << this->triplets[current].second << "\n";
		if (this->triplets[current].first < dimensions)
		{
			newTriplets[i] = this->triplets[current];
			newNext[i] = i + 1;
			++i;
		}
		current = this->next[current];
	} while (current != -1);
	newNext[i] = -1;
	delete[] this->triplets;
	delete[] this->next;
	this->triplets = newTriplets;
	this->next = newNext;
	this->firstFree = this->size;
}

// Best case: Theta(1), Worst case: Theta(capacity), Average case: Theta(capacity)
void Matrix::downsize()
{
	this->capacity /= 2;
	Triple *newTriplets = new Triple[this->capacity];
	int *newNext = new int[this->capacity];
	int current = this->first, i = 0;
	do
	{
		newTriplets[i] = this->triplets[current];
		newNext[i] = i + 1;
		current = this->next[current];
		++i;
	} while (current != -1);
	newNext[this->capacity - 1] = -1;
	delete[] this->triplets;
	delete[] this->next;
	this->triplets = newTriplets;
	this->next = newNext;
	this->firstFree = this->size;
}
