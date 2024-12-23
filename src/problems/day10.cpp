#include "day10.h"
#include <algorithm>
#include <numeric>

namespace adventofcode
{
Day10::Day10() : DaySolver(10) {
    // Data for tests
    test_data = R"(89010123
78121874
87430965
96549874
45678903
32019012
01329801
10456732)";
    test_results = { 36, 81 };
}

void Day10::parse() {
    grid = utils::ImmutableGrid(input_data);
    for (size_t idx = 0; idx < grid.grid_data.size(); ++idx) {
        if (grid[idx] == '0') {
            trailheads.emplace_back(grid.getCoords(idx));
        }
    }
}

template<bool check_all>
void Day10::dfs(const utils::Vector2& pos, std::vector<utils::Vector2>& visited, std::vector<utils::Vector2>& summits) {
    visited.push_back(pos);
    for (const auto& dir : utils::enum_range(utils::Direction::UP, utils::Direction::LEFT)) {
        const auto next = pos + utils::DirectionToVector.at(dir);
        if (!grid.isInside(next)) { continue; }
        if (grid[next] - grid[pos] == 1) {
            if constexpr (!check_all) {
                if (std::ranges::contains(visited, next)) {
                    continue;
                }
            }
            dfs<check_all>(next, visited, summits);
        }
    }
    
    if (grid[pos] == '9') {
        summits.push_back(pos);
    }
}

template<bool check_all>
long Day10::get_result() {
    parse();
    return std::transform_reduce(trailheads.begin(), trailheads.end(), 0L, std::plus(), [&](const auto& pos) {
        std::vector<utils::Vector2> visited;
        std::vector<utils::Vector2> summits;
        dfs<check_all>(pos, visited, summits);
        return summits.size();
    });
}

ResultType Day10::solvePart1() {
    return get_result<false>();
}

ResultType Day10::solvePart2() {
    return get_result<true>();
}

}
