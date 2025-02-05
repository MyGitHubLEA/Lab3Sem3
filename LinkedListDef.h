#pragma once
#include <stdexcept>
#include <iostream>

template <typename T> 
class LinkedList
{
public: 
	LinkedList(T* items, int size)
	{
		this->ListSize = 0;
		for (int i = 0; i < size; ++i)
			this->Append(items[i]);
	}
	LinkedList()
	{
		this->ListSize = 0;
		this->FirstNode = nullptr;
	}

	T Get(int index)
	{
		if (index < 0 || index > this->GetLength())
			throw std::out_of_range("Index is out of range\n");
		Node <T>* current = this->FirstNode;
		for (int i = 0; i < index; ++i) 
		{
			current = current->NextElemPtr;
		}
		return current->Data;
	}

	int GetLength()
	{
		return this->ListSize;
	}

	void Append(T item) 
	{
		Node <T>* current = this->FirstNode;
		if (current == nullptr)
		{
			this->FirstNode = new Node<T>(item);
		}
		else 
		{
			while (current->NextElemPtr != nullptr)
			{
				current = current->NextElemPtr;
			}
			current->NextElemPtr = new Node<T>(item);
		}
		(this->ListSize)++;
	}

	void Prepend(T item)
	{
		Node<T>* NewFirstElem = new Node<T>(item, this->FirstNode);
		this->FirstNode = NewFirstElem;
		(this->ListSize)++;
	}

	void InsertAt(T item, int index) 
	{
		if (index < 0 || index >= this->GetLength()) 
			throw std::out_of_range("Index is out of range\n");
		if (index == 0) this->Prepend(item);
		else
		{
			Node <T>* current = this->FirstNode;
			Node<T>* NewElem = new Node<T>(item);
			for (int i = 1; i < index; ++i) //index = 3
			{
				current = current->NextElemPtr;
			}
			NewElem->NextElemPtr = current->NextElemPtr;
			current->NextElemPtr = NewElem;
			this->ListSize++;
		}
	}

	LinkedList(const LinkedList<T>& other)
	{
		this->ListSize = other.ListSize;
		this->FirstNode = new Node<T>(other.FirstNode->Data);
		Node<T>* current = this->FirstNode;
		Node<T>* otherCurrent = other.FirstNode->NextElemPtr;
		while (otherCurrent != nullptr) 
		{
			current->NextElemPtr = new Node<T>(otherCurrent->Data);
			current = current->NextElemPtr;
			otherCurrent = otherCurrent->NextElemPtr;
		}
	}

	~LinkedList()
	{
		while (ListSize)
		{
			Node<T>* temp = FirstNode;
			FirstNode = FirstNode->NextElemPtr;
			delete temp;
			ListSize--;
		}
	}

private:
	template <typename T>
	class Node
	{
	public:
		Node<T>* NextElemPtr;
		T Data;
		Node(T data = T(), Node* Nptr = nullptr)
		{
			this->NextElemPtr = Nptr;
			this->Data = data;
		}
	};
	Node <T>* FirstNode;
	int ListSize;
};
