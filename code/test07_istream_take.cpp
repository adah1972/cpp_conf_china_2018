#include <experimental/ranges/ranges>
#include <fstream>
#include <iostream>
#include <nvwa/istream_line_reader.h>

int main()
{
    namespace ranges = std::experimental::ranges;
    using std::cout;
    using std::ifstream;
    using nvwa::istream_line_reader;
    using ranges::view::take;

    cout << "This program outputs the first 10 lines of itself.\n";
    cout << "--------------------------------------------------\n";
    ifstream ifs(__FILE__);
    for (auto& line : istream_line_reader(ifs) | take(10)) {
        cout << line << '\n';
    }
}
