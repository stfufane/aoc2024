#include "day7.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <numeric>
#include <ranges>

namespace adventofcode
{
Day7::Day7() : DaySolver(7) {
    // Data for tests
    test_data = R"(
190: 10 19
3267: 81 40 27
83: 17 5
156: 15 6
7290: 6 8 6 15
161011: 16 10 13
192: 17 8 14
21037: 9 7 18 13
292: 11 6 16 20)";
    test_results = { 3749, 11387 };
}

std::vector<Day7::Equation> Day7::parse() {
    std::vector<Equation> equations;
    auto equations_split = input_data | std::views::split('\n');
    equations.reserve(static_cast<size_t>(std::ranges::distance(equations_split)));
    std::ranges::for_each(equations_split, [&](const auto equation_line) {
        std::string_view equation_str(equation_line.begin(), equation_line.end());
        auto equation_sep = equation_str.find(':');
        assert(equation_sep != std::string_view::npos);
        auto& equation = equations.emplace_back();
        std::from_chars(equation_str.data(), equation_str.data() + equation_sep, equation.expected_result);
        std::string_view operands_str(equation_line.begin() + equation_sep + 2, equation_line.end());
        std::ranges::for_each(operands_str | std::views::split(' '), [&](const auto operand) { 
            std::from_chars(operand.data(), operand.data() + operand.size(), equation.operands.emplace_back()); 
        });
    });
    return equations;
}

template<bool concat>
void Day7::Equation::get_results(std::optional<uint64_t>& result, size_t index, uint64_t current_result) const {
    // No need to go further if we reach over the result.
    if (current_result > expected_result) {
        return;
    }
    // We reached the end of the list of operands
    if (index == operands.size()) {
        if (current_result == expected_result) {
            result = current_result;
        }
        return;
    }
    get_results<concat>(result, index + 1, current_result + operands[index]);
    get_results<concat>(result, index + 1, current_result * operands[index]);
    if constexpr(concat) {
        long num_digits = static_cast<long>(std::log10(operands[index]) + 1);
        uint64_t new_result = current_result * static_cast<uint64_t>(std::pow(10, num_digits)) + operands[index];
        get_results<concat>(result, index + 1, new_result);
    }
}

template<bool concat>
bool Day7::evaluate(const Equation& equation) {
    std::optional<uint64_t> result = std::nullopt;
    equation.get_results<concat>(result, 1, equation.operands[0]);
    return result.has_value();
}

long Day7::solvePart1() {
    const auto equations = parse();
    return std::transform_reduce(equations.begin(), equations.end(), 0L, std::plus(), [&](const Equation& e) {
        return evaluate<false>(e) ? e.expected_result : 0;
    });
}

long Day7::solvePart2() {
    const auto equations = parse();
    return std::transform_reduce(equations.begin(), equations.end(), 0L, std::plus(), [&](const Equation& e) {
        return evaluate<true>(e) ? e.expected_result : 0;
    });
}

}
