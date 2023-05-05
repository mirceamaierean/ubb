// ADT Matrix–represented as a sparse matrix, using a SLLAwith <line, column, value> triples (value ≠0), ordered lexicographically considering the line and column of every element.
#pragma once
#include <compare>
#include <iostream>
// DO NOT CHANGE THIS PART
typedef int TElem;
typedef std::pair<std::pair<int, int>, TElem> Triple;
#define NULL_TELEM 0
#define NULL_TRIPLE      \
	{                      \
		{-1, -1}, NULL_TELEM \
	}
class Matrix
{
private:
	// representation of the Matrix
	int nrL, nrC;
	Triple *triplets;
	int *next;
	int capacity, size, first, firstFree;
	void resize();
	void downsize();

public:
	// constructor
	Matrix(int nrLines, int nrCols);

	// returns the number of lines
	int nrLines() const;

	// returns the number of columns
	int nrColumns() const;

	// returns the element from line i and column j (indexing starts from 0)
	// throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	// modifies the value from line i and column j
	// returns the previous value from the position
	// throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

	void resizeToNewDimensions(int newNrL, int newNrC);
};
