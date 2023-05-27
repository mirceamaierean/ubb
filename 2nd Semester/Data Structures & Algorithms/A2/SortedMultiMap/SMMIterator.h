#pragma once

#include "SortedMultiMap.h"

class SMMIterator
{
	friend class SortedMultiMap;

private:
	// DO NOT CHANGE THIS PART
	const SortedMultiMap &map;
	Node *current;
	SMMIterator(const SortedMultiMap &map);

public:
	// Add copy assignment operator and copy constructor
	SMMIterator &operator=(const SMMIterator &other);
	void first();
	void last();
	void next();
	void previous();
	bool valid() const;
	TElem getCurrent();
};
