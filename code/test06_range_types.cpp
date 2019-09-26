#include <experimental/ranges/concepts>
#include <experimental/ranges/ranges>
#include <iostream>
#include <list>
#include <string>
#include <string_view>
#include <typeinfo>
#include <type_traits>
#include <vector>

#ifdef HAVE_NVWA
// Nvwa is available at <URL:https://github.com/adah1972/nvwa>
#include <nvwa/istream_line_reader.h>
#endif

using namespace std;

#define TEST_CONCEPT(Concept, Type...) \
    cout << #Concept << '<' << #Type << ">: " << Concept<Type> << endl

#define TEST_CONCEPTS(Type) \
    cout << "\n*** " << (is_const_v<Type> ? "const " : "") \
         << typeid(Type).name() << endl; \
    TEST_CONCEPT(range, Type); \
    TEST_CONCEPT(view, Type); \
    TEST_CONCEPT(sized_range, Type); \
    TEST_CONCEPT(output_range, Type, int); \
    TEST_CONCEPT(common_range, Type); \
    TEST_CONCEPT(input_range, Type); \
    TEST_CONCEPT(forward_range, Type); \
    TEST_CONCEPT(bidirectional_range, Type); \
    TEST_CONCEPT(random_access_range, Type); \
    TEST_CONCEPT(contiguous_range, Type)

int main()
{
    namespace ranges = std::experimental::ranges;
    using ranges::range;
    using ranges::view;
    using ranges::sized_range;
    using ranges::common_range;
    using ranges::output_range;
    using ranges::input_range;
    using ranges::forward_range;
    using ranges::bidirectional_range;
    using ranges::random_access_range;
    using ranges::contiguous_range;

    int arr[] = {1, 7, 3, 6, 5, 2, 4, 8};
    const int arc[] = {1, 7, 3, 6, 5, 2, 4, 8};
    auto rng_arr_rev = arr | ranges::views::reverse;
    auto rng_arc_rev = arc | ranges::views::reverse;
    auto rng_arr_take = arr | ranges::views::take(5);
    auto rng_arr_filter =
        arr | ranges::views::filter([](int i) { return i % 2 == 0; });
    auto rng_arc_all = arc | ranges::views::all;
    cout << boolalpha;
    TEST_CONCEPTS(decltype(arr));
    TEST_CONCEPTS(decltype(arc));
    TEST_CONCEPTS(vector<int>);
    TEST_CONCEPTS(const vector<int>);
    TEST_CONCEPTS(list<int>);
    TEST_CONCEPTS(const list<int>);
    TEST_CONCEPTS(string);
    TEST_CONCEPTS(string_view);
    TEST_CONCEPTS(decltype(rng_arr_rev));
    TEST_CONCEPTS(decltype(rng_arc_rev));
    TEST_CONCEPTS(decltype(rng_arr_take));
    TEST_CONCEPTS(decltype(rng_arr_filter));
    TEST_CONCEPTS(decltype(rng_arc_all));

    auto ints = ranges::views::iota(0);
    auto ints_0_5 = ranges::views::iota(0, 5);
    auto ints_take = ints | ranges::views::take(5);
    TEST_CONCEPTS(decltype(ints));
    TEST_CONCEPTS(decltype(ints_0_5));
    TEST_CONCEPTS(decltype(ints_take));

#ifdef HAVE_NVWA
    auto line_reader = nvwa::istream_line_reader(cin);
    auto rng_lr_take = line_reader | ranges::views::take(5);
    TEST_CONCEPTS(decltype(line_reader));
    TEST_CONCEPTS(decltype(rng_lr_take));
#endif
}
