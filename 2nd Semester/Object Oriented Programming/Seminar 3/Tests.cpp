#include "Tests.h"
#include <cstring>
#include <cassert>
#include <iostream>
#include <cctype>
#include "DynamicVector.h"

void Tests::testDynamicVector()
{
	DynamicVector<int> v1{2};
	v1.add(10);
	v1.add(20);
	assert(v1.getSize() == 2);
	assert(v1[1] == 20);
	v1[1] = 25;
	assert(v1[1] == 25);
	v1.add(30);
	assert(v1.getSize() == 3);

	DynamicVector<int> v2{v1};
	assert(v2.getSize() == 3);

	DynamicVector<int> v3;
	v3 = v1;
	assert(v3[0] == 10);

	// test iterator
	DynamicVector<int>::iterator it = v1.begin();
	assert(*it == 10);
	assert(it != v1.end());
	it++;
	assert(*it == 25);
}