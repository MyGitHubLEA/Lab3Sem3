#pragma once
#include <string>

//void assertStringsEqual(const std::string& expected, const std::string& actual, const std::string& message);
void testHashTableAddAndFind();
void testHashTableDelete();
void testHashTableSize();
void testHashTableEmpty();
void testHashTableRehashing();
void testHashTableKeys();
void testHashTableDeleteWithKeys();

void testUniformBuckets();
void testNonUniformBuckets();
void testDoubleData();
void testEmptyHistogram();
void testEmptyData();


void testAddAndGet();
void testRemove();
void testUpdate();
void testAddition();
void testScalarMultiplication();
void testMatrixMultiplication();
void testNorm();
void testNormalize();
void testKeys();
void testGetItems();

void testSparseVectorAddAndGet();
void testSparseVectorRemove();
void testSparseVectorUpdate();
void testSparseVectorAddition();
void testSparseVectorScalarMultiplication();
void testSparseVectorVectorMultiplication();
void testSparseVectorNorm();
void testSparseVectorNormalize();
void testSparseVectorKeys();
void testSparseVectorGetItems();