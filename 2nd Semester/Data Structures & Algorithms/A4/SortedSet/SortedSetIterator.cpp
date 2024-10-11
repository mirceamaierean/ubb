#include "SortedSetIterator.h"
#include <exception>

using namespace std;

void SortedSetIterator::merge(int left, int middle, int right)
{
	int subArray1 = middle - left + 1;
	int subArray2 = right - middle;

	TElem *leftArray = new TElem[subArray1],
				*rightArray = new TElem[subArray2];

	for (int i = 0; i < subArray1; ++i)
		leftArray[i] = elementsSorted[left + i];

	for (int i = 0; i < subArray2; ++i)
		rightArray[i] = elementsSorted[middle + 1 + i];

	int indexLeft = 0, indexRight = 0, indexMerged = left;

	while (indexLeft < subArray1 && indexRight < subArray2)
	{
		if (multime.relation()(leftArray[indexLeft], rightArray[indexRight]))
			elementsSorted[indexMerged++] = leftArray[indexLeft++];
		else
			elementsSorted[indexMerged++] = rightArray[indexRight++];
	}

	while (indexLeft < subArray1)
		elementsSorted[indexMerged++] = leftArray[indexLeft++];
	while (indexRight < subArray2)
		elementsSorted[indexMerged++] = rightArray[indexRight++];

	delete[] leftArray;
	delete[] rightArray;
}

void SortedSetIterator::mergeSort(int left, int right)
{
	if (left >= right)
		return;

	int middle = (left + right) / 2;
	mergeSort(left, middle);
	mergeSort(middle + 1, right);
	merge(left, middle, right);
}

SortedSetIterator::SortedSetIterator(const SortedSet &m) : multime(m)
{
	this->currentElement = 0;
	elementsSorted = new TElem[multime.size()];
	int index = 0;
	for (int i = 0; i < this->multime.getCapacity(); ++i)
	{
		if (multime.elements[i] != NULL_TELEM)
			elementsSorted[index++] = multime.elements[i];
	}

	mergeSort(0, index - 1);
}

SortedSetIterator::~SortedSetIterator()
{
	delete[] elementsSorted;
}

void SortedSetIterator::first()
{
	this->currentElement = 0;
}

void SortedSetIterator::next()
{
	if (this->valid())
		this->currentElement++;
	else
		throw exception();
}

TElem SortedSetIterator::getCurrent()
{
	if (this->valid())
		return this->elementsSorted[this->currentElement];
	else
		throw exception();
	return NULL_TELEM;
}

bool SortedSetIterator::valid() const
{
	return this->currentElement < this->multime.size();
}
