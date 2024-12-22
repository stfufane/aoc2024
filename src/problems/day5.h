#pragma once

#include "../DaySolver.h"
#include "../utils.h"

#include <map>

namespace adventofcode
{
    class Day5 final : public DaySolver
{
public:
    Day5();
    ~Day5() override = default;

    long solvePart1() override;
    long solvePart2() override;

private:
    using Update = std::vector<int>;
    friend std::ostream& operator<<(std::ostream& stream, const Day5::Update& u);

    void parse();

    int checkUpdate(const Update& update);
    void sortUpdate(Update& update);

    std::map<int, std::vector<int>> mustBeBefore;
    std::vector<Update> updates;
};

inline std::ostream& operator<<(std::ostream& stream, const Day5::Update& u) {
    utils::print_range(u);
    return stream;
}

}
