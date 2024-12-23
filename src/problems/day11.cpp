#include "day11.h"

#include <numeric>

namespace adventofcode
{
Day11::Day11() : DaySolver(11) {
    // Data for tests
    test_data = R"(125 17)";
    test_results = { 55312, 0 };
    // input_data = test_data;
}

void Day11::parse() {
    auto stone_numbers = input_data | std::views::split(' ');
    stones.reserve(static_cast<size_t>(std::ranges::distance(stone_numbers)));
    std::ranges::for_each(stone_numbers, [&](const auto number) {
        stones.emplace_back(nullptr, std::string(number.begin(), number.end()));
    });
}

void Day11::blink(utils::Tree<Stone>& stone, int nb_times) {
    while (nb_times > 0) {
        if (stone.data == 0) {
            stone.data = 1;
            --nb_times;
        }
        else if (auto num_digits = utils::count_digits(stone.data.value); num_digits % 2 == 0) {
            stone.left_node = std::make_unique<utils::Tree<Stone>>(&stone, stone.data.value / static_cast<long>(std::pow(10L, num_digits / 2L)));
            stone.right_node = std::make_unique<utils::Tree<Stone>>(&stone, stone.data.value % static_cast<long>(std::pow(10L, num_digits / 2L)));
            --nb_times;
            blink(*stone.left_node, nb_times);
            blink(*stone.right_node, nb_times);
            return;
        }
        else {
            stone.data *= 2024;
            --nb_times;
        }
    }
}

ResultType Day11::solvePart1() {
    parse();
    return std::transform_reduce(stones.begin(), stones.end(), 0, std::plus<>(), [&](auto& stone) {
        blink(stone, 25);
        return stone.nb_leaves();
    });
}

ResultType Day11::solvePart2() {
    parse();
    // TODO better solution
    return 0;
}

}
