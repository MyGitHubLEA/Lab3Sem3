#pragma once
#include <iostream>
#include <stdexcept>
#include <memory>
#include <cmath>
#include <string>
#include "..\..\..\Documents\Laba3Sem3\HashTable.h"
//#include "IDictionary.h"
#include <fstream>
#include <sstream>

template <typename TElement>
class SparseMatrix;

template<typename T>
struct IndexPair 
{
    int row;
    int column;
    IndexPair(int row, int column) : row(row), column(column) {};
    IndexPair() = default;
    template <class U>
    friend bool operator==(const IndexPair<U>& a, const IndexPair<U>& b);
};
/*
std::ostream& operator << (std::ostream& out, const IndexPair<int>& pair)
{
    out << "{" << pair.row << "   " << pair.column << "}" << std::endl;
    return out;
}
*/
template <typename T>
std::ostream& operator << (std::ostream& out, const std::pair<IndexPair<int>, T>& pair)
{
    out << "{"<<pair.first.row << "   " << pair.first.column << "}" << "   " << pair.second << std::endl;
    return out;
}

template <typename T>
bool operator==(const IndexPair<T>& a, const IndexPair<T>& b)
{
    return a.row == b.row && a.column == b.column;
}

template <typename TElement>
class SparseMatrix
{
private:
    int rows;
    int columns;
    IDictionary<IndexPair<int>, TElement>* elems; // 

public:
    SparseMatrix(const SparseMatrix& other);
    SparseMatrix(int rows, int columns);
    SparseMatrix(int rows, int columns, IDictionary<IndexPair<int>, TElement, std::hash<IndexPair<int>>>* dictionary);
    SparseMatrix(int rows, int columns, const TElement* array, int arrayRows, int arrayColumns);
    SparseMatrix(const std::string& filename);
    SparseMatrix& operator=(const SparseMatrix& other);
    SparseMatrix();
    ~SparseMatrix() = default;

    void Add(const IndexPair<int>& index, const TElement& value);
    void Remove(const IndexPair<int>& index);
    TElement Get(const IndexPair<int>& index) const;
    void Update(const IndexPair<int>& key, const TElement& value);


    SparseMatrix<TElement> operator+(const SparseMatrix<TElement>& other) const;
    SparseMatrix<TElement> operator*(double scalar) const;
    SparseMatrix<TElement> operator*(const SparseMatrix<TElement>& other) const;
    double norm() const;
    void normalize();
    ArraySequence<IndexPair<int>> Keys() const;
    ArraySequence<std::pair<IndexPair<int>, TElement>> GetItems() const;

    //std::unique_ptr<SparseMatrix<TElement>> Mult(const SparseMatrix<TElement>& other) const;
    SparseMatrix(SparseMatrix&& other) noexcept;

    SparseMatrix& operator=(SparseMatrix&& other) noexcept;
    template <typename TElement>
    friend std::ostream& operator<<(std::ostream& out, const SparseMatrix<TElement>& matrix);
   

};

template <typename TElement>
SparseMatrix<TElement>::SparseMatrix(int rows, int columns, const TElement* array, int arrayRows, int arrayColumns) : rows(rows), columns(columns)
{
    if (rows != arrayRows || columns != arrayColumns)
        throw std::invalid_argument("Incorrect array dimensions.");
    elems = new HashTable<IndexPair<int>, TElement, std::hash<IndexPair<int>>>();
    for (int i = 0; i < rows; ++i) 
    {
        for (int j = 0; j < columns; ++j) 
        {
            IndexPair<int> index(i, j);
            if (array[i * arrayColumns + j] != 0)
                elems->Add(index, array[i * arrayColumns + j]);
        }
    }
}
template <typename TElement>
SparseMatrix<TElement>& SparseMatrix<TElement>::operator=(const SparseMatrix<TElement>& other)
{
    std::cout << "Operator = of SparseMatrix was called" << std::endl;
    if (this == &other) 
    {
        return *this; 
    }

    delete elems;
    
    rows = other.rows;
    columns = other.columns;
    elems = new HashTable<IndexPair<int>, TElement>();
    for (auto iterator = other.elems->begin(); *iterator != *other.elems->end(); ++(*iterator)) 
    {
        const IndexPair<int>& index = (**iterator).key;
        const TElement& value = other.Get(index);
        elems->Add(index, value); 
    }

    return *this;
}

template <typename TElement>
SparseMatrix<TElement>::SparseMatrix(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file.");
    }

    std::string line;
    std::getline(file, line);
    std::stringstream ss(line);

    if (!(ss >> rows >> columns))
    {
        throw std::runtime_error("Incorrect dimensions format");
    }
    elems = new HashTable<IndexPair<int>, TElement>();

    for (int i = 0; i < rows; ++i)
    {
        if (!getline(file, line))
            throw std::runtime_error("Incorrect file format.");
        std::stringstream ssLine(line);

        for (int j = 0; j < columns; ++j)
        {
            TElement value;
            if (!(ssLine >> value))
                throw std::runtime_error("Incorrect file format.");
            IndexPair<int> index(i, j);
            if (value != static_cast<TElement>(0))
                elems->Add(index, value);

        }
    }
}

template <typename TElement>
SparseMatrix<TElement>::SparseMatrix(const SparseMatrix& other) : rows(other.rows), columns(other.columns)
{
    std::cout << "Copy constructor of SparseMatrix was called" << std::endl;
    elems = new HashTable<IndexPair<int>, TElement>();
    for (auto iterator = other.elems->begin(); *iterator != *other.elems->end(); ++(*iterator)) 
    {
        const IndexPair<int>& index = (**iterator).key;
        const TElement& value = other.Get(index);
        elems->Add(index, value); 
    }
}

template <typename TElement>
SparseMatrix<TElement>::SparseMatrix(int rows, int columns) : rows(rows), columns(columns)
{
    elems = new HashTable<IndexPair<int>, TElement, std::hash<IndexPair<int>>>();
}

template <typename TElement>
SparseMatrix<TElement>::SparseMatrix() : rows(0), columns(0)
{
    elems = new HashTable<IndexPair<int>, TElement, std::hash<IndexPair<int>>>();
}

template <typename TElement>
SparseMatrix<TElement>::SparseMatrix(int rows, int columns, IDictionary<IndexPair<int>, TElement, std::hash<IndexPair<int>>>* dictionary) : rows(rows), columns(columns),elems(std::move(dictionary)) {}


template <typename TElement>
void SparseMatrix<TElement>::Add(const IndexPair<int>& index, const TElement& value)
{
    if (index.row < 0 || index.row >= rows || index.column < 0 || index.column >= columns)
    {
        throw std::out_of_range("Index out of bounds.");
    }
    elems->Add(index, value);
}

template <typename TElement>
void SparseMatrix<TElement>::Remove(const IndexPair<int>& index)
{
    if (!elems->ContainsKey(index))
    {
        throw std::out_of_range("Index out of range");
    }
    elems->Delete(index);
}

template <typename TElement>
SparseMatrix<TElement>::SparseMatrix(SparseMatrix&& other) noexcept : rows(other.rows), columns(other.columns), elems(other.elems) 
{
    std::cout << "Move copy constructor of SparseMatrix was called" << std::endl;
    other.rows = 0;
    other.columns = 0;
    other.elems = nullptr;
}

template <typename TElement> 
SparseMatrix<TElement>& SparseMatrix<TElement>::operator=(SparseMatrix&& other) noexcept
{
    std::cout << "Move operator = of SparseMatrix was called" << std::endl;
    if (this != &other) 
    {
        delete elems;

        rows = other.rows;
        columns = other.columns;
        elems = other.elems;

        other.rows = 0;
        other.columns = 0;
        other.elems = nullptr;
    }
    return *this;
}


//ñ ìóâ ñåìàíòèêîé
//ñäåëàòü ðåïîçèòîðèé, ñ âåòêàìè, ñðàâíèòü âðåìÿ âûïîëíåíèÿ ñ ññûëêàìè è áåç. 
//
template <typename TElement>
SparseMatrix<TElement> SparseMatrix<TElement>::operator+(const SparseMatrix<TElement>& other) const
{
    if (rows != other.rows || columns != other.columns)
    {
        throw std::invalid_argument("Matrix dimensions must match for addition.");
    }

    SparseMatrix<TElement> result(*this);

    for (auto iterator = other.elems->begin(); *(iterator) != *(other.elems->end()); ++(*iterator))
    {
        const IndexPair<int>& currentKey = (**iterator).key;
        if (result.elems->ContainsKey(currentKey))
        {
            result.elems->Update(currentKey, result.elems->Get(currentKey) + (**iterator).value);
        }
        else
        {
            result.elems->Add(currentKey, (**iterator).value);
        }
    }
    return result;
}


template <typename TElement>
SparseMatrix<TElement> SparseMatrix<TElement>::operator*(double scalar) const
{
    SparseMatrix<TElement> result(*this);
    for (auto iterator = elems->begin(); *iterator != *(elems->end()); ++(*iterator))
    {
        IndexPair<int> currentKey = (**iterator).key;
        result.elems->Update(currentKey, (**iterator).value * scalar);
    }
    return result;
}


template <typename TElement>
SparseMatrix<TElement> SparseMatrix<TElement>::operator*(const SparseMatrix<TElement>& other) const 
{
    if (columns != other.rows)
    {
        throw std::invalid_argument("Incompatible dimensions for matrix multiplication.");
    }
    
    SparseMatrix<TElement> result(rows, other.columns); 
    for (auto iterator = elems->begin(); *iterator != *elems->end(); ++(*iterator))
    {
        const IndexPair<int>& index1 = (**iterator).key;
        for (auto iterator2 = other.elems->begin(); *iterator2 != *other.elems->end(); ++(*iterator2))
        {
            const IndexPair<int>& index2 = (**iterator2).key;
            if (index1.column == index2.row)
            {
                IndexPair<int> resultIndex(index1.row, index2.column);
                TElement newValue = Get(index1) * other.Get(index2);
                if (result.elems->ContainsKey(resultIndex))
                {
                    result.elems->Update(resultIndex, result.elems->Get(resultIndex) + newValue);
                }
                else
                {
                    result.elems->Add(resultIndex, newValue);
                }
            }
        }
    }
  
    return result;
}


template <typename TElement>
double SparseMatrix<TElement>::norm() const
{
    double sumOfSquares = 0.0;
    for (auto iterator = elems->begin(); *iterator != *elems->end(); ++(*iterator)) 
    {
        sumOfSquares += std::pow((**iterator).value, 2);
    }
    return std::sqrt(sumOfSquares);
}

template <typename TElement>
void SparseMatrix<TElement>::normalize()
{
    double currentNorm = norm();
    if (currentNorm == 0) return;
    for (auto iterator = elems->begin(); *iterator != *elems->end(); ++(*iterator))
    {
        Update((**iterator).key, (**iterator).value / currentNorm);
    }
}

template <typename TElement>
ArraySequence<IndexPair<int>> SparseMatrix<TElement>::Keys() const
{
    return elems->Keys();
}

template <typename TElement>
ArraySequence<std::pair<IndexPair<int>, TElement>> SparseMatrix<TElement>::GetItems() const
{
    return elems->GetAll();
}



template <typename TElement>
std::ostream& operator<<(std::ostream& out, const SparseMatrix<TElement>& matrix) 
{
    out << "SparseVector: " << std::endl << "Dimensions: " << matrix.rows << "x" << matrix.columns << std::endl;
    
    for (auto iterator = matrix.elems->begin(); *iterator != *matrix.elems->end(); ++(*iterator))
    {
        const std::pair<IndexPair<int>, TElement> pair ((**iterator).key, (**iterator).value);
        out << pair;
    }
    return out;
}

namespace std
{
    template <typename T>
    struct hash<IndexPair<T>> 
    {
        size_t operator()(const IndexPair<T>& index) const 
        {
            size_t h1 = std::hash<int>()(index.row);
            size_t h2 = std::hash<int>()(index.column);
            return h1 ^ (h2 << 1);
        }
    };
}


template <typename T>
SparseMatrix<T> createSparseMatrixFromArray(int rows, int columns, const T* array)
{
    return SparseMatrix<T>(rows, columns, array, rows, columns);
}

template <typename TElement>
TElement SparseMatrix<TElement>::Get(const IndexPair<int>& index) const
{
    if (!elems->ContainsKey(index))
    {
        throw std::out_of_range("Index out of range");
    }
    return elems->Get(index);
}

template <typename TElement>
void SparseMatrix<TElement>::Update(const IndexPair<int>& key, const TElement& value)
{
    elems->Update(key, value);
}
