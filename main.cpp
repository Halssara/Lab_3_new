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
        CURL *curl = curl_easy_init();
        if(curl)
        {
            CURLcode res;
            curl_easy_setopt(curl, CURLOPT_URL, argc);
            res = curl_easy_perform(curl);
        if (res != 0)
        {
            curl_easy_cleanup(curl);
            exit(1);
        }
        }
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
