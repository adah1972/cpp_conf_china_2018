#include <experimental/ranges/algorithm>
#include <experimental/ranges/iterator>
#include <experimental/ranges/ranges>
#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    namespace ranges = std::experimental::ranges;
    int a[] = {1, 7, 3, 6, 5, 2, 4, 8};
    auto r = a
        | ranges::view::filter([](int i) { return i % 2 == 0; })
        | ranges::view::reverse;
    ranges::copy(a, ranges::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    ranges::copy(r, ranges::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}

