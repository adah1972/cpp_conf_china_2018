#include <experimental/ranges/algorithm>
#include <experimental/ranges/iterator>
#include <experimental/ranges/ranges>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <assert.h>

namespace ranges = std::experimental::ranges;

class prime_generator {
public:
    class iterator;
    friend class iterator;

    prime_generator() = default;
    iterator begin()
    { return iterator{this}; }
    iterator end() const
    { return iterator{}; }

    class iterator {
    public:
        typedef int                       difference_type;
        typedef int                       value_type;
        typedef const value_type*         pointer_type;
        typedef const value_type&         reference;
        typedef std::forward_iterator_tag iterator_category;

        iterator() : parent_(nullptr), current_(0) {}
        explicit iterator(prime_generator* this_)
            : parent_(this_)
            , current_(0)
        {
        }

        reference operator*() const
        {
            assert(parent_ != nullptr);
            return parent_->primes_.back();
        }
        pointer_type operator->() const
        {
            assert(parent_ != nullptr);
            return &parent_->primes_.back();
        }
        iterator& operator++()
        {
            assert(parent_ != nullptr &&
                   current_ < parent_->primes_.size());
            ++current_;
            if (current_ == parent_->primes_.size()) {
                int n = parent_->primes_.back() + 1;
                for (;;) {
                    if (is_prime(n)) {
                        break;
                    }
                    ++n;
                }
                parent_->primes_.push_back(n);
            }
            return *this;
        }
        iterator operator++(int)
        {
            iterator temp(*this);
            ++*this;
            return temp;
        }

        friend bool operator==(const iterator& lhs, const iterator& rhs);

    private:
        bool is_prime(int n)
        {
            return ranges::none_of(parent_->primes_,
                                   [n](int p) { return n % p == 0; });
        }
        prime_generator* parent_;
        std::size_t current_;
    };

private:
    std::vector<int> primes_{2};
};

bool operator==(const prime_generator::iterator& lhs,
                const prime_generator::iterator& rhs)
{
    return (!lhs.parent_ && !rhs.parent_) ||
           (lhs.parent_ && rhs.parent_ && lhs.current_ == rhs.current_);
}
bool operator!=(const prime_generator::iterator& lhs,
                const prime_generator::iterator& rhs)
{
    return !operator==(lhs, rhs);
}

int main()
{
    ranges::copy(prime_generator() | ranges::view::take(20),
                 ranges::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}
