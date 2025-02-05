#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>
#include <stdexcept>
//#include "IDictionary.h"
#include "..\..\..\Documents\Laba3Sem3\HashTable.h"
#include "..\Laba2\Sequence.h"
#include <functional>


template <typename TElement>
class SparseVector
{
private:
    int size;
    IDictionary<int, TElement, std::hash<int>>* elems; // 
public:
    SparseVector(int size);
    SparseVector(int size, const TElement* array);
    SparseVector(const std::string& filename);
    SparseVector(int size, IDictionary<int, TElement, std::hash<int>>* dictionary);
    SparseVector(const SparseVector& other);

    SparseVector();
    ~SparseVector() = default;

    void Add(int index, const TElement& value);
    void Remove(int index);
    TElement Get(int index) const;
    void Update(int key, const TElement& value);

    SparseVector<TElement>& operator=(const SparseVector<TElement>& other);


    SparseVector<TElement> operator+(const SparseVector<TElement>& other) const;
    SparseVector<TElement> operator*(double scalar) const;
    TElement operator*(const SparseVector<TElement>& other) const;
    double norm() const;
    void normalize();
    ArraySequence<int> Keys() const;
    ArraySequence<std::pair<int, TElement>> GetItems() const;
   
    template <typename TElement>
    friend std::ostream& operator<<(std::ostream& out, const SparseVector<TElement>& vector);

    SparseVector& operator=(SparseVector&& other) noexcept;
    SparseVector(SparseVector&& other) noexcept;

};
template <typename TElement>
SparseVector<TElement>::SparseVector(SparseVector&& other) noexcept : size(other.size)
{
    std::cout << "Move copy constructor of SparseVector was called" << std::endl;
    other.size = 0;
    other.elems = nullptr;
}


template <typename TElement>
SparseVector<TElement>& SparseVector<TElement>::operator=(SparseVector&& other) noexcept
{
    std::cout << "Move operator = of SparseVector was called" << std::endl;
    if (this != &other)
    {
        delete elems;

        size = other.size;
        
        elems = other.elems;

        other.size = 0;
        other.elems = nullptr;
    }
    return *this;
}

template <typename TElement>
SparseVector<TElement>::SparseVector(const SparseVector& other) : size(other.size)
{
    std::cout << "Copy constructor of SparseVector was called" << std::endl;
    elems = new HashTable<int, TElement>();
    for (auto iterator = other.elems->begin(); *iterator != *other.elems->end(); ++(*iterator))
    {
        const int& index = (**iterator).key;
        const TElement& value = other.Get(index);
        elems->Add(index, value);
    }
}


template <typename TElement>
SparseVector<TElement>& SparseVector<TElement>::operator=(const SparseVector<TElement>& other)
{
    std::cout << "Operator = of SparseVector was called" << std::endl;
    if (this == &other)
    {
        return *this;
    }

    delete elems;
    size = other.size;
    elems = new HashTable<int, TElement>();
    for (auto iterator = other.elems->begin(); *iterator != *other.elems->end(); ++(*iterator))
    {
        const int& index = (**iterator).key;
        const TElement& value = other.Get(index);
        elems->Add(index, value);
    }

    return *this;
}


template <typename TElement>
SparseVector<TElement>::SparseVector(int size) : size(size)
{
    elems = new HashTable<int, TElement, std::hash<int>>();
}

template <typename TElement>
SparseVector<TElement>::SparseVector() : size(0)
{
    elems = new HashTable<int, TElement, std::hash<int>>();
}

template <typename TElement>
SparseVector<TElement>::SparseVector(int size, IDictionary<int, TElement, std::hash<int>>* dictionary) : size(size), elems(std::move(dictionary)) {}

template <typename TElement>
SparseVector<TElement>::SparseVector(int size, const TElement* array) : size(size)
{
    elems = new HashTable<int, TElement, std::hash<int>>();
    for (int i = 0; i < size; ++i) 
    {
        if (array[i] != 0)
            elems->Add(i, array[i]);
    }
}

template <typename TElement>
SparseVector<TElement>::SparseVector(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) 
    {
        throw std::runtime_error("Could not open file.");
    }

    std::string line;
    std::getline(file, line);
    std::stringstream ss(line);

    if (!(ss >> size))
    {
        throw std::runtime_error("Incorrect dimensions format");
    }
    elems = new HashTable<int, TElement, std::hash<int>>();

    if (!getline(file, line))
        throw std::runtime_error("Incorrect file format.");

    std::stringstream ssLine(line);
    for (int i = 0; i < size; ++i)
    {
        TElement value;
        if (!(ssLine >> value))
            throw std::runtime_error("Incorrect file format.");
        if (value != static_cast<TElement>(0))
            elems->Add(i, value);
    }

}

template <typename TElement>
void SparseVector<TElement>::Add(int index, const TElement& value)
{
    if (index < 0 || index >= size)
    {
        throw std::out_of_range("Index out of bounds.");
    }
    elems->Add(index, value);
}

template <typename TElement>
void SparseVector<TElement>::Remove(int index)
{
    if (!elems->ContainsKey(index))
    {
        throw std::out_of_range("Index out of range");
    }
    elems->Delete(index);
}

template <typename TElement>
SparseVector<TElement> SparseVector<TElement>::operator+(const SparseVector<TElement>& other) const
{
    if (size != other.size)
    {
        throw std::invalid_argument("Vector dimensions must match for addition.");
    }
    SparseVector<TElement> result(size);
    for (auto iterator = elems->begin(); *iterator != *elems->end(); ++(*iterator))
    {
        result.elems->Add((**iterator).key, (**iterator).value);
    }

    for (auto iterator = other.elems->begin(); *iterator != *other.elems->end(); ++(*iterator))
    {
        if (result.elems->ContainsKey((**iterator).key))
        {
            result.elems->Update((**iterator).key, result.elems->Get((**iterator).key) + (**iterator).value);
        }
        else
        {
            result.elems->Add((**iterator).key, (**iterator).value);
        }
    }
    return result;
}

template <typename TElement>
SparseVector<TElement> SparseVector<TElement>::operator*(double scalar) const
{
    SparseVector<TElement> result(size);
    for (auto iterator = elems->begin(); *iterator != *elems->end(); ++(*iterator))
    {
        result.elems->Add((**iterator).key, (**iterator).value * scalar);
    }
    return result;
}

template <typename TElement>
TElement SparseVector<TElement>::operator*(const SparseVector<TElement>& other) const
{
    if (size != other.size)
    {
        throw std::invalid_argument("Incompatible dimensions for vector multiplication.");
    }
    TElement result = 0;
    for (auto iterator = elems->begin(); *iterator != *elems->end(); ++(*iterator))
    {
        if (other.elems->ContainsKey((**iterator).key))
            result += (**iterator).value * other.Get((**iterator).key);

    }
    return result;
}


template <typename TElement>
double SparseVector<TElement>::norm() const
{
    double sumOfSquares = 0.0;
    for (auto iterator = elems->begin(); *iterator != *elems->end(); ++(*iterator))
    {
        sumOfSquares += std::pow((**iterator).value, 2);
    }
    return std::sqrt(sumOfSquares);
}

template <typename TElement>
void SparseVector<TElement>::normalize()
{
    double currentNorm = norm();
    if (currentNorm == 0) return;
    for (auto iterator = elems->begin(); *iterator != *elems->end(); ++(*iterator))
    {
        Update((**iterator).key, (**iterator).value / currentNorm);
    }
}

template <typename TElement>
ArraySequence<int> SparseVector<TElement>::Keys() const
{
    ArraySequence<int> keys;
    for (auto iterator = elems->begin(); *iterator != *elems->end(); ++(*iterator))
    {
        keys.Append((**iterator).key);
    }
    return keys;
}

template <typename TElement>
ArraySequence<std::pair<int, TElement>> SparseVector<TElement>::GetItems() const
{
    ArraySequence<std::pair<int, TElement>> items;
    for (auto iterator = elems->begin(); *iterator != *elems->end(); ++(*iterator))
    {
        items.Append({ (**iterator).key, (**iterator).value });
    }
    return items;
}


template <typename TElement>
std::ostream& operator<<(std::ostream& out, const SparseVector<TElement>& vector)
{
    for (auto iterator = vector.elems->begin(); *iterator != *vector.elems->end(); ++(*iterator))
    {
        out << (**iterator).key << " " << (**iterator).value <<std::endl;
    }
    return out;
}

template <typename T>
SparseVector<T> createSparseVectorFromArray(int size, const T* array)
{
    return SparseVector<T>(size, array);
}

template <typename TElement>
TElement SparseVector<TElement>::Get(int index) const
{
    if (!elems->ContainsKey(index))
    {
        throw std::out_of_range("Index out of range");
    }
    return elems->Get(index);
}


template <typename TElement>
void SparseVector<TElement>::Update(int key, const TElement& value)
{
    elems->Update(key, value);
}