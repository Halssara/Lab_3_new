#include <iostream>
#include <vector>
using namespace std;
#include "histogram.h"
Input read_input (istream& in)
{
    Input data;

    cerr << "Enter number count: ";
    in >> data.number_count;

    cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, data.number_count);

    cerr << "Enter bin count: ";
        in >> data.bin_count;

    return data;
}
int main ()
{
    Input input;
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_size = SCREEN_WIDTH - 3 - 1;
    input = read_input (cin);
    vector <string> color(input.bin_count);
    color_add(input.bin_count, color, cin);
    const auto bins = make_histogram(input);
    show_histogram_svg(bins, input.bin_count, color);
    getchar ();
    return 0;
}
