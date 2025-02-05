#pragma once
#include <stdexcept>
#include <iostream>
template <typename T> 
class DynamicArray 
{
private:
	T* data = nullptr; 
	int size = 0;
public:
	DynamicArray(int);

	DynamicArray(T*, int );

	DynamicArray(const DynamicArray<T>& );

	const T& GetTest(int) const;


	~DynamicArray();

	T& Get(int) const;

	int GetLength() const;

	void Set(const T&, int );

	void Resize(int);

	void Delete(int);
};

template <typename T>
DynamicArray<T>::DynamicArray(int size)
{
	this->data = new T[size];
	this->size = size;
}

template <typename T>
DynamicArray<T>::DynamicArray(T* data, int size) : DynamicArray(size) 
{
	for (int i = 0; i < size; i++)
		this->data[i] = data[i];
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& array) : DynamicArray(array.size)
{
//	std::cout << "Copy Constuctor of DynamicArray was called. New[] was called" << std::endl;
	for (int i = 0; i < size; i++)
		this->data[i] = array.data[i];
}

template <typename T>
T& DynamicArray<T>::Get(int index) const
{
	if (index < 0 || index >= this->GetLength()) throw std::out_of_range("IndexOutOfRange");
	return this->data[index];
}


template <typename T>
const T& DynamicArray<T>::GetTest(int index) const
{
	if (index < 0 || index >= this->GetLength()) throw std::out_of_range("IndexOutOfRange");
	return this->data[index];
}

template <typename T>
int DynamicArray<T>::GetLength() const
{
	return this->size;
}

template <typename T>
void DynamicArray<T>::Set(const T& value, int index)
{
	if (index < 0 || index >= this->GetLength()) throw std::out_of_range("IndexOutOfRange");
	this->data[index] = value;
}

template <typename T>
void DynamicArray<T>::Resize(int size)
{
	//std::cout << "Delete[] of DynamicArray was called" << std::endl;

	T* newData = new T[size];
	int Count = (this->size > size ? size : this->size);
	for (int i = 0; i < Count; i++)
		newData[i] = data[i];
	delete[] data;
	this->data = newData;
	this->size = size;
}

template <typename T>
void DynamicArray<T>::Delete(int index)
{
	T* newData = new T[size - 1];
	//int Count = (this->size > size ? size : this->size);
	int j = 0;
	for (int i = 0; i < size; ++i)
	{
		if (i != index)
		{
			newData[j] = data[i];
			++j;
		}
	}
	//std::cout << "Delete[] of DynamicArray was called" << std::endl;

	delete[] data;
	this->data = newData;
	this->size = size - 1;
}


template <typename T>
DynamicArray<T>::~DynamicArray<T>() 
{
	//std::cout << "Delete[] of DynamicArray was called" << std::endl;
	delete[] data;
}