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

void
svg_begin(double width, double height)
{
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void
svg_end()
{
    cout << "</svg>\n";
}

void
svg_text(double left, double baseline, string text)
{
    cout << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>";
}

void svg_rect(double x, double y, double width, double height, string stroke, string fill)
{
    cout <<"<rect x='"<<x<<"' y='"<<y<<"' width='"<<width<<"' height='"<<height<<"' stroke='"<<stroke<<"' fill='"<<fill<<"' />";
}

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
