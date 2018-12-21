#include <experimental/ranges/algorithm>
#include <experimental/ranges/iterator>
#include <iostream>

int main()
{
    namespace ranges = std::experimental::ranges;
    int a[] = {1, 7, 3, 6, 5, 2, 4, 8};
    ranges::copy(a, ranges::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    ranges::sort(a);
    ranges::copy(a, ranges::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}
