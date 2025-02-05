#pragma once

#include "LinkedList.h"
#include <iostream>

template <typename T> class Sequence
{
public:
	virtual T GetFirst() const = 0;
	virtual T GetLast() const = 0;
	virtual T Get(int index) const = 0;
	virtual const T& GetTest(int index) const = 0;
	virtual int GetLength() const = 0;
};

template <typename T> class MutableSequence : public Sequence<T>
{
public:
	virtual void Set(const T& item, int index) = 0;
	virtual void Append(const T& item) = 0;
	virtual void Prepend(const T& item) = 0;
	virtual void InsertAt(const T& item, int index) = 0;
	virtual Sequence<T>* GetSubsequence(int start, int end) const = 0;
	virtual Sequence<T>* Concat(const Sequence<T>* seq) const = 0;
};

template <typename T> class ImmutableSequence : public Sequence<T>
{
public:
	virtual ImmutableSequence<T>* Set(const T& item, int index) const = 0;
	virtual ImmutableSequence<T>* Append(const T& item) const = 0;
	virtual ImmutableSequence<T>* Prepend(const T& item) const = 0;
	virtual ImmutableSequence<T>* InsertAt(const T& item, int index) const = 0;
	virtual Sequence<T>* GetSubsequence(int start, int end) const = 0;
	virtual Sequence<T>* Concat(const Sequence<T>* seq) const = 0;
};

/*
template <typename T> class ListSequence : public MutableSequence<T> {
private:
	LinkedList<T>* list; 
public:
	ListSequence() 
	{
		this->list = new LinkedList<T>();
	}
	ListSequence(const ListSequence<T>& seq)
	{
		this->list = new LinkedList<T>(*seq.list);
	}

	ListSequence(T* items, int size) {
		this->list = new LinkedList<T>(items, size);
	}

	virtual ~ListSequence() {
		delete this->list;
	}

	T GetFirst() const override
	{
		if (this->GetLength() == 0) throw std::out_of_range("Sequence is empty\n");
		return this->list->GetFirst();
	}

	T GetLast() const override
	{
		if (this->GetLength() == 0) throw std::out_of_range("Sequence is empty\n");
		return this->list->GetLast();
	}

	T Get(int index) const override
	{
		return this->list->Get(index);
	}

	int GetLength() const override {
		return this->list->GetLength();
	}

	ListSequence<T>* GetSubsequence(int start, int end) const override
	{
		ListSequence<T>* subList = new ListSequence<T>();
		subList->list = this->list->GetSubList(start, end);
		return subList;
	}

	void Set(const T& item, int index) override
	{
		this->list->Set(item, index);
	}

	void Append(const T& item) override
	{
		this->list->Append(item);
	}

	void Prepend(const T& item) override
	{
		this->list->Prepend(item);
	}

	void InsertAt(const T& item, int index) override
	{
		this->list->InsertAt(item, index);
	}

	ListSequence<T>* Concat(const Sequence<T>* seq) const override
	{
		ListSequence<T>* newList = new ListSequence<T>(*this);
		for (int i = 0; i < seq->GetLength(); ++i)
			newList->list->Append(seq->Get(i));
		return newList;
	}

};


template <typename T>
std::ostream& operator <<(std::ostream& out, const Sequence<T>& Seq)
{
	for (int i = 0; i < Seq.GetLength(); ++i)
	{
		out << Seq.Get(i) << " ";
	}
	out << "" << std::endl;
	return out;
}
*/