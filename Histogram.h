#pragma once

//#include "C:\Users\≈катерина\source\repos\Lab1Sem3\Students.h"
//#include "..\Laba2\Sequence.h"
#include "C:\Users\≈катерина\Documents\Laba3Sem3\HashTable.h"
#include <functional>

template <typename T, typename TKey>
class Histogram 
{  
	struct DataSummary
	{
		size_t count = 0;
		TKey minValue = std::numeric_limits<TKey>::max();
		TKey maxValue = std::numeric_limits<TKey>::lowest();
		double totalValue = 0.0;

		void accumulate(const TKey& value)
		{
			count++;
			minValue = std::min(minValue, value);
			maxValue = std::max(maxValue, value);
			totalValue += value;
		}

        double getAverageValue() const
		{
			if (count == 0) return 0;
			return totalValue / count;
		}

        void clear() 
        {
			count = 0;
			minValue = std::numeric_limits<TKey>::max();
			maxValue = std::numeric_limits<TKey>::lowest();
			totalValue = 0.0;
		}
	};

    template <typename U, typename V>
    friend std::ostream& operator<<(std::ostream& os, const typename Histogram<U, V>::DataSummary& summary);

public:
    
    Histogram(ArraySequence<TKey>& bucketBoundaries, std::function<TKey(const T&)> valueExtractor);
    Histogram(ArraySequence<std::pair<TKey, TKey>>& ranges, std::function<TKey(const T&)> valueExtractor);

    void Add(const T& data);
    const HashTable<TKey, DataSummary>& GetHistogram() const;
    ArraySequence<TKey> GetBoundaries() const;
   
    void Reset();

private:
    HashTable<TKey, DataSummary> table; 
    ArraySequence<TKey> bucketPoints; 
    ArraySequence<std::pair<TKey, TKey>> bucketRanges; 
    std::function<TKey(const T&)> getValue; 
    bool usingRanges = false; 

    // бакет по значению
    TKey IdentifyBucket(const TKey& value) const;
};

template <typename T, typename TKey>
Histogram<T, TKey>::Histogram(ArraySequence<TKey>& bucketBoundaries, std::function<TKey(const T&)> valueExtractor)
    : bucketPoints(bucketBoundaries), getValue(valueExtractor), usingRanges(false)
{
    for (int i = 0; i < bucketBoundaries.GetLength(); ++i)
    {
        const auto& boundary = bucketBoundaries.Get(i);
        table.Add(boundary, DataSummary());
    }
}

template <typename T, typename TKey>
Histogram<T, TKey>::Histogram(ArraySequence<std::pair<TKey, TKey>>& ranges, std::function<TKey(const T&)> valueExtractor)
    : bucketRanges(ranges), getValue(valueExtractor), usingRanges(true) 
{
    for (int i=0; i< ranges.GetLength(); ++i)
    {
        const auto& range = ranges.Get(i);
        table.Add(range.first, DataSummary());
    }
}


template <typename T, typename TKey>
void Histogram<T, TKey>::Add(const T& data) 
{
    TKey extractedValue = getValue(data); 
    TKey bucketKey;
  //  if (!usingRanges)
    bucketKey = IdentifyBucket(extractedValue); 
   // else
     //   bucketKey = identifyBucket(extractedValue);
    if (table.ContainsKey(bucketKey))
    {
        auto summary = table.Get(bucketKey);
        summary.accumulate(extractedValue);
        table.Update(bucketKey, summary);
    }
}

template <typename T, typename TKey>
void Histogram<T, TKey>::Reset() 
{
    for (auto iterator = table.begin(); *iterator != *table.end(); ++(*iterator))
    {
        DataSummary summary = (*iterator).GetValue();
        summary.clear();
        table.Update((*iterator).GetKey(), summary);
    }
}


template <typename T, typename TKey>
const HashTable<TKey, typename Histogram<T, TKey>::DataSummary>& Histogram<T, TKey>::GetHistogram() const
{
    return table; 
}


template <typename T, typename TKey>
ArraySequence<TKey> Histogram<T, TKey>::GetBoundaries() const
{
    return bucketPoints;
}

// поиск бакета
template <typename T, typename TKey>
TKey Histogram<T, TKey>::IdentifyBucket(const TKey& value) const 
{

    if (usingRanges) 
    {
        if (bucketRanges.GetLength() == 0) 
        {
            throw std::invalid_argument("Bucket ranges are empty.");
        }
        if (value < bucketRanges.Get(0).first) 
        {
            return bucketRanges.Get(0).first;
        }
        for (int i = 0; i < bucketRanges.GetLength(); ++i) 
        {
            const auto& range = bucketRanges.Get(i);
            if (value >= range.first && value < range.second) 
            {
                return range.first;
            }
        }
        return bucketRanges.Get(bucketRanges.GetLength() - 1).first; 
    }
    else 
    {
        if (bucketPoints.GetLength() == 0)
        {
            throw std::invalid_argument("Bucket points are empty.");
        }
        if (value < bucketPoints.Get(0)) 
        {
            return bucketPoints.Get(0); 
        }
        for (size_t i = 0; i < bucketPoints.GetLength(); ++i) 
        {
            if (i + 1 < bucketPoints.GetLength() && value >= bucketPoints.Get(i) && value < bucketPoints.Get(i + 1)) 
            {
                return bucketPoints.Get(i);
            }
        }
        return bucketPoints.Get(bucketPoints.GetLength() - 1); 
    }

}

template <typename U, typename V>
std::ostream& operator<<(std::ostream& os, const typename Histogram<U, V>::DataSummary& summary)
{
    os << "Count = " << summary.count
        << ", Min = " << summary.minValue << ", Max = " << summary.maxValue
        << ", Avg = " << summary.getAverageValue();
    return os;
}
