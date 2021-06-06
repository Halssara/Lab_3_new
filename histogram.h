#ifndef HISTOGRAM_H_INCLUDED
#define HISTOGRAM_H_INCLUDED
#include <vector>
#include <string>
using namespace std;
struct Input
{
    vector<double> numbers;
    size_t bin_count;
    size_t number_count;
};
void find_minmax(const vector<double>& numbers, double& min, double& max);
void svg_begin(double width, double height);
void svg_end();
void svg_text(double left, double baseline, string text);
void svg_rect(double x, double y, double width, double height, string stroke, string fill);
void show_histogram_svg(const vector<size_t>& bins, const size_t bin_count, vector <string>& color);
void color_add(const size_t bin_count,vector <string>& color, istream& in);
vector<size_t> make_histogram (Input input);
vector<double> input_numbers(istream& in,size_t count);
Input read_input (istream& in, bool prompt);
#endif // HISTOGRAM_H_INCLUDED
