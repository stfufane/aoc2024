#pragma once

#include "../DaySolver.h"

#include <vector>

namespace adventofcode
{
    class Day1 final : public DaySolver {
    public:
        Day1();
        ~Day1() override = default;

        ResultType solvePart1() override;
        ResultType solvePart2() override;
    private:

        [[nodiscard]] std::pair<std::vector<int>, std::vector<int>> getLists(bool sorted) const;
    };
}
