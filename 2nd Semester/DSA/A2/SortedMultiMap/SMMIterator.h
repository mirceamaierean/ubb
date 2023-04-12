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
	void first();
	void next();
	bool valid() const;
	TElem getCurrent() const;
};
