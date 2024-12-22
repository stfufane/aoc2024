#include "day1.h"

#include <cstddef>
#include <ranges>
#include <algorithm>
#include <numeric>

namespace adventofcode
{
Day1::Day1() : DaySolver(1) {
    // Data for tests
    test_data = R"(3   4
4   3
2   5
1   3
3   9
3   3)";
    test_results = { 11, 31 };
}

std::pair<std::vector<int>, std::vector<int>> Day1::getLists(bool sorted) const {
    std::pair<std::vector<int>, std::vector<int>> lists;
    auto data_lines = input_data | std::views::split('\n'); // Split input into lines
    std::ranges::for_each(data_lines, [&](const auto line) {
        const std::string line_str(line.begin(), line.end());
        std::istringstream iss(line_str);
        int first, second;
        iss >> first >> second;
        lists.first.push_back(first);
        lists.second.push_back(second);
    });
    if (sorted) {
        std::ranges::sort(lists.first);
        std::ranges::sort(lists.second);
    }
    return lists;
}

ResultType Day1::solvePart1() {
    const auto [first_list, second_list] = getLists(true);
    long distance = 0;
    for (size_t i = 0; i < first_list.size(); ++i) {
        distance += std::abs(first_list[i] - second_list[i]);
    }
    return distance;
}

ResultType Day1::solvePart2() {
    const auto [first_list, second_list] = getLists(false);
    return std::transform_reduce(
        first_list.begin(), first_list.end(), 0L, std::plus(),
        [&](int x) {
            return x * std::ranges::count(second_list, x);
        }
    );
}

}
