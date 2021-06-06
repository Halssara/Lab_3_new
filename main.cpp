#include <iostream>
#include <vector>
using namespace std;
#include "histogram.h"
#include <curl/curl.h>
Input read_input (istream& in, bool prompt)
{
    Input data;
    if (prompt)
    {
        cerr << "Enter number count: ";
        in >> data.number_count;

        cerr << "Enter numbers: ";
        data.numbers = input_numbers(in, data.number_count);

        cerr << "Enter bin count: ";
        in >> data.bin_count;
    }
    else
    {
        in >> data.number_count;
        data.numbers = input_numbers(in, data.number_count);
        in >> data.bin_count;
    }
    return data;
}
int main (int argc, char* argv[])
{
    if (argc > 1)
    {
        cout << argc;
        cout << argv[0];
        return 0;
    }
    Input input;
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_size = SCREEN_WIDTH - 3 - 1;
    input = read_input (cin, true);
    vector <string> color(input.bin_count);
    color_add(input.bin_count, color, cin);
    const auto bins = make_histogram(input);
    show_histogram_svg(bins, input.bin_count, color);
    getchar ();
    return 0;
}
