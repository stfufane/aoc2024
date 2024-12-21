#include "day4.h"

#include "../utils.h"
#include <ranges>

namespace adventofcode
{
Day4::Day4() : DaySolver(4) {
    // Data for tests
    test_data = R"(MMMSXXMASM
MSAMXMSMSA
AMXSXMAAMM
MSAMASMSMX
XMASAMXAMM
XXAMMXXAMA
SMSMSASXSS
SAXAMASAAA
MAMMMXMMMM
MXMXAXMASX)";
    test_results = { 18, 9 };
}

void Day4::parse() {
    grid = utils::ImmutableGrid(input_data);
}

long Day4::solvePart1() {
    parse();
    auto check_xmas = [&](long row, long col, const std::array<utils::Vector2, 3>& positions) -> bool {
        utils::Vector2 X_coords = { static_cast<int>(col), static_cast<int>(row) };
        return std::ranges::all_of(positions | std::views::enumerate, [&](const std::tuple<long, const utils::Vector2&>& position) {
            const auto& direction = std::get<1>(position);
            const auto next_coord = X_coords + direction;
            if (next_coord.y < 0 || next_coord.y > static_cast<int>(grid.height) || next_coord.x < 0 || next_coord.x > static_cast<int>(grid.width)) {
                return false;
            }
            return mas_letters[static_cast<size_t>(std::get<0>(position))] == grid[next_coord];
        });
    };

    long nb_xmas = 0;
    for (auto [row, line]: grid.rows | std::views::enumerate) {
        for (auto [col, letter]: line | std::views::enumerate) {
            if (letter == 'X') {
                for (const auto direction: utils::enum_range(Day4::Direction::N, Day4::Direction::NW)) {
                    const auto& directions = DirectionsVector(direction);
                    if (check_xmas(row, col, directions)) {
                        ++nb_xmas;
                    }
                }
            }
        }
    }

    return nb_xmas;
}

long Day4::solvePart2() {
    parse();

    auto is_same = [&](const std::array<unsigned long, 3>& letter_indices, std::string_view word)-> bool {
        return std::ranges::equal(
            letter_indices | std::views::transform([&](unsigned long index) { return input_data[index]; }),
            word);
    };

    auto check_x_mas = [&](size_t y, size_t x) -> bool {
        const auto a_index = grid.getIndex(x, y);
        const auto first_branch = std::array<unsigned long, 3> {
            grid.getIndex(x - 1, y - 1),
            a_index,
            grid.getIndex(x + 1, y + 1),
        };
        const auto second_branch = std::array<unsigned long, 3> {
            grid.getIndex(x + 1, y - 1),
            a_index,
            grid.getIndex(x - 1, y + 1),
        };
        return (is_same(first_branch, SAM) || is_same(first_branch, MAS)) &&
               (is_same(second_branch, SAM) || is_same(second_branch, MAS));
    };

    long nb_x_mas = 0;
    for (auto [row, line]: grid.rows | std::views::enumerate) {
        if (row == 0 || row == static_cast<long>(grid.height)) { continue; }
        for (auto [col, letter]: line | std::views::enumerate) {
            if (col == 0 || col == static_cast<long>(grid.width)) { continue; }
            if (letter == 'A') {
                if (check_x_mas(static_cast<size_t>(row), static_cast<size_t>(col))) {
                    ++nb_x_mas;
                }
            }
        }
    }

    return nb_x_mas;
}

} // namespace adventofcode
