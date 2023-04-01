#include "Set.h"
#include <assert.h>
#include "ExtendedTest.h"
#include "SetIterator.h"
#include <iostream>
#include <fstream>

using namespace std;

bool isEven(TElem elem)
{
	return elem % 2 == 0;
}

bool isOdd(TElem elem)
{
	return elem % 2 != 0;
}

void printM(Set &s)
{
	SetIterator it = s.iterator();
	while (it.valid())
	{
		std::cout << it.getCurrent() << " ";
		it.next();
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

void testIteratorSteps(Set &s)
{
	int count = 0;
	SetIterator si = s.iterator();
	while (si.valid())
	{
		count++;
		si.next();
	}
	assert(count == s.size());
}

void testCreate()
{
	cout << "Test create" << endl;
	Set s;
	assert(s.size() == 0);
	assert(s.isEmpty() == true);

	for (int i = -10; i < 10; i++)
	{ // search in an empty set
		assert(s.search(i) == false);
	}
	for (int i = -10; i < 10; i++)
	{ // delete from an empty set
		assert(s.remove(i) == false);
	}

	SetIterator it = s.iterator(); // iterator on the empty set should be invalid from the start
	assert(it.valid() == false);
}

void testAdd()
{
	cout << "Test add" << endl;
	Set s; // adaugam elemente [0, 10)
	for (int i = 0; i < 10; i++)
	{
		s.add(i);
	}
	// printM(m);
	assert(s.isEmpty() == false);
	assert(s.size() == 10);
	for (int i = -10; i < 20; i++)
	{ // add more elements [-10, 20)
		s.add(i);
	}
	// printM(m);
	assert(s.isEmpty() == false);
	assert(s.size() == 30);
	for (int i = -100; i < 100; i++)
	{ // add more elements [-100, 100)
		s.add(i);
	}
	// printM(m);
	assert(s.isEmpty() == false);
	assert(s.size() == 200);
	for (int i = -200; i < 200; i++)
	{
		if (i < -100)
			assert(s.search(i) == false);

		else if (i < 0)
			assert(s.search(i) == true);

		else if (i < 100)
			assert(s.search(i) == true);

		else
			assert(s.search(i) == false);
	}
	testIteratorSteps(s);
	for (int i = 10000; i > -10000; i--)
	// add larger values first
	{
		s.add(i);
	}
	// testIteratorSteps(s);

	assert(s.size() == 20000);
}

void testRemove()
{
	cout << "Test remove" << endl;
	Set m;
	for (int i = -100; i < 100; i++)
	{ // delete from the emtpy set
		assert(m.remove(i) == false);
	}
	assert(m.size() == 0);
	// printM(m);
	for (int i = -100; i < 100; i = i + 2)
	{
		m.add(i);
	}
	for (int i = -100; i < 100; i++)
	{ // delete everything (including inexistent elements)
		if (i % 2 == 0)
		{
			assert(m.remove(i) == true);
		}
		else
		{
			assert(m.remove(i) == false);
		}
	}
	assert(m.size() == 0);
	// printM(m);

	for (int i = -100; i <= 100; i = i + 2)
	{
		m.add(i);
	}
	// printM(m);
	for (int i = 100; i > -100; i--)
	{ // delete in descending order (reverse order compared to the adding)
		if (i % 2 == 0)
		{
			assert(m.remove(i) == true);
		}
		else
		{
			assert(m.remove(i) == false);
		}
	}

	assert(m.size() == 1);
	// printM(m);

	m.remove(-100);
	assert(m.size() == 0);

	for (int i = -100; i < 100; i++)
	{ // add each element five times
		m.add(i);
		m.add(i);
		m.add(i);
		m.add(i);
		m.add(i);
	}
	// printM(m);
	assert(m.size() == 200);
	for (int i = -200; i < 200; i++)
	{ // delete existing and inexistent elements
		if (i < -100 || i >= 100)
		{
			assert(m.remove(i) == false);
		}
		else
		{
			assert(m.remove(i) == true);
			assert(m.remove(i) == false);
		}
		testIteratorSteps(m);
	}
	assert(m.size() == 0);
}

void testIterator()
{
	cout << "Test iterator" << endl;
	Set s;
	SetIterator it = s.iterator(); // iterator on an empty set
	assert(it.valid() == false);
	try
	{
		it.next();
		assert(false);
	}
	catch (exception &e)
	{
		assert(true);
	}
	try
	{
		it.getCurrent();
		assert(false);
	}
	catch (exception &ex)
	{
		assert(true);
	}
	for (int i = 0; i < 100; i++)
	{
		s.add(33);
	}
	// printM(m);
	SetIterator it2 = s.iterator();
	assert(it2.valid() == true);
	TElem elem = it2.getCurrent();
	assert(elem == 33);
	it2.next();
	assert(it2.valid() == false);

	it2.first();
	assert(it2.valid() == true);

	Set s2;
	for (int i = -100; i < 100; i++)
	{
		s2.add(i);
		s2.add(i);
		s2.add(i);
	}
	// printM(m2);
	SetIterator it3 = s2.iterator();
	assert(it3.valid() == true);
	for (int i = 0; i < 200; i++)
	{
		// TElem e1 = im3.element();
		it3.next();
	}
	assert(it3.valid() == false);
	it3.first();
	assert(it3.valid() == true);

	Set s3;
	for (int i = 0; i < 200; i = i + 4)
	{
		s3.add(i);
	}
	// printM(m3);

	SetIterator it4 = s3.iterator();
	assert(it4.valid() == true);
	int count = 0;
	while (it4.valid())
	{
		TElem e = it4.getCurrent();
		assert(e % 4 == 0);
		it4.next();
		count++;
	}
	try
	{
		it4.getCurrent();
		assert(false);
	}
	catch (exception &ex)
	{
		assert(true);
	}
	try
	{
		it4.next();
		assert(false);
	}
	catch (exception &ex)
	{
		assert(true);
	}
	assert(count == 50);
}

void testMix()
{
	cout << "Test mix" << endl;
	Set s;
	int first = 11;
	int last = 11;
	int count = 3;
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < count; j++)
		{
			s.add(last);
			last = (last + 7) % 11111;
		}
		assert(s.search(first) == true);
		assert(s.remove(first) == true);
		first = (first + 7) % 11111;
		if (i % 10 == 0)
		{
			count++;
		}
	}
	while (s.isEmpty() == false)
	{
		assert(s.search(first) == true);
		assert(s.remove(first) == true);
		first = (first + 7) % 11111;
	}
}

void testQuantity()
{ // add lots of elements
	cout << "Test quantity" << endl;
	Set s;
	for (int i = 10; i >= 1; i--)
	{
		for (int j = -30000; j < 30000; j = j + i)
		{
			s.add(j);
		}
	}
	assert(s.size() == 60000);
	SetIterator it = s.iterator();
	assert(it.valid() == true);
	for (int i = 0; i < s.size(); i++)
	{
		it.next();
	}
	it.first();
	while (it.valid())
	{
		TElem e = it.getCurrent();
		assert(s.search(e) == true);
		it.next();
	}
	assert(it.valid() == false);
	for (int i = 0; i < 10; i++)
	{ // delete existing and inexistent elements
		for (int j = 40000; j >= -40000; j--)
		{
			s.remove(j);
		}
	}
	assert(s.size() == 0);
}

void testFilter()
{
	cout << "Test filter" << endl;
	Set s;
	// Can't filter an empty set
	try
	{
		s.filter(isEven);
		assert(false);
	}
	catch (exception &ex)
	{
		assert(true);
	}

	for (int i = 0; i < 100; i++)
		s.add(i);

	assert(s.size() == 100);

	s.filter(isEven);

	assert(s.size() == 50);

	s.filter(isEven);
	assert(s.size() == 50);

	for (int i = 0; i < 100; i++)
		s.add(i);

	assert(s.size() == 100);

	s.filter(isOdd);

	assert(s.size() == 50);

	s.filter(isEven);
	assert(s.size() == 0);
}
// we don't know how the set is represented and in which order the elements are stored or printed, we can only test general thing
void testAllExtended()
{
	testFilter();
	testCreate();
	testAdd();
	testRemove();
	testIterator();
	testMix();
	testQuantity();
}
