#include <experimental/ranges/algorithm>
#include <experimental/ranges/iterator>
#include <experimental/ranges/ranges>
#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <vector>

class controlled_vector {
public:
    controlled_vector(const std::initializer_list<int>& l) : v_(l) {}
    ~controlled_vector() { std::cout << "Destroyed" << std::endl; }
    auto begin() { return v_.begin(); }
    auto begin() const { return v_.begin(); }
    auto end() { return v_.end(); }
    auto end() const { return v_.end(); }
private:
    std::vector<int> v_;
};

controlled_vector get_data()
{
    controlled_vector v{2, 3, 5, 7};
    return v;
}

int main()
{
    namespace ranges = std::experimental::ranges;
    auto it = std::begin(get_data());
    std::vector<int> u{1, 1, 1, 1};
    std::cout << *it << std::endl;    // Wrong result
    //it = ranges::begin(get_data()); // ranges::begin refuses to take rvalues
}
