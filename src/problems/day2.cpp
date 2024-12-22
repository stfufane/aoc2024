#include "day2.h"

#include <algorithm>
#include <cmath>
#include <ranges>

namespace adventofcode
{
Day2::Day2() : DaySolver(2) {
    // Data for tests
    test_data = R"(7 6 4 2 1
1 2 7 8 9
9 7 6 2 1
1 3 2 4 5
8 6 4 4 1
1 3 6 7 9)";
    test_results = { 2, 4 };
}

std::vector<std::vector<int>> Day2::getReports() const {
    std::vector<std::vector<int>> reports;
    auto data_lines = input_data | std::views::split('\n'); // Split input into lines
    size_t line_count = std::ranges::distance(data_lines);
    reports.reserve(line_count);
    std::ranges::for_each(data_lines, [&](const auto line) {
        auto& report = reports.emplace_back();
        std::string_view line_str(line.begin(), line.end());
        auto report_numbers = line_str | std::views::split(' ');
        std::ranges::for_each(report_numbers, [&](const auto number) { std::from_chars(number.data(), number.data() + number.size(), report.emplace_back()); });
    });
    return reports;
}

template <typename Range>
    requires std::is_integral_v<std::ranges::range_value_t<Range>>
bool Day2::isSafeReport(Range report) {
    bool increasing = std::signbit(report.front() - *std::next(report.begin()));
    for (const auto pairs : report | std::views::slide(2)) {
        auto sign = std::signbit(pairs.front() - *std::next(pairs.begin()));
        auto diff = std::abs(pairs.front() - *std::next(pairs.begin()));
        if (sign != increasing || diff < 1 || diff > 3) {
            return false;
        }
    }
    return true;
}

// https://github.com/admo/AoC/blob/main/2024/day02_02.cpp
bool Day2::recheckUnsafeReport(const std::vector<int>& report) {
    for (size_t i = 0; i < report.size(); ++i) {
        auto filtered_report = report 
            | std::views::enumerate 
            | std::views::filter([i](const auto& elt) { return std::get<0>(elt) != static_cast<int>(i); }) 
            | std::views::values | std::views::common;

        if (isSafeReport(filtered_report)) {
            return true;
        }
    }

    return false;
}

ResultType Day2::solvePart1() {
    auto reports = getReports();
    return std::ranges::count_if(reports, [](const auto& report) { return isSafeReport(report); });
}

ResultType Day2::solvePart2() {
    long safe_reports = 0;
    auto reports = getReports();
    for (const auto& report : reports) {
        if (isSafeReport(report)) {
            safe_reports++;
        } else {
            if (recheckUnsafeReport(report)) {
                safe_reports++;
            }
        }
    }
    return safe_reports;
}

} // namespace adventofcode
