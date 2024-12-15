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
    rows = input_data | std::views::split('\n');
    row_count = std::ranges::distance(rows);
    col_count = rows.front().size();
}

// Calculate the index of the letter in the string_view. Adding next_coord.y to include the eol character of each line.
unsigned long Day4::getFlatIndex(long row, long col) const {
    return row * row_count + col + row;
}

long Day4::solvePart1() {
    parse();
    auto check_xmas = [&](long row, long col, const std::array<utils::Vector2, 3>& positions) -> bool {
        utils::Vector2 X_coords = { static_cast<int>(col), static_cast<int>(row) };
        return std::ranges::all_of(positions | std::views::enumerate, [&](const std::tuple<long, const utils::Vector2&>& position) {
            const auto& direction = std::get<1>(position);
            const auto next_coord = X_coords + direction;
            if (next_coord.y < 0 || next_coord.y > static_cast<int>(row_count) || next_coord.x < 0 || next_coord.x > static_cast<int>(col_count)) {
                return false;
            }
            // Calculate the index of the letter in the string_view. Adding next_coord.y to include the eol character of each line.
            const auto flat_index = next_coord.y * row_count + next_coord.x + next_coord.y;
            return mas_letters[static_cast<size_t>(std::get<0>(position))] == input_data[flat_index];
        });
    };

    long nb_xmas = 0;
    for (auto [row, line]: rows | std::views::enumerate) {
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

    auto check_x_mas = [&](long row, long col) -> bool {
        const auto a_index = getFlatIndex(row, col);
        const auto first_branch = std::array<unsigned long, 3> {
            getFlatIndex(row - 1, col - 1),
            a_index,
            getFlatIndex(row + 1, col + 1),
        };
        const auto second_branch = std::array<unsigned long, 3> {
            getFlatIndex(row - 1, col + 1),
            a_index,
            getFlatIndex(row + 1, col - 1),
        };
        return (is_same(first_branch, SAM) || is_same(first_branch, MAS)) &&
               (is_same(second_branch, SAM) || is_same(second_branch, MAS));
    };

    long nb_x_mas = 0;
    for (auto [row, line]: rows | std::views::enumerate) {
        if (row == 0 || row == static_cast<long>(row_count)) { continue; }
        for (auto [col, letter]: line | std::views::enumerate) {
            if (col == 0 || col == static_cast<long>(col_count)) { continue; }
            if (letter == 'A') {
                if (check_x_mas(row, col)) {
                    ++nb_x_mas;
                }
            }
        }
    }

    return nb_x_mas;
}

} // namespace adventofcode
