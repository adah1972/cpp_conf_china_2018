#include <experimental/ranges/algorithm>
#include <experimental/ranges/concepts>
#include <iostream>
#include <string>
#include <stdlib.h>

namespace ranges = std::experimental::ranges;
using ranges::input_iterator;

struct null_sentinel {};

template <input_iterator I>
bool operator==(I i, null_sentinel) { return *i == 0; }

template <input_iterator I>
bool operator==(null_sentinel, I i) { return *i == 0; }

template <input_iterator I>
bool operator!=(I i, null_sentinel) { return *i != 0; }

template <input_iterator I>
bool operator!=(null_sentinel, I i) { return *i != 0; }

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cout << "Please provide an argument!" << std::endl;
        exit(1);
    }
    ranges::for_each(argv[1], null_sentinel(),
                     [](char ch) { std::cout << ch; });
    std::cout << std::endl;
}
