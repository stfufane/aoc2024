#pragma once

#include "../DaySolver.h"

#include "../utils.h"

namespace adventofcode
{
    class Day8 final : public DaySolver {
    public:
        Day8();
        ~Day8() override = default;

        long solvePart1() override;
        long solvePart2() override;

    private:
        using Antenna = char;
        using AntennaCoords = std::vector<utils::Vector2>;
        utils::ImmutableGrid grid;

        std::map<Antenna, AntennaCoords> antennas;

        void parse();

        void get_mirrors(std::vector<utils::Vector2>& mirrors) const;
    };
}
