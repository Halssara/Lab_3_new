#include <iostream>
#include <vector>
#include <sstream>
#include <string>

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

        cerr << "Enter color" << ": " << '\n';
        data.color = colorsvg(in, data.bin_count);
    }
    else
    {
        in >> data.number_count;
        data.numbers = input_numbers(in, data.number_count);
        in >> data.bin_count;
        data.color = colorsvg(in, data.bin_count);
    }
    return data;
}
size_t
write_data(void* items, size_t item_size, size_t item_count, void* ctx) {
    size_t data_size = item_size * item_count;

    stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
    buffer->write(reinterpret_cast<const char*>(items), data_size);

    return data_size;
}
Input download(const string& address)
{
    stringstream buffer;
    curl_global_init(CURL_GLOBAL_ALL);
    CURL *curl = curl_easy_init();
    if(curl)
    {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        if (!res)
        {
            curl_off_t cl;
            res = curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_UPLOAD_T, &cl);
            if(!res)
            {
                cerr << "Upload_size = " << cl;
            }
        }
        if(res)
        {
            cout <<  curl_easy_strerror(res);
            exit(1);
        }
    }
    return read_input(buffer, false);
}
int main (int argc, char* argv[])
{
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_size = SCREEN_WIDTH - 3 - 1;
    Input input;
    if (argc > 1)
    {
        input = download(argv[1]);
    }

    else
    {
        input = read_input (cin, true);
    }
    const auto bins = make_histogram(input);
    show_histogram_svg(bins, input.bin_count, input);
    getchar ();
    return 0;
}
