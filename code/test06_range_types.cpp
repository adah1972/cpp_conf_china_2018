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
    TEST_CONCEPT(Range, Type); \
    TEST_CONCEPT(View, Type); \
    TEST_CONCEPT(SizedRange, Type); \
    TEST_CONCEPT(OutputRange, Type, int); \
    TEST_CONCEPT(CommonRange, Type); \
    TEST_CONCEPT(InputRange, Type); \
    TEST_CONCEPT(ForwardRange, Type); \
    TEST_CONCEPT(BidirectionalRange, Type); \
    TEST_CONCEPT(RandomAccessRange, Type); \
    TEST_CONCEPT(ContiguousRange, Type)

int main()
{
    namespace ranges = std::experimental::ranges;
    using ranges::Range;
    using ranges::View;
    using ranges::SizedRange;
    using ranges::CommonRange;
    using ranges::OutputRange;
    using ranges::InputRange;
    using ranges::ForwardRange;
    using ranges::BidirectionalRange;
    using ranges::RandomAccessRange;
    using ranges::ContiguousRange;

    int arr[] = {1, 7, 3, 6, 5, 2, 4, 8};
    const int arc[] = {1, 7, 3, 6, 5, 2, 4, 8};
    auto rng_arr_rev = arr | ranges::view::reverse;
    auto rng_arc_rev = arc | ranges::view::reverse;
    auto rng_arr_take = arr | ranges::view::take(5);
    auto rng_arr_filter =
        arr | ranges::view::filter([](int i) { return i % 2 == 0; });
    auto rng_arc_all = arc | ranges::view::all;
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

    auto ints = ranges::view::iota(0);
    auto ints_0_5 = ranges::view::iota(0, 5);
    auto ints_take = ints | ranges::view::take(5);
    TEST_CONCEPTS(decltype(ints));
    TEST_CONCEPTS(decltype(ints_0_5));
    TEST_CONCEPTS(decltype(ints_take));

#ifdef HAVE_NVWA
    auto line_reader = nvwa::istream_line_reader(cin);
    auto rng_lr_take = line_reader | ranges::view::take(5);
    TEST_CONCEPTS(decltype(line_reader));
    TEST_CONCEPTS(decltype(rng_lr_take));
#endif
}
