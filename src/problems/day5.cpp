#include "day5.h"

#include <cassert>
#include <numeric>
#include <ranges>

namespace adventofcode
{
Day5::Day5() : DaySolver(5) {
    // Data for tests
    test_data = R"(47|53
97|13
97|61
97|47
75|29
61|13
75|53
29|13
97|29
53|29
61|53
97|53
61|29
47|13
75|47
97|75
47|61
75|61
47|29
75|13
53|13

75,47,61,53,29
97,61,53,29,13
75,29,13
75,97,47,61,53
61,13,29
97,13,75,29,47)";
    test_results = { 143, 123 };
}

void Day5::parse() {
    const auto split_pos = input_data.find("\n\n");
    assert(split_pos != std::string_view::npos);

    auto rules_str = std::string_view { input_data.substr(0, split_pos) };
    auto updates_str = std::string_view { input_data.substr(split_pos + 2) };

    auto rules_split = rules_str | std::views::split('\n');
    std::ranges::for_each(rules_split, [&](const auto rule_line) {
        std::string_view rule_str(rule_line.begin(), rule_line.end());
        auto rule_sep = rule_str.find('|');
        assert(rule_sep != std::string_view::npos);
        int key;
        std::from_chars(rule_str.data(), rule_str.data() + rule_sep, key);
        if (!mustBeBefore.contains(key)) {
            mustBeBefore[key] = std::vector<int>();
        }
        std::from_chars(rule_str.data() + rule_sep + 1, rule_str.data() + rule_str.size(), mustBeBefore[key].emplace_back());
    });

    auto updates_split = updates_str | std::views::split('\n');
    auto nb_updates = std::ranges::distance(updates_split);
    updates.reserve(static_cast<size_t>(nb_updates));
    std::ranges::for_each(updates_split, [&](const auto update_line) {
        std::string_view update_str(update_line.begin(), update_line.end());
        auto& update = updates.emplace_back();
        for (const auto& page : update_str | std::views::split(',')) {
            std::from_chars(page.data(), page.data() + page.size(), update.emplace_back());
        }
    });
}

int Day5::checkUpdate(const Update& update) {
    if (std::ranges::all_of(update | std::views::reverse | std::ranges::views::enumerate, [&](const std::tuple<long, const int&> page) {
        const auto& [idx, page_nb] = page;
        return std::ranges::none_of(update | std::views::reverse | std::views::drop(idx), [&](const int& remaining_page) {
            return std::ranges::find(mustBeBefore[page_nb], remaining_page) != mustBeBefore[page_nb].end();
        });
    })) {
        const auto middle_idx = update.size() / 2;
        return update[middle_idx];
    }
    return 0;
}

void Day5::sortUpdate(Update& update) {
    bool swapped = true;
    while (swapped) {
        swapped = false;
        for (size_t i = 0; i < update.size() - 1; ++i) {
            if (std::ranges::find(mustBeBefore[update[i + 1]], update[i]) != mustBeBefore[update[i + 1]].end()) {
                std::swap(update[i], update[i + 1]);
                swapped = true;
            }
        }
    }
}

ResultType Day5::solvePart1() {
    parse();
    return std::transform_reduce(updates.begin(), updates.end(), 0, std::plus(), [&](const auto& update) {
        return checkUpdate(update);
    });
}

ResultType Day5::solvePart2() { 
    parse();
    return std::transform_reduce(updates.begin(), updates.end(), 0, std::plus(), [&](auto& update) {
        if (checkUpdate(update) == 0) {
            sortUpdate(update);
            const auto middle_idx = update.size() / 2;
            return update[middle_idx];
        }
        return 0;
    });
}

} // namespace adventofcode
