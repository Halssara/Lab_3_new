#include "histogram.h"
#include <vector>
#include <cassert>
#include <iostream>
#include <sstream>
using namespace std;
void test_positive()

{

double min = 0;

double max = 0;

find_minmax({1, 2, 3}, min, max);

assert(min == 1);

assert(max == 3);

}

void test_negative()

{

double min = 0;

double max = 0;

find_minmax({-1, -2, -3}, min, max);

assert(min == -3);

assert(max == -1);

}

void test_equally()

{

double min = 0;

double max = 0;

find_minmax({1, 1, 1}, min, max);

assert(min == 1);

assert(max == 1);

}

void test_alone()

{

double min = 0;

double max = 0;

find_minmax({1}, min, max);

assert(min == 1);

assert(max == 1);

}


void test_color()

{

vector <string> colors (3);
string col0 = "000000";
string col1 = "111111";
string col2 = "222222";
stringstream input("000000 111111 222222");

color_add(3, colors, input);
assert(colors[0] == "000000");
assert(colors[1] == "111111");
assert(colors[2] == "222222");
}



int main()

{
test_color();
test_positive();

test_negative();

test_equally();

test_alone();


}
