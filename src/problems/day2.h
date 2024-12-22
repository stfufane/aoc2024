#pragma once

#include "../DaySolver.h"
#include <vector>

namespace adventofcode
{
class Day2 final : public DaySolver
{
public:
    Day2();
    ~Day2() override = default;

    ResultType solvePart1() override;
    ResultType solvePart2() override;

private:
    [[nodiscard]] std::vector<std::vector<int>> getReports() const;
    [[nodiscard]] static bool recheckUnsafeReport(const std::vector<int>& report);

    template <typename Range>
        requires std::is_integral_v<std::ranges::range_value_t<Range>>
    static bool isSafeReport(Range report);
};
} // namespace adventofcode
