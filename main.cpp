#include <iostream>
#include <vector>
using namespace std;
#include "histogram.h"
vector <size_t>
make_histogram (const vector<double>& numbers, const size_t& number_count, const size_t& bin_count, const double min, const double max, const double bin_size)
{
    vector <size_t> bins (bin_count);
    for (size_t i = 0; i < number_count; i++)
        {
            bool found = false;
            for (size_t j = 0; (j < bin_count - 1) && !found; j++)
            {
                auto lo = min + j * bin_size;
                auto hi = min + (j + 1) * bin_size;
                if ((lo <= numbers[i]) && (numbers[i] < hi))
                {
                    bins[j]++;
                    found = true;
                }
            }
            if (!found)
            {
                bins[bin_count - 1]++;
            }
        }
    return bins;
}


vector<double>
input_numbers(size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        cin >> result[i];
    }
    return result;
}
int main ()
{
    size_t number_count;
    size_t bin_count;
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_size = SCREEN_WIDTH - 3 - 1;
    cerr << "Enter number count: ";
    cin >> number_count;
    cerr << "Enter bin count:";
    cin >> bin_count;
    vector <string> color(bin_count);
    color_add(bin_count, color);
    const auto numbers = input_numbers(number_count);
    double min, max;
    find_minmax(numbers, min, max);
    double bin_size = (max - min) / bin_count;
    const auto bins = make_histogram(numbers, number_count, bin_count, min, max, bin_size);
    show_histogram_svg(bins, bin_count, color);
    getchar ();
    return 0;
}
