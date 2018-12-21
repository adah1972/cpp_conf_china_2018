#include <experimental/ranges/ranges>
#include <iostream>
#include <fstream>
#include <memory>
#include <nvwa/functional.h>
#include <nvwa/istream_line_reader.h>

class line_reader_t {
public:
    line_reader_t() {}  // Important
    line_reader_t(const char* filename)
        : filename_(filename)
    {
    }
    auto begin()
    {
        if (!ifs_) {
            ifs_ = std::make_shared<std::ifstream>(filename_);
            reader_ = std::make_shared<nvwa::istream_line_reader>(*ifs_);
        }
        return reader_->begin();
    }
    auto end()
    {
        return reader_->end();
    }

private:
    std::string filename_;
    std::shared_ptr<std::ifstream> ifs_;
    std::shared_ptr<nvwa::istream_line_reader> reader_;
};

int main(int argc, char* argv[])
{
    namespace ranges = std::experimental::ranges;
    using namespace ranges;
#if 1
    auto make_line_reader = [](const char* filename) {
        return line_reader_t(filename);
    };
#else
    std::ifstream tmp;
    auto make_line_reader = [&tmp](const char* filename) {
        tmp = std::ifstream(filename);
        return nvwa::istream_line_reader(tmp);
    };
#endif
    for (auto&& line : view::counted(argv + 1, argc - 1) |
                       view::transform(make_line_reader) |
                       view::join) {
        std::cout << line << std::endl;
    }
}
