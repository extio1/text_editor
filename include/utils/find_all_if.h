#include <vector>

template <class _InputIterator, class _Predicate>
std::vector<_InputIterator> find_all_if(_InputIterator begin,
                                        _InputIterator end, _Predicate pred) {
    std::vector<_InputIterator> matches;
    while (begin != end) {
        if (pred(*begin)) matches.push_back(begin);
        ++begin;
    }

    return matches;
}