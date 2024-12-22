#pragma once

#include "../DaySolver.h"
#include "../utils.h"

#include <array>

namespace adventofcode
{

class Day4 final : public DaySolver {
    public:
        Day4();
        ~Day4() override = default;

        ResultType solvePart1() override;
        ResultType solvePart2() override;


    private:
        utils::ImmutableGrid grid;

        void parse();

        enum class Direction
        {
            N, NE, E, SE, S, SW, W, NW
        };

        static constexpr std::string_view SAM = "SAM";
        static constexpr std::string_view MAS = "MAS";

        static constexpr std::array<char, 3> mas_letters { 'M', 'A', 'S' };
        static constexpr std::array<utils::Vector2, 3> E_Directions {{ { 1, 0 }, { 2, 0 }, { 3, 0 } }};
        static constexpr std::array<utils::Vector2, 3> W_Directions {{ { -1, 0 }, { -2, 0 }, { -3, 0 } }};
        static constexpr std::array<utils::Vector2, 3> N_Directions {{ { 0, -1 }, { 0, -2 }, { 0, -3 } }};
        static constexpr std::array<utils::Vector2, 3> S_Directions {{ { 0, 1 }, { 0, 2 }, { 0, 3 } }};
        static constexpr std::array<utils::Vector2, 3> NE_Directions {{ { 1, -1 }, { 2, -2 }, { 3, -3 } }};
        static constexpr std::array<utils::Vector2, 3> SE_Directions {{ { 1, 1 }, { 2, 2 }, { 3, 3 } }};
        static constexpr std::array<utils::Vector2, 3> SW_Directions {{ { -1, 1 }, { -2, 2 }, { -3, 3 } }};
        static constexpr std::array<utils::Vector2, 3> NW_Directions {{ { -1, -1 }, { -2, -2 }, { -3, -3 } }};
        static constexpr std::array<utils::Vector2, 3> No_Directions {{ { 0, 0 }, { 0, 0 }, { 0, 0 } }};

        static const std::array<utils::Vector2, 3>& DirectionsVector(const Direction direction) {
            switch (direction) {
            case Direction::E:
                return E_Directions;
            case Direction::W:
                return W_Directions;
            case Direction::N:
                return N_Directions;
            case Direction::S:
                return S_Directions;
            case Direction::NE:
                return NE_Directions;
            case Direction::SE:
                return SE_Directions;
            case Direction::SW:
                return SW_Directions;
            case Direction::NW:
                return NW_Directions;
            }
            return No_Directions;
        }
};
}
