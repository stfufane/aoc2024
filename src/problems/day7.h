#pragma once

#include "../DaySolver.h"

namespace adventofcode
{
    class Day7 final : public DaySolver {
    public:
        Day7();
        ~Day7() override = default;

        ResultType solvePart1() override;
        ResultType solvePart2() override;

    private:
        struct Equation {
            Equation() { 
                operands.reserve(12);
            }
            uint64_t expected_result = 0;
            std::vector<uint64_t> operands;

            template<bool concat>
            void get_results(std::optional<uint64_t>& result, size_t index, uint64_t current_result) const;
        };

        std::vector<Equation> parse();
        
        template<bool concat>
        bool evaluate(const Equation& equation);

        template<bool concat>
        long get_result();

    };
}
