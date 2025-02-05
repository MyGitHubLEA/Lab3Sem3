#pragma once
#include <cassert>
#include "SparseMatrix.h"

void testAddAndGet()
{
    SparseMatrix<int> matrix(3, 3);
    IndexPair<int> index1(0, 1);
    IndexPair<int> index2(2, 2);

    matrix.Add(index1, 10);
    matrix.Add(index2, 20);

    assert(matrix.Get(index1) == 10);
    assert(matrix.Get(index2) == 20);

   
    std::cout << "testAddAndGet passed" << std::endl;
}

void testRemove() {
    SparseMatrix<int> matrix(3, 3);
    IndexPair<int> index1(0, 1);
    IndexPair<int> index2(2, 2);

    matrix.Add(index1, 10);
    matrix.Add(index2, 20);
    matrix.Remove(index1);
    try 
    {
        matrix.Get(index1);
        assert(false);
    }
    catch (const std::out_of_range& e)
    {

    }
    assert(matrix.Get(index2) == 20);
    std::cout << "testRemove passed" << std::endl;
}

void testUpdate()
{
    SparseMatrix<int> matrix(3, 3);
    IndexPair<int> index1(0, 1);
    IndexPair<int> index2(2, 2);
    matrix.Add(index1, 10);
    matrix.Add(index2, 20);
    matrix.Update(index1, 15);
    assert(matrix.Get(index1) == 15);
    assert(matrix.Get(index2) == 20);
    std::cout << "testUpdate passed" << std::endl;

}

void testAddition() {
    int array1[2][3] = { {1, 0, 2}, {0, 3, 0} };
    int array2[2][3] = { {0, 2, 0}, {1, 0, 1} };

    SparseMatrix<int> matrix1 = createSparseMatrixFromArray(2, 3, reinterpret_cast<int*>(array1));
    SparseMatrix<int> matrix2 = createSparseMatrixFromArray(2, 3, reinterpret_cast<int*>(array2));

    SparseMatrix<int> result = matrix1 + matrix2;

    int expectedArray[2][3] = { {1, 2, 2}, {1, 3, 1} };
    SparseMatrix<int> expected = createSparseMatrixFromArray(2, 3, reinterpret_cast<int*>(expectedArray));

    ArraySequence<IndexPair<int>> keys1 = result.Keys();
    ArraySequence<IndexPair<int>> keys2 = expected.Keys();
    assert(keys1.GetLength() == keys2.GetLength());
    for (int i = 0; i < keys1.GetLength(); ++i) {
        assert(result.Get(keys1.Get(i)) == expected.Get(keys2.Get(i)));
    }
    try {
        int array3[3][3] = { {0, 2, 0}, {1, 0, 1}, {1, 1, 1} };
        SparseMatrix<int> matrix3 = createSparseMatrixFromArray(3, 3, reinterpret_cast<int*>(array3));
        matrix1 + matrix3;
        assert(false);
    }
    catch (const std::invalid_argument& e)
    {
    }
    std::cout << "testAddition passed" << std::endl;
}

void testScalarMultiplication() {
    int array[2][3] = { {1, 0, 2}, {0, 3, 0} };
    SparseMatrix<int> matrix = createSparseMatrixFromArray(2, 3, reinterpret_cast<int*>(array));

    SparseMatrix<int> result = matrix * 2.0;
    int expectedArray[2][3] = { {2, 0, 4}, {0, 6, 0} };
    SparseMatrix<int> expected = createSparseMatrixFromArray(2, 3, reinterpret_cast<int*>(expectedArray));
    ArraySequence<IndexPair<int>> keys1 = result.Keys();
    ArraySequence<IndexPair<int>> keys2 = expected.Keys();
    assert(keys1.GetLength() == keys2.GetLength());
    for (int i = 0; i < keys1.GetLength(); ++i) {
        assert(result.Get(keys1.Get(i)) == expected.Get(keys2.Get(i)));
    }

    std::cout << "testScalarMultiplication passed" << std::endl;
}

void testMatrixMultiplication()
{
    int array1[2][3] = { {1, 0, 2}, {0, 3, 0} }; //3 0, 0 6
    int array2[3][2] = { {1, 0}, {0, 2}, {1, 0} };
    SparseMatrix<int> matrix1 = createSparseMatrixFromArray(2, 3, reinterpret_cast<int*>(array1));
    SparseMatrix<int> matrix2 = createSparseMatrixFromArray(3, 2, reinterpret_cast<int*>(array2));

    SparseMatrix<int> result = matrix1 * matrix2;

    int expectedArray[2][2] = { {3, 0}, {0, 6} };
    SparseMatrix<int> expected = createSparseMatrixFromArray(2, 2, reinterpret_cast<int*>(expectedArray));

    ArraySequence<IndexPair<int>> keys1 = result.Keys();
    ArraySequence<IndexPair<int>> keys2 = expected.Keys();
    assert(keys1.GetLength() == keys2.GetLength());
    for (int i = 0; i < keys1.GetLength(); ++i) {
        assert(result.Get(keys1.Get(i)) == expected.Get(keys2.Get(i)));
    }
    try {
        int array3[2][2] = { {1, 0}, {0, 2} };
        SparseMatrix<int> matrix3 = createSparseMatrixFromArray(2, 2, reinterpret_cast<int*>(array3));
        matrix1* matrix3;
        assert(false);
    }
    catch (const std::invalid_argument& e)
    {
    }
    std::cout << "testMatrixMultiplication passed" << std::endl;
}


void testNorm()
{
    int array[2][3] = { {1, 0, 2}, {0, 3, 0} };
    SparseMatrix<int> matrix = createSparseMatrixFromArray(2, 3, reinterpret_cast<int*>(array));

    double norm = matrix.norm();
    assert(abs(norm - sqrt(14.0)) < 0.001);
    int array2[2][3] = { {0, 0, 0}, {0, 0, 0} };
    SparseMatrix<int> matrix2 = createSparseMatrixFromArray(2, 3, reinterpret_cast<int*>(array2));
    double norm2 = matrix2.norm();
    assert(norm2 == 0);
    std::cout << "testNorm passed" << std::endl;
}

void testNormalize()
{
    double array[2][3] = { {1, 0, 2}, {0, 3, 0} };
    SparseMatrix<double> matrix = createSparseMatrixFromArray(2, 3, reinterpret_cast<double*>(array));

    matrix.normalize();
    double norm = matrix.norm();
    assert(abs(norm - 1.0) < 0.001);
    std::cout << "testNormalize passed" << std::endl;

}
void testKeys()
{
    int array[2][3] = { {1, 0, 2}, {0, 3, 0} };
    SparseMatrix<int> matrix = createSparseMatrixFromArray(2, 3, reinterpret_cast<int*>(array));
    ArraySequence<IndexPair<int>> keys = matrix.Keys();
    assert(keys.GetLength() == 3);
    bool first_found = false;
    bool second_found = false;
    bool third_found = false;
    for (int i = 0; i < keys.GetLength(); ++i)
    {
        if (keys.Get(i) == IndexPair<int>(0, 0))
            first_found = true;
        if (keys.Get(i) == IndexPair<int>(0, 2))
            second_found = true;
        if (keys.Get(i) == IndexPair<int>(1, 1))
            third_found = true;
    }
    assert(first_found && second_found && third_found);

    std::cout << "testKeys passed" << std::endl;
}

void testGetItems()
{
    int array[2][3] = { {1, 0, 2}, {0, 3, 0} };
    SparseMatrix<int> matrix = createSparseMatrixFromArray(2, 3, reinterpret_cast<int*>(array));
    ArraySequence<std::pair<IndexPair<int>, int>> items = matrix.GetItems();
    assert(items.GetLength() == 3);

    bool first_found = false;
    bool second_found = false;
    bool third_found = false;
    for (int i = 0; i < items.GetLength(); ++i)
    {
        if (items.Get(i).first == IndexPair<int>(0, 0) && items.Get(i).second == 1)
            first_found = true;
        if (items.Get(i).first == IndexPair<int>(0, 2) && items.Get(i).second == 2)
            second_found = true;
        if (items.Get(i).first == IndexPair<int>(1, 1) && items.Get(i).second == 3)
            third_found = true;
    }
    assert(first_found && second_found && third_found);

    std::cout << "testGetItems passed" << std::endl;
}