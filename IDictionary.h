#pragma once
#include <cstddef>
#include "Iterator.h"

template <class Key, class Value, class Hash = std::hash<Key>>
class IDictionary
{
public:
    virtual ~IDictionary() {}

    virtual size_t GetCount() const = 0;

    virtual size_t GetCapacity() const = 0;

    virtual Value Get(const Key& key) const = 0;
    virtual bool ContainsKey(const Key& key) const = 0;
    virtual void Add(const Key& key, const Value& element) = 0;
    virtual void Delete(const Key& key) = 0;
    virtual void Update(const Key& key, const Value& element) = 0;
    virtual ArraySequence<std::pair<Key, Value>> GetAll() const = 0;
    virtual ArraySequence<Key> Keys() const = 0;
    virtual std::unique_ptr < IDictionaryIterator<Key, Value>> begin() const = 0;
    virtual std::unique_ptr < IDictionaryIterator<Key, Value>> end() const = 0;
};
/*
template <typename T1, typename T2>
std::ostream& operator << (std::ostream& out, const IDictionary<T1, T2>& dictionary)
{
    out << *dictionary.dict;
    return out;
}
*/