#include "day6.h"

#include <unordered_set>

namespace adventofcode
{

Day6::Day6() : DaySolver(6) {
    // Data for tests
    test_data = R"(....#.....
.........#
..........
..#.......
.......#..
..........
.#..^.....
........#.
#.........
......#...)";

    test_results = { 41, 6 };
    // input_data = test_data;
}

void Day6::parse() {
    grid = utils::MutableGrid(input_data);
}

std::optional<Day6::Step> Day6::move(const Step& step) const {
    auto step_coord = grid.getCoords(step.index);
    auto next_coord = step_coord + utils::DirectionToVector.at(step.direction);
    if (!grid.isInside(next_coord)) {
        return std::nullopt;
    }
    auto next_step = step;
    while (grid[next_coord] == OBSTACLE) {
        next_step.direction = utils::getNext(next_step.direction);
        next_coord = step_coord + utils::DirectionToVector.at(next_step.direction);
    }
    next_step.index = grid.getIndex(next_coord);
    return next_step;
}

template <bool check_loop>
Day6::GuardWalk Day6::guard_walk(const Step& starting_step) const {
    std::unordered_set<Step, StepHash> visited;
    auto current_step = visited.insert(starting_step).first;
    while (true) {
        auto next_step = move(*current_step);
        if (!next_step) {
            break;
        }
        auto inserted = visited.insert(*next_step);
        if constexpr (check_loop) {
            if (!inserted.second) {
                return { visited, true };
            }
        }
        current_step = inserted.first;
    }
    return { visited, !check_loop }; // if check_loop is true and we're here, it's not a loop.
}

ResultType Day6::solvePart1() {
    parse();
    auto guard_position = grid.grid_data.find_first_of(GUARD);
    const auto walk = guard_walk<false>(Step { guard_position, utils::Direction::UP });
    auto indexes = walk.steps | std::views::transform([](const Step& step) { return step.index; });
    std::unordered_set<size_t> unique_indexes(indexes.begin(), indexes.end());
    return static_cast<long>(unique_indexes.size());
}

ResultType Day6::solvePart2() {
    parse();
    auto guard_position = grid.grid_data.find_first_of(GUARD);
    size_t nb_obstacles = 0;

    const auto walk = guard_walk<false>(Step { guard_position, utils::Direction::UP });
    auto indexes = walk.steps | std::views::transform([](const Step& step) { return step.index; });
    std::unordered_set<size_t> unique_indexes(indexes.begin(), indexes.end());

    for (auto idx: unique_indexes) {
        if (grid.grid_data[idx] == GUARD) {
            continue;
        }
        grid[idx] = OBSTACLE;
        if (guard_walk<true>(Step { guard_position, utils::Direction::UP }).is_loop) {
            ++nb_obstacles;
        }
        grid[idx] = GROUND;
    }
    
    return static_cast<long>(nb_obstacles);
}

}
