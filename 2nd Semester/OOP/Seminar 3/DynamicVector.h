#pragma once
#include <iterator>

template <typename T>
class DynamicVector
{
private:
	T *elems;
	int size;
	int capacity;

public:
	DynamicVector(int capacity = 10);
	DynamicVector(const DynamicVector &v);
	~DynamicVector();
	DynamicVector &operator=(const DynamicVector &v);
	T &operator[](int pos);
	void add(const T &e);
	int getSize() const;

private:
	// Resizes the current DynamicVector, multiplying its capacity by a given factor (real number).
	void resize(double factor = 2);

public:
	class iterator
	{
	private:
		T *ptr;

	public:
		// constructor with parameter T*
		// operator++ - pre-incrementing
		// operator++ - post-incrementing
		// dereferencing operator
		// operator!=
		// Incrementare prefixat
		iterator(T *ptr = nullptr) : ptr{ptr} {}
		~iterator() = default;
		T &operator*() const { return *ptr; }
		T *operator->() const { return ptr; }
		iterator &operator++()
		{
			ptr++;
			return *this;
		}
		iterator operator++(int)
		{
			iterator it = *this;
			ptr++;
			return it;
		}
		bool operator!=(const iterator &it) const { return ptr != it.ptr; }
	};

	iterator begin()
	{
		return iterator{this->elems};
	}

	iterator end()
	{
		return iterator{this->elems + this->size};
	}
};

template <typename T>
DynamicVector<T>::DynamicVector(int capacity)
{
	this->size = 0;
	this->capacity = capacity;
	this->elems = new T[capacity];
}

template <typename T>
DynamicVector<T>::DynamicVector(const DynamicVector &v)
{
	this->size = v.size;
	this->capacity = v.capacity;
	this->elems = new T[this->capacity];
	for (int i = 0; i < this->size; i++)
		this->elems[i] = v.elems[i];
}

template <typename T>
DynamicVector<T>::~DynamicVector()
{
	delete[] this->elems;
}

template <typename T>
void DynamicVector<T>::add(const T &e)
{
	if (this->size == this->capacity)
		this->resize();
	this->elems[this->size] = e;
	this->size++;
}

template <typename T>
void DynamicVector<T>::resize(double factor)
{
	this->capacity *= static_cast<int>(factor);

	T *els = new T[this->capacity];
	for (int i = 0; i < this->size; i++)
		els[i] = this->elems[i];

	delete[] this->elems;
	this->elems = els;
}

template <typename T>
int DynamicVector<T>::getSize() const
{
	return this->size;
}

template <typename T>
T &DynamicVector<T>::operator[](int pos)
{
	if (pos < 0 || pos >= this->size)
		throw std::exception();
	return this->elems[pos];
}

template <typename T>
DynamicVector<T> &DynamicVector<T>::operator=(const DynamicVector<T> &v)
{
	if (this == &v)
		return *this;

	this->size = v.size;
	this->capacity = v.capacity;

	delete[] this->elems;
	this->elems = new T[this->capacity];
	for (int i = 0; i < this->size; i++)
		this->elems[i] = v.elems[i];

	return *this;
}