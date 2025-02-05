#include <iostream>
#include <cassert>
#include <cmath>
#include <limits>
#include "SparseVector.h"
#include "..\Laba2\Sequence.h"


void testSparseVectorAddAndGet() 
{
    SparseVector<int> vector(5);
    vector.Add(1, 10);
    vector.Add(3, 20);

    assert(vector.Get(1) == 10);
    assert(vector.Get(3) == 20);

    try 
    {
        vector.Get(-1);
        assert(false);
    }
    catch (const std::out_of_range& e)
    {
    }
    try {
        vector.Get(5);
        assert(false);
    }
    catch (const std::out_of_range& e)
    {
    }
    std::cout << "testSparseVectorAddAndGet passed" << std::endl;
}

void testSparseVectorRemove() 
{
    SparseVector<int> vector(5);
    vector.Add(1, 10);
    vector.Add(3, 20);
    vector.Remove(1);
    try {
        vector.Get(1);
        assert(false);
    }
    catch (const std::out_of_range& e) {
    }
    assert(vector.Get(3) == 20);
    std::cout << "testSparseVectorRemove passed" << std::endl;
}

void testSparseVectorUpdate()
{
    SparseVector<int> vector(5);
    vector.Add(1, 10);
    vector.Add(3, 20);
    vector.Update(1, 15);
    assert(vector.Get(1) == 15);
    assert(vector.Get(3) == 20);
    std::cout << "testSparseVectorUpdate passed" << std::endl;
}

void testSparseVectorAddition() 
{
    int array1[] = { 1, 0, 2, 0, 3 };
    int array2[] = { 0, 2, 0, 1, 0 };

    SparseVector<int> vector1 = createSparseVectorFromArray(5, array1);
    SparseVector<int> vector2 = createSparseVectorFromArray(5, array2);

    SparseVector<int> result = vector1 + vector2;

    int expectedArray[] = { 1, 2, 2, 1, 3 };
    SparseVector<int> expected = createSparseVectorFromArray(5, expectedArray);
    ArraySequence<int> keys1 = result.Keys();
    ArraySequence<int> keys2 = expected.Keys();
    assert(keys1.GetLength() == keys2.GetLength());
    for (int i = 0; i < keys1.GetLength(); ++i) {
        assert(result.Get(keys1.Get(i)) == expected.Get(keys2.Get(i)));
    }
    try
    {
        SparseVector<int> vector3(3);
        vector1 + vector3;
        assert(false);
    }
    catch (const std::invalid_argument& e)
    {
    }

    std::cout << "testSparseVectorAddition passed" << std::endl;
}

void testSparseVectorScalarMultiplication() 
{
    int array[] = { 1, 0, 2, 0, 3 };
    SparseVector<int> vector = createSparseVectorFromArray(5, array);
    SparseVector<int> result = vector * 2.0;

    int expectedArray[] = { 2, 0, 4, 0, 6 };
    SparseVector<int> expected = createSparseVectorFromArray(5, expectedArray);
    ArraySequence<int> keys1 = result.Keys();
    ArraySequence<int> keys2 = expected.Keys();
    assert(keys1.GetLength() == keys2.GetLength());
    for (int i = 0; i < keys1.GetLength(); ++i) {
        assert(result.Get(keys1.Get(i)) == expected.Get(keys2.Get(i)));
    }
    std::cout << "testSparseVectorScalarMultiplication passed" << std::endl;
}


void testSparseVectorVectorMultiplication()
{
    int array1[] = { 1, 0, 2, 0, 3 };
    int array2[] = { 0, 2, 0, 1, 0 };

    SparseVector<int> vector1 = createSparseVectorFromArray(5, array1);
    SparseVector<int> vector2 = createSparseVectorFromArray(5, array2);
    int result = vector1 * vector2;
    assert(result == 0);
    int array3[] = { 1, 2, 3, 4, 5 };
    SparseVector<int> vector3 = createSparseVectorFromArray(5, array3);
    int result2 = vector1 * vector3;
    
    assert(result2 == 22);
    try
    {
        SparseVector<int> vector4(3);
        vector1* vector4;
        assert(false);

    }
    catch (const std::invalid_argument& e)
    {
    }

    std::cout << "testSparseVectorVectorMultiplication passed" << std::endl;
}

void testSparseVectorNorm() 
{
    int array[] = { 1, 0, 2, 0, 3 };
    SparseVector<int> vector = createSparseVectorFromArray(5, array);
    double norm = vector.norm();
    assert(abs(norm - sqrt(14.0)) < 0.001);

    int array2[] = { 0,0,0,0,0 };
    SparseVector<int> vector2 = createSparseVectorFromArray(5, array2);
    double norm2 = vector2.norm();
    assert(norm2 == 0);

    std::cout << "testSparseVectorNorm passed" << std::endl;
}


void testSparseVectorNormalize() {
    int array[] = { 1, 0, 2, 0, 3 };
    SparseVector<double> vector = createSparseVectorFromArray(5, reinterpret_cast<double*>(array));

    vector.normalize();
    double norm = vector.norm();
    assert(abs(norm - 1.0) < 0.001);
    std::cout << "testSparseVectorNormalize passed" << std::endl;
}

void testSparseVectorKeys()
{
    int array[] = { 1, 0, 2, 0, 3 };
    SparseVector<int> vector = createSparseVectorFromArray(5, array);
    ArraySequence<int> keys = vector.Keys();
    assert(keys.GetLength() == 3);
    bool first_found = false;
    bool second_found = false;
    bool third_found = false;
    for (int i = 0; i < keys.GetLength(); ++i)
    {
        if (keys.Get(i) == 0)
            first_found = true;
        if (keys.Get(i) == 2)
            second_found = true;
        if (keys.Get(i) == 4)
            third_found = true;
    }
    assert(first_found && second_found && third_found);
    std::cout << "testSparseVectorKeys passed" << std::endl;

}

void testSparseVectorGetItems()
{
    int array[] = { 1, 0, 2, 0, 3 };
    SparseVector<int> vector = createSparseVectorFromArray(5, array);
    ArraySequence<std::pair<int, int>> items = vector.GetItems();
    assert(items.GetLength() == 3);
    bool first_found = false;
    bool second_found = false;
    bool third_found = false;
    for (int i = 0; i < items.GetLength(); ++i)
    {
        if (items.Get(i).first == 0 && items.Get(i).second == 1)
            first_found = true;
        if (items.Get(i).first == 2 && items.Get(i).second == 2)
            second_found = true;
        if (items.Get(i).first == 4 && items.Get(i).second == 3)
            third_found = true;
    }
    assert(first_found && second_found && third_found);
    std::cout << "testSparseVectorGetItems passed" << std::endl;
}