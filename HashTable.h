#pragma once
#include <functional>
#include "C:\Users\Екатерина\source\repos\Laba2\Sequence.h"
#include "C:\Users\Екатерина\source\repos\Project5\IDictionary.h"
#include "Iterator.h"
#include "KeyValue.h"
#include < memory >
template <class Key, class Value, class Hash = std::hash<Key>> 
class HashTable : public IDictionary<Key, Value>
{
private:

    ArraySequence<ArraySequence<KeyValue<Key, Value>>> table;
    size_t count;
    double threshold = 0.7;

    size_t Index(const Key& key) const
    {
        Hash hashFunction;
        return hashFunction(key) % table.GetLength();
    }

    void Rehash() 
    {
        size_t oldCapacity = table.GetLength();
        size_t newCapacity = oldCapacity * 2 + 1;
        ArraySequence<ArraySequence<KeyValue<Key, Value>>> newTable(newCapacity);  
        
     
        for (size_t i = 0; i < oldCapacity; ++i) 
        {
            for (size_t j = 0; j < table.Get(i).GetLength(); ++j) 
            {
                const auto& pair = table.Get(i).Get(j);
                
                Hash hashFunction;
                size_t newIndex = hashFunction(pair.key) % newCapacity;
                //std::cout << "hash: "<<hashFunction(pair.key) % newCapacity << std::endl;
                    //Hash()(pair.key) % newCapacity;

                newTable.Get(newIndex).Append(pair); 
            }
        }
      //  std::cout << newTable.GetLength();
        table = newTable; 
    }
public:
    HashTable() : table(10), count(0) {}

    size_t GetCapacity() const
    {
        return table.GetLength();
    }

    Value Get(const Key& key) const
    {
        size_t index = Index(key);

        for (size_t i = 0; i < table.Get(index).GetLength(); ++i) 
        {
            if (key == table.Get(index).Get(i).key) 
            {
                return (table.Get(index).Get(i).value);  
            }
        }

        return Value();
    }

    bool ContainsKey(const Key& key) const
    {
        size_t index = Index(key);

        for (size_t i = 0; i < table.Get(index).GetLength(); ++i)
        {
            if (key == table.Get(index).Get(i).key)
            {
                return true;  
            }
        }

        return false; 
    }

    void Add(const Key& key, const Value& value) 
    {
        if (ContainsKey(key))
        {
            size_t index = Index(key);
            for (size_t i = 0; i < table.Get(index).GetLength(); ++i) 
            {
                if (key == table.Get(index).Get(i).key) 
                {
                    table.Get(index).Get(i).value = value;
                    return;

                }
            }
        }

        if ((double)(count + 1) / table.GetLength() > threshold)
        {
          //  std::cout << "Hi there!";
            Rehash(); 
        }

        size_t index = Index(key);
        KeyValue<Key, Value> kv (key, value);
        table.Get(index).Append(kv); 
        ++count; 
    }

    void Update(const Key& key, const Value& value)
    {
        if (ContainsKey(key))
        {
            size_t index = Index(key);
            for (size_t i = 0; i < table.Get(index).GetLength(); ++i)
            {
                if (key == table.Get(index).Get(i).key)
                {
                    table.Get(index).Get(i).value = value;
                    return;
                }
            }
        }
    }

    void Delete(const Key& key) 
    {
        size_t index = Index(key);

        for (size_t i = 0; i < table.Get(index).GetLength(); ++i) 
        {
            if (key == table.Get(index).Get(i).key)
            {
                (table.Get(index)).Delete(i);
                --count; 
                return;
            }
        }
    }

    ArraySequence<Key> Keys() const
    {
        ArraySequence<Key> keyList;

        for (size_t i = 0; i < table.GetLength(); ++i) 
        {
            for (size_t j = 0; j < table.Get(i).GetLength(); ++j)
            {
                keyList.Append(table.Get(i).Get(j).key); 
            }
        }

        return keyList; 
    }

    size_t GetCount() const 
    {
        return count;
    }

    bool empty() const 
    {
        return count == 0;
    }
   
    class HashTableIterator : public IDictionaryIterator<Key, Value>
    {
    public:
        const HashTable& hashTable;
        size_t currentIndex;
        size_t currentBucket;
        bool isValid;

      //  std::pair<const Key&, const Value&> currentValue;
      //  bool valid = false;

    public:
        HashTableIterator(const HashTable<Key, Value>& hashTable) : hashTable(hashTable), currentBucket(0), currentIndex(0), isValid(false)
        {
            FindNext();
        }

        HashTableIterator(const HashTable<Key, Value>& hashTable, int currentbuckect) : hashTable(hashTable), currentBucket(currentbuckect), 
            currentIndex(0), isValid(false)
        {
            FindNext();
        }

        void FindNext() override
        {

            isValid = false; 
            while (currentBucket < hashTable.table.GetLength()) 
            {
                if (currentIndex < hashTable.table.Get(currentBucket).GetLength()) 
                {
                    isValid = true; 
                    return;
                }
                else {
                    currentBucket++;
                    currentIndex = 0;
                }
            }
            currentBucket = hashTable.table.GetLength(); // конец

        }

        
        const KeyValue<Key, Value>& operator*() override 
        {

            if (!isValid) 
            {
                throw std::out_of_range("Iterator out of range");
            }
            return hashTable.table.Get(currentBucket).Get(currentIndex);
        }

        Key GetKey() const override
        {
            return hashTable.table.Get(currentBucket).Get(currentIndex).key;
        }

        Value GetValue() const override
        {
            return hashTable.table.Get(currentBucket).Get(currentIndex).value;
        }

        bool operator!=(const IDictionaryIterator<Key, Value>& other) const override 
        {
            const HashTableIterator& otherIterator = dynamic_cast<const HashTableIterator&>(other);
            return (currentBucket != otherIterator.currentBucket || currentIndex != otherIterator.currentIndex);
        }

        bool operator==(const IDictionaryIterator<Key, Value>& other) const override
        {
            const HashTableIterator& otherIterator = dynamic_cast<const HashTableIterator&>(other);
            return currentBucket == otherIterator.currentBucket && currentIndex == otherIterator.currentIndex;
        }

        std::unique_ptr<IDictionaryIterator<Key, Value>> operator++() override
        {
            currentIndex++;
            FindNext();
            return std::make_unique<HashTableIterator>(hashTable, currentBucket);
        }
    };

    std::unique_ptr<IDictionaryIterator<Key, Value>> begin() const override
    {
        auto iterator = std::make_unique<HashTableIterator>(*this);
        return iterator;
    }

    std::unique_ptr<IDictionaryIterator<Key, Value>> end() const override
    {
      //  std::unique_ptr<IDictionaryIterator<Key, Value>> iterator(new HashTableIterator(*this, table.GetLength()));
        //(*iterator).currentBucket = table.GetLength();
        return std::make_unique<HashTableIterator>(*this, table.GetLength());
    }

    ArraySequence<std::pair<Key, Value>> GetAll() const
    {
        ArraySequence<std::pair<Key, Value>> all;
        try 
        {
            for (auto iterator = begin(); *iterator != *end(); ++(*iterator)) 
            {
                all.Append({ (**iterator).key, (**iterator).value });
            }
        }
        catch (const std::out_of_range& e) 
        {
            std::cerr << "Error in GetAll(): " << e.what() << std::endl;
        }
        return all;
    }

    template<class T, class U>
    friend std::ostream& operator<<(std::ostream& out, const IDictionary<T, U>& hashTable);
};

template <class Key, class Value>
std::ostream& operator<<(std::ostream& out, const IDictionary<Key, Value>& hashTable)
{
    for (auto iterator = hashTable.begin(); *iterator != *hashTable.end(); ++(*iterator))
    {
        out << (**iterator).key << " " << (**iterator).value << std::endl;
    }
    return out;
}
    