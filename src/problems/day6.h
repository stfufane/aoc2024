#pragma once

#include "../DaySolver.h"

#include "../utils.h"
#include <unordered_set>
#include <utility>

namespace adventofcode
{
    class Day6 final : public DaySolver {
    public:
        Day6();
        ~Day6() override = default;

        long solvePart1() override;
        long solvePart2() override;
        

    private:
        utils::MutableGrid grid;
        enum class Direction { UP, RIGHT, DOWN, LEFT };

        static const std::map<Direction, utils::Vector2> DirectionToVector;

        // To check if we're in a loop
        struct Step {
            Step() = default;
            Step(size_t i, Direction dir) : index(i), direction(dir) {}
            
            size_t index = 0;
            Direction direction = Direction::UP;

            bool operator==(const Step& other) const {
                return index == other.index && direction == other.direction;
            }
        };
        friend std::ostream& operator<<(std::ostream& stream, const Day6::Step& s);

        struct StepHash {
            std::size_t operator()(const Step& step) const noexcept {
                std::size_t h1 = std::hash<size_t>{}(step.index);
                std::size_t h2 = std::hash<int>{}(static_cast<int>(step.direction));
                return h1 ^ (h2 * 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
            }
        };

        struct GuardWalk {
            std::unordered_set<Step, StepHash> steps;
            bool is_loop = false;
        };

        template <bool check_loop>
        GuardWalk guard_walk(const Step& starting_step) const;

        std::optional<Step> move(const Step& step) const;

        void parse();
        
        inline Direction getNext(Direction current) const {
            return static_cast<Direction>((std::to_underlying(current) + 1) % 4);
        }

        static constexpr char OBSTACLE = '#';
        static constexpr char GROUND   = '.';
        static constexpr char GUARD    = '^';
    };

    inline std::ostream& operator<<(std::ostream& stream, const Day6::Step& s) {
        std::cout << "Step: " << s.index << " Direction: " << static_cast<int>(s.direction) << "\n";
        return stream;
    }
}
