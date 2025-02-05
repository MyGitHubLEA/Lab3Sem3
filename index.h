#pragma once
//#//include "C:\Users\Екатерина\source\repos\Laba4\AVLTree.h"

/*
template <class T>
bool asc(std::pair<int, T> a, std::pair<int, T> b)
{
	return a.second < b.second;
}

template <class T>
class IndexTree
{
public:
    AVLTree<std::pair<int, T>>* tree;
    T(Student::* getParam)() const;

public:
    IndexTree(ArraySequence<Student>& seq, T(Student::*getParam)() const)
    {
        this->getParam = getParam;
        bool (*cmp)(std::pair<int, T>, std::pair<int, T>) = asc;
		std::pair<int, T> first( 0, (seq.Get(0).*getParam)() );
		tree = new AVLTree<std::pair<int, T>>(first, cmp);
		int size = seq.GetLength();
		
		for (int i = 1; i < size; ++i)
		{
			std::pair<int, T> newp(i, (seq.Get(i).*getParam)());
			tree->Insert(newp);
		}
    }

    ~IndexTree() = default;

    int GetCode(T index)
    {
		std::pair<int, T> key (0, index);
        return this->tree->Search(key).first;
    }
	


};
*/
