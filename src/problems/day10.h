#pragma once

#include "../DaySolver.h"

#include "../utils.h"

namespace adventofcode
{
    class Day10 final : public DaySolver {
    public:
        Day10();
        ~Day10() override = default;

        ResultType solvePart1() override;
        ResultType solvePart2() override;

    private:
        utils::ImmutableGrid grid;
        std::vector<utils::Vector2> trailheads;

        template<bool check_all>
        long get_result();

        template<bool check_all>
        void dfs(const utils::Vector2& pos, std::vector<utils::Vector2>& visited, std::vector<utils::Vector2>& summits);

        void parse();
    };
}
