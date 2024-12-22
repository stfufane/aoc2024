#pragma once

#include "../DaySolver.h"

namespace adventofcode
{
    class Day9 final : public DaySolver {
    public:
        Day9();
        ~Day9() override = default;

        ResultType solvePart1() override;
        ResultType solvePart2() override;

    private:
        void parse();

        long compute_checksum() const;

        enum class MemType {
            Free,
            Used,
        };
        struct MemoryBlock {
            MemType type = MemType::Free;
            long id = 0;
            size_t size = 0;
        };
        friend inline std::ostream& operator<<(std::ostream& stream, const MemoryBlock& m);
        using Memory = std::vector<MemoryBlock>;

        Memory memory;
    };

    inline std::ostream& operator<<(std::ostream& stream, const Day9::MemoryBlock& m) {
        if (m.type == Day9::MemType::Free) {
            stream << ".";
        } else {
            // stream << "[" << m.id << "]";
            stream << m.id;
        }
        return stream;
    }

}
