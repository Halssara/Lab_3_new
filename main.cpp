#include <iostream>
#include <vector>
using namespace std;
#include "histogram.h"
void
show_histogram_svg(const vector<size_t>& bins, const size_t bin_count)
{
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    const auto MAX_WIGTH = IMAGE_WIDTH - TEXT_WIDTH;
    size_t max_bins = bins [0];
    for (size_t i = 0; i < bin_count; i++)
    {
        if (bins [i] > max_bins)
        max_bins = bins[i] ;
    }
    max_bins = max_bins * BLOCK_WIDTH;
    double height;
    if (max_bins <= MAX_WIGTH)
        height = 1;
    else
    height = (static_cast < double > (MAX_WIGTH) / max_bins );

    double top = 0;
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    for (size_t bin : bins )
    {
        const double bin_width = BLOCK_WIDTH * bin;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH , top, bin_width * height, BIN_HEIGHT, "black", "#000000");
        top += BIN_HEIGHT;
    }
    svg_end();
}

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
    const auto numbers = input_numbers(number_count);
    double min, max;
    find_minmax(numbers, min, max);
    double bin_size = (max - min) / bin_count;
    const auto bins = make_histogram(numbers, number_count, bin_count, min, max, bin_size);
    show_histogram_svg(bins, bin_count);
    getchar ();
    return 0;
}
