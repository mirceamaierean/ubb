#pragma once

#include "SortedMultiMap.h"

class SMMIterator
{
	friend class SortedMultiMap;

private:
	const SortedMultiMap &map;
	SMMIterator(const SortedMultiMap &map);
	TElem *elements;
	int currentElement, numberOfElements, capacity;

public:
	// Destructor
	void DFS(Node *node);
	void first();
	void next();
	bool valid() const;
	TElem getCurrent() const;
	~SMMIterator();
};
