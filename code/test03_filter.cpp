#include <experimental/ranges/algorithm>
#include <experimental/ranges/iterator>
#include <experimental/ranges/ranges>
#include <iostream>

int main()
{
    namespace ranges = std::experimental::ranges;
    int a[] = {1, 7, 3, 6, 5, 2, 4, 8};
    auto r = ranges::filter_view(a, [](int i) { return i % 2 == 0; });
    ranges::copy(a, ranges::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    ranges::copy(r, ranges::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}
