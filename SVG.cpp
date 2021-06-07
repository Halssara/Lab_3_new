#include "histogram.h"
#include <iostream>
#include <windows.h>
#include <sstream>
#include <string>
using namespace std;

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
string
make_info_text() {
    stringstream buffer;
    DWORD WINAPI GetVersion(void);
    DWORD info = GetVersion();
    DWORD mask = 0b00000000'00000000'11111111'11111111;
    DWORD version = info & mask;
    DWORD platform = info >> 16;
    DWORD maska = 0b00000000'11111111;
    if ((info & 0x40000000) == 0)
    {
        DWORD version_major = version & maska;
        DWORD version_minor = version >> 8;
        DWORD build = platform;
        buffer << "Windows v" << version_major << "." << version_minor << "(build " << build << ")\n";
    }
    DWORD size = MAX_COMPUTERNAME_LENGTH + 1;
    char name[MAX_COMPUTERNAME_LENGTH + 1];

    GetComputerNameA(name, &size);
    buffer << "PC name: " << name << '\n';
    return buffer.str();
}


void
show_histogram_svg(const vector<size_t>& bins, const size_t bin_count, Input data)
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
    int help_color = 0;
    for (size_t bin : bins )
    {
        string COLOR = "#" + data.color[help_color];
        const double bin_width = BLOCK_WIDTH * bin;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH , top, bin_width * height, BIN_HEIGHT, "black", COLOR);
        top += BIN_HEIGHT;
        help_color ++;
    }
    svg_text(1, top + TEXT_BASELINE, make_info_text());
    svg_end();
}
