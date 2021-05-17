#include <iostream>
#include <vector>
using namespace std;
#include "histogram.h"

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
    color_add(bin_count, color, cin);
    const auto numbers = input_numbers(number_count);
    const auto bins = make_histogram(numbers, number_count, bin_count);
    show_histogram_svg(bins, bin_count, color);
    getchar ();
    return 0;
}
