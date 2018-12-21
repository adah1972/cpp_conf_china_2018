#include <range/v3/all.hpp>
#include <iostream>
#include <string>
#include <vector>

namespace range_v3 = ranges::v3;
using namespace std;

int main()
{
    vector<int> vd{1, 7, 3, 6, 5, 2, 4, 8};
    vector<string> vs{"one",  "seven", "three", "six",
                      "five", "two",   "four",  "eight"};
    auto v = range_v3::view::zip(vd, vs);
    range_v3::action::sort(v);
    for (auto i : vs) {
        cout << i << endl;
    }
}
