#include "Histogram.h"
#include <cassert>


void testUniformBuckets() 
{
    int boundariesData []  {0, 10, 20, 30};
    ArraySequence<int> boundaries = createSequence<int>(boundariesData);
    auto valueExtractor = [](int val) { return val; };

    Histogram<int, int> histogram(boundaries, valueExtractor);

    histogram.Add(5);
    histogram.Add(15);
    histogram.Add(25);
    histogram.Add(5);

    auto hist = histogram.GetHistogram();
    assert(hist.Get(0).count == 2);
    assert(hist.Get(10).count == 1);
    assert(hist.Get(20).count == 1);
    assert(hist.Get(0).minValue == 5);
    assert(hist.Get(0).maxValue == 5);
    assert(hist.Get(0).totalValue == 10);
    assert(hist.Get(10).minValue == 15);
    assert(hist.Get(10).maxValue == 15);
    assert(hist.Get(10).totalValue == 15);
    assert(hist.Get(20).minValue == 25);
    assert(hist.Get(20).maxValue == 25);
    assert(hist.Get(20).totalValue == 25);

    histogram.Reset();
    hist = histogram.GetHistogram();
    assert(hist.Get(0).count == 0);
    assert(hist.Get(0).totalValue == 0);
    assert(hist.Get(0).maxValue == std::numeric_limits<int>::lowest());
    assert(hist.Get(0).minValue == std::numeric_limits<int>::max());

    std::cout << "testUniformBuckets passed" << std::endl;
}

void testNonUniformBuckets() {
    //std::vector<std::pair<int, int>> rangesData = { {0, 10}, {10, 20}, {20, 30} };
    ArraySequence<std::pair<int, int>> ranges;
    ranges.Append({ 0, 10 });
    ranges.Append({ 10, 20 });
    ranges.Append({ 20, 30 });

    auto valueExtractor = [](int val) { return val; };

    Histogram<int, int> histogram(ranges, valueExtractor);

    histogram.Add(5);
    histogram.Add(15);
    histogram.Add(25);
    histogram.Add(5);

    auto hist = histogram.GetHistogram();
    assert(hist.Get(0).count == 2);
    assert(hist.Get(10).count == 1);
    assert(hist.Get(20).count == 1);
    assert(hist.Get(0).minValue == 5);
    assert(hist.Get(0).maxValue == 5);
    assert(hist.Get(0).totalValue == 10);
    assert(hist.Get(10).minValue == 15);
    assert(hist.Get(10).maxValue == 15);
    assert(hist.Get(10).totalValue == 15);
    assert(hist.Get(20).minValue == 25);
    assert(hist.Get(20).maxValue == 25);
    assert(hist.Get(20).totalValue == 25);


    histogram.Reset();
    hist = histogram.GetHistogram();
    assert(hist.Get(0).count == 0);
    assert(hist.Get(0).totalValue == 0);
    assert(hist.Get(0).maxValue == std::numeric_limits<int>::lowest());
    assert(hist.Get(0).minValue == std::numeric_limits<int>::max());
    std::cout << "testNonUniformBuckets passed" << std::endl;
}

void testDoubleData() 
{
    double boundariesData [] {0.0, 10.0, 20.0, 30.0};
    ArraySequence<double> boundaries = createSequence<double>(boundariesData);
    auto valueExtractor = [](double val) { return val; };

    Histogram<double, double> histogram(boundaries, valueExtractor);

    histogram.Add(5.5);
    histogram.Add(15.2);
    histogram.Add(25.8);
    histogram.Add(5.1);

    auto hist = histogram.GetHistogram();
    assert(hist.Get(0.0).count == 2);
    assert(hist.Get(10.0).count == 1);
    assert(hist.Get(20.0).count == 1);
    assert(abs(hist.Get(0.0).minValue - 5.1) < 0.001);
    assert(abs(hist.Get(0.0).maxValue - 5.5) < 0.001);
    assert(abs(hist.Get(0.0).totalValue - 10.6) < 0.001);
    assert(abs(hist.Get(10.0).minValue - 15.2) < 0.001);
    assert(abs(hist.Get(10.0).maxValue - 15.2) < 0.001);
    assert(abs(hist.Get(10.0).totalValue - 15.2) < 0.001);
    assert(abs(hist.Get(20.0).minValue - 25.8) < 0.001);
    assert(abs(hist.Get(20.0).maxValue - 25.8) < 0.001);
    assert(abs(hist.Get(20.0).totalValue - 25.8) < 0.001);

    histogram.Reset();
    hist = histogram.GetHistogram();
    assert(hist.Get(0.0).count == 0);
    assert(abs(hist.Get(0.0).totalValue - 0.0) < 0.001);
    assert(hist.Get(0.0).maxValue == std::numeric_limits<double>::lowest());
    assert(hist.Get(0.0).minValue == std::numeric_limits<double>::max());

    std::cout << "testDoubleData passed" << std::endl;
}


void testEmptyHistogram()
{
    int boundariesData [] { 0, 10, 20, 30 };
    ArraySequence<int> boundaries = createSequence<int>(boundariesData);
    auto valueExtractor = [](int val) { return val; };
    Histogram<int, int> histogram(boundaries, valueExtractor);
    auto hist = histogram.GetHistogram();
    for (int i = 0; i < boundaries.GetLength(); ++i)
    {
        assert(hist.Get(boundaries.Get(i)).count == 0);
    }


    histogram.Reset();
    hist = histogram.GetHistogram();
    for (int i = 0; i < boundaries.GetLength(); ++i)
    {
        assert(hist.Get(boundaries.Get(i)).count == 0);
        assert(hist.Get(boundaries.Get(i)).maxValue == std::numeric_limits<int>::lowest());
        assert(hist.Get(boundaries.Get(i)).minValue == std::numeric_limits<int>::max());
    }
    std::cout << "testEmptyHistogram passed" << std::endl;
}

void testEmptyData()
{
    int boundariesData [] { 0, 10, 20, 30 };
    ArraySequence<int> boundaries = createSequence<int>(boundariesData);
    auto valueExtractor = [](int val) { return val; };
    Histogram<int, int> histogram(boundaries, valueExtractor);
    histogram.Reset();
    auto hist = histogram.GetHistogram();
    for (int i = 0; i < boundaries.GetLength(); ++i)
    {
        assert(hist.Get(boundaries.Get(i)).count == 0);
    }

    histogram.Reset();
    hist = histogram.GetHistogram();
    for (int i = 0; i < boundaries.GetLength(); ++i)
    {
        assert(hist.Get(boundaries.Get(i)).count == 0);
        assert(hist.Get(boundaries.Get(i)).maxValue == std::numeric_limits<int>::lowest());
        assert(hist.Get(boundaries.Get(i)).minValue == std::numeric_limits<int>::max());
    }
    std::cout << "testEmptyData passed" << std::endl;

}