#pragma once
#include "C:\Users\Екатерина\source\repos\Lab1Sem3\Students.h"
#include "C:\Users\Екатерина\source\repos\Laba2\Sequence.h"
//#include "..\Lab1Sem3\Comparators.h"
#include <fstream>
#include <sstream>
#include <random>
#include <string>
#include <vector>

#include <iomanip> 

template <typename T>
void MakeSequence(ArraySequence<T>* seq, std::ifstream& in)
{
	std::string s;
	int size = seq->GetLength();
	for (int i = 0; i < size; ++i)
	{
		std::getline(in, s);

		std::stringstream ss(s);
		T p;
		ss >> p;
		seq->Set(p, i);
	}
	in.close();
}


template <typename T>
T generateRandomElement(double density, T min, T max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> distrib(0.0, 1.0);
    if (distrib(gen) < density)
    {
        if constexpr (std::is_integral_v<T>) 
        {
            std::uniform_int_distribution<> intDistrib(min, max);
            return intDistrib(gen);
        }
        else if constexpr (std::is_floating_point_v<T>) 
        {
            std::uniform_real_distribution<T> floatDistrib(min, max);
            return floatDistrib(gen);
        }
        else 
        {
            throw std::runtime_error("Unsupported type");
        }
    }
    return static_cast<T>(0);

}

template <typename T>
bool generateRandomSparseMatrixFile(const std::string& filename, int rows, int columns, double density, T min, T max) 
{
    std::ofstream file(filename);
    if (!file.is_open()) 
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }
    file << rows << " " << columns << std::endl;
    file << std::fixed << std::setprecision(17);
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            file << generateRandomElement<T>(density, min, max) << " ";
        }
        file << std::endl;
    }

    file.close();
    return true;
}
