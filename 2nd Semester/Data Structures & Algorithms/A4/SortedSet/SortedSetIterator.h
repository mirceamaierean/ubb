#pragma once
#include "SortedSet.h"

// DO NOT CHANGE THIS PART
class SortedSetIterator
{
	friend class SortedSet;

private:
	void merge(int left, int middle, int right);
	void mergeSort(int left, int right);
	const SortedSet &multime;
	SortedSetIterator(const SortedSet &m);
	TElem *elementsSorted;
	int currentElement;

public:
	~SortedSetIterator();
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;
};
