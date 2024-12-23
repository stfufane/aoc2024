#pragma once

#include "../DaySolver.h"

#include "../utils.h"

namespace adventofcode
{
    class Day11 final : public DaySolver {
    public:
        Day11();
        ~Day11() override = default;

        ResultType solvePart1() override;
        ResultType solvePart2() override;

    private:
        struct Stone {
            long value = 0;

            Stone() = default;
            explicit Stone(std::string_view value_str) {
                std::from_chars(value_str.data(), value_str.data() + value_str.size(), value);
            }
            explicit Stone(long v): value(v) {}

            Stone& operator=(long new_value) {
                value = new_value;
                return *this;
            }
            Stone& operator*=(long new_value) {
                value *= new_value;
                return *this;
            }
            bool operator==(long other) const {
                return value == other;
            }
        };
        friend inline std::ostream& operator<<(std::ostream& out, const Stone& stone) {
            out << stone.value;
            return out;
        }
        
        std::vector<utils::Tree<Stone>> stones;

        void parse();

        void blink(utils::Tree<Stone>& stone, int nb_times);
        void fast_blink();
    };
}
