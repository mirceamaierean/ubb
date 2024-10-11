// using a hashtable with coalesced chaining
#pragma once
typedef int TElem;
typedef TElem TComp;
typedef bool (*Relation)(TComp, TComp);
#define NULL_TELEM -111111
#define INITIAL_CAPACITY 17
class SortedSetIterator;

class SortedSet
{
	friend class SortedSetIterator;

private:
	// TODO - Representation
	Relation rel;
	int capacity;
	int nrElements;
	int *next;
	int firstEmpty;
	TElem *elements;

	void resize(int newCapacity);

	inline int hashFunction(TComp elem) const
	{
		while (elem < 0)
			elem += this->capacity;
		return elem % this->capacity;
	}

	inline bool requiresResize() const
	{
		return this->nrElements == this->capacity;
	}

	inline bool requireDownsize() const
	{
		return this->nrElements < this->capacity / 4;
	}

public:
	// constructor
	SortedSet(Relation r);

	// adds an element to the sorted set
	// if the element was added, the operation returns true, otherwise (if the element was already in the set)
	// it returns false
	bool add(TComp e);

	// removes an element from the sorted set
	// if the element was removed, it returns true, otherwise false
	bool remove(TComp e);

	// checks if an element is in the sorted set
	bool search(TElem elem) const;

	// returns the number of elements from the sorted set
	int size() const;

	int getCapacity() const { return this->capacity; };

	Relation relation() const { return this->rel; };

	bool isSubset(const SortedSet &s) const;

	// checks if the sorted set is empty
	bool isEmpty() const;

	// returns an iterator for the sorted set
	SortedSetIterator iterator() const;

	// destructor
	~SortedSet();
};
