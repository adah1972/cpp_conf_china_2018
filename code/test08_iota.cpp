#include <experimental/ranges/ranges>
#include <algorithm>
#include <iostream>
#include <functional>
#include <iterator>
#include <numeric>
#include <vector>
#include <nvwa/functional.h>

int main()
{
    namespace ranges = std::experimental::ranges;
    using namespace ranges;
    auto square = [](int x) { return x * x; };

    {
        int sum = 0;
        for (int i = 1; i < 101; ++i) {
            sum += square(i);
        }
        std::cout << sum << std::endl;
    }

    {
        auto rng = views::iota(1, 101);
        std::vector<int> result;
        std::transform(rng.begin(), rng.end(), std::back_inserter(result),
                       square);
        int sum = std::accumulate(result.begin(), result.end(), 0);
        std::cout << sum << std::endl;
    }

    {
        int sum = nvwa::reduce(
            std::plus<int>(),
            nvwa::fmap(square, views::iota(1, 101)));
        std::cout << sum << std::endl;
    }

    {
        int sum = nvwa::reduce(
            std::plus<int>(),
            views::iota(1, 101) | views::transform(square));
        std::cout << sum << std::endl;
    }
}
