#pragma once
#include "KeyValue.h"
#include "..\..\..\Documents\Laba3Sem3\HashTable.h"

template <class Key, class Value> //нужна хеш функция для некоторых кей студент
class IDictionaryIterator
{
public:
    virtual ~IDictionaryIterator() = default;
    virtual void FindNext() = 0;
    virtual const KeyValue<Key, Value>& operator*() = 0;
    virtual bool operator==(const IDictionaryIterator <Key, Value>& other) const = 0;
    virtual bool operator!=(const IDictionaryIterator<Key, Value>& other) const = 0;
    virtual std::unique_ptr<IDictionaryIterator<Key, Value>> operator++() = 0;

    virtual Key GetKey() const = 0;
    virtual Value GetValue() const = 0;

};