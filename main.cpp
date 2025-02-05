
#include "GetData.h"
#include "Histogram.h"
#include "SparseMatrix.h"
#include "TestAllStruct.h"
#include "SparseVector.h"
#include <chrono>
#include <random>
#include <windows.h> 
#include <psapi.h> 

size_t getMemoryUsage() 
{
    PROCESS_MEMORY_COUNTERS pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
    return pmc.WorkingSetSize; // Использование памяти в байтах
}

int main()
{ 
    
	testUniformBuckets();
	testNonUniformBuckets();
	testDoubleData();
	testEmptyHistogram();
	testEmptyData();

	testAddAndGet();
	testRemove();
	testUpdate();
	testAddition();
	testScalarMultiplication();
	testMatrixMultiplication();
	testNorm();
	testNormalize();
	testKeys();
	testGetItems();

	testSparseVectorAddAndGet();
	testSparseVectorRemove();
	testSparseVectorUpdate();
	testSparseVectorAddition();
	testSparseVectorScalarMultiplication();
	testSparseVectorVectorMultiplication();
	testSparseVectorNorm();
	testSparseVectorNormalize();
	testSparseVectorKeys();
	testSparseVectorGetItems();

	int size = 100;
	SparseMatrix<double> matrix1(size, size);
	SparseMatrix<double> matrix2(size, size);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0.0, 1.0);

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if (dis(gen) < 0.01)
			{
				matrix1.Add({ i, j }, dis(gen));
				matrix2.Add({ i, j }, dis(gen));

			}
		}
	}

	// память время

	size_t memoryBefore = getMemoryUsage();
	auto start = std::chrono::high_resolution_clock::now();
	SparseMatrix<double> result;
	result = matrix1 * matrix2;
	auto end = std::chrono::high_resolution_clock::now();
	size_t memoryAfter = getMemoryUsage();

	std::chrono::duration<double> elapsed = end - start;

	std::cout << "Time with copy: " << elapsed.count() << " s\n";
	std::cout << "Memory usage: " << (memoryAfter - memoryBefore) / (1024.0 * 1024.0) << " MB\n"; // в мегабайтах

	memoryBefore = getMemoryUsage();
	start = std::chrono::high_resolution_clock::now();
	//auto rresult = matrix1.Mult(matrix2); 
	end = std::chrono::high_resolution_clock::now();
	memoryAfter = getMemoryUsage();

	elapsed = end - start;

	std::cout << "Time with unique_ptr: " << elapsed.count() << " s\n";
	std::cout << "Memory usage: " << (memoryAfter - memoryBefore) / (1024.0 * 1024.0) << " MB\n";


	//std::cout << SM<< std::endl;
	return 0;

} 















