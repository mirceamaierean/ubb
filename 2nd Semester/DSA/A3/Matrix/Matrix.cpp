#include "Matrix.h"
#include <exception>

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

int Matrix::nrLines() const
{
	return this->nrL;
	return 0;
}

int Matrix::nrColumns() const
{
	return this->nrC;
	return 0;
}

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

void Matrix::resize()
{
	this->capacity *= 2;
	Triple *newTriplets = new Triple[this->capacity];
	int *newNext = new int[this->capacity];
	for (int i = 0; i < this->size; i++)
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

TElem Matrix::modify(int i, int j, TElem e)
{
	// std::cout << "Modify: " << i << " " << j << " " << e << " size " << this->size << " capacity " << this->capacity << std::endl;
	int oldValue = 0;
	try
	{
		oldValue = this->element(i, j);
	}
	catch (const std::exception &ex)
	{
		throw ex;
	}
	std::pair<int, int> p = {i, j};
	int current = this->first, previous = -1, indexOfLargestSmallest = -1;
	do
	{
		if (this->triplets[current].first == p)
		{
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
		if (this->triplets[current].first < p)
			indexOfLargestSmallest = current;
		previous = current;
		current = this->next[current];
	} while (current != -1);
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

void Matrix::downsize()
{
	this->capacity /= 2;
	Triple *newTriplets = new Triple[this->capacity];
	int *newNext = new int[this->capacity];
	for (int i = 0; i < this->size; i++)
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
