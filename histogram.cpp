#include "histogram.h"
#include <iostream>
using namespace std;

void find_minmax(const vector<double>& numbers, double& min, double& max)
{
    min = numbers[0];
    max = numbers[0];
    for (double x : numbers)
    {
        if (x < min)
        {
            min = x;
        }
        if (x > max)
        {
            max = x;
        }
    }
}

vector <size_t>
make_histogram (Input data)
{
    vector <size_t> bins (data.bin_count);
    double min, max;
    find_minmax(data.numbers, min, max);
    double bin_size = (max - min) / data.bin_count;
    for (size_t i = 0; i < data.number_count; i++)
        {
            bool found = false;
            for (size_t j = 0; (j < data.bin_count - 1) && !found; j++)
            {
                auto lo = min + j * bin_size;
                auto hi = min + (j + 1) * bin_size;
                if ((lo <= data.numbers[i]) && (data.numbers[i] < hi))
                {
                    bins[j]++;
                    found = true;
                }
            }
            if (!found)
            {
                bins[data.bin_count - 1]++;
            }
        }
    return bins;
}

vector<double>
input_numbers(istream& in, size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        in >> result[i];
    }
    return result;
}
