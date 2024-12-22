#include "day8.h"

#include <cassert>
#include <ranges>
#include <unordered_set>
#include <vector>

namespace adventofcode
{
Day8::Day8() : DaySolver(8) {
    // Data for tests
    test_data = R"(............
........0...
.....0......
.......0....
....0.......
......A.....
............
............
........A...
.........A..
............
............)";
    test_results = { 14, 34 };
}

void Day8::parse() {
    grid = utils::ImmutableGrid(input_data);
    for (size_t i = 0; i < input_data.size(); ++i) {
        auto letter = input_data[i];
        if (letter == '.' || letter == '\n') { continue; }
        if (!antennas.contains(letter)) {
            antennas[letter] = std::vector<utils::Vector2>();
        }
        antennas[letter].push_back(grid.getCoords(i));
    }
}

void Day8::get_mirrors(std::vector<utils::Vector2>& mirrors) const {
    assert(mirrors.size() > 1);
    const auto mirror = mirrors[mirrors.size() - 2].mirror(mirrors.back());
    if (grid.isInside(mirror)) {
        mirrors.push_back(mirror);
        get_mirrors(mirrors);
    }
}

ResultType Day8::solvePart1() {
    parse();
    std::unordered_set<size_t> antinodes;
    for (const auto& [antenna, coords]: antennas) {
        // Make a combination of all coordinates couples for an antenna type and find their opposite coordinates
        for (const auto& couple: std::views::cartesian_product(coords, coords)) {
            const auto& [antenna1, antenna2] = couple;
            if (antenna1 == antenna2) { continue; }
            if (const auto mirror = antenna1.mirror(antenna2); grid.isInside(mirror)) {
                antinodes.insert(grid.getIndex(mirror));
            }
        }
    }
    return static_cast<long>(antinodes.size());
}

ResultType Day8::solvePart2() {
    parse();
    std::unordered_set<utils::Vector2, utils::Vector2Hash> antinodes;

    for (const auto& [antenna, coords]: antennas) {
        // Make a combination of all coordinates couples for an antenna type and find their opposite coordinates
        for (const auto& couple: std::views::cartesian_product(coords, coords)) {
            const auto& [antenna1, antenna2] = couple;
            if (antenna1 == antenna2) { continue; }
            std::vector<utils::Vector2> mirrors { antenna1, antenna2 };
            get_mirrors(mirrors);
            antinodes.insert(mirrors.begin(), mirrors.end());
        }
    }
    return static_cast<long>(antinodes.size());
}

}
