//Collen Larsen z1930118 CSCI 340-3L
//Lab Project 2 Mixed numbers
#include <vector>
#include <algorithm>
#include <iterator>

template <typename ForwardIterator>
void mixNumbers(ForwardIterator begin, ForwardIterator end) {
    using ValueType = typename std::iterator_traits<ForwardIterator>::value_type;
    
    std::vector<std::pair<ValueType, size_t>> temp;
    size_t n = std::distance(begin, end);

    if (n <= 1) return; // No need to mix if there's one or zero elements

    // Store elements and their original indices
    size_t index = 0;
    for (auto it = begin; it != end; ++it, ++index) {
        temp.emplace_back(*it, index);
    }

    // Iterate through the elements in their original order and reposition them
    for (size_t i = 0; i < n; ++i) {
        auto it = std::find_if(temp.begin(), temp.end(), [i](const auto &p) {
            return p.second == i;
        });

        if (it != temp.end()) {
            int value = it->first;
            if (value != 0) {
                // Calculate the new index
                int old_index = std::distance(temp.begin(), it);
                int new_index = (old_index + value) % (n - 1);

                if (new_index < 0) new_index += (n - 1);

                // Remove and reinsert at the correct position
                auto element = *it;
                temp.erase(it);
                temp.insert(temp.begin() + new_index, element);
            }
        }
    }

    // Copy the reordered elements back to the original range
    for (size_t i = 0; i < n; ++i) {
        *(begin + i) = temp[i].first;
    }
}
