#include "day3.h"

namespace adventofcode
{
Day3::Day3() : DaySolver(3) {
    // Data for tests
    test_data = R"(xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5)))";
    test_data2 = R"(xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5)))";
    test_results = { 161, 48 };
}

// Non regex version
long Day3::getInstructions(std::string_view data_slice) const {
    long total = 0;

    auto parse_number = [](std::string_view str, size_t start, size_t end, long& result) -> bool {
        auto [ptr, ec] = std::from_chars(str.data() + start, str.data() + end, result);
        return ec == std::errc() && ptr == str.data() + end;
    };

    size_t pos = 0;
    while (pos < data_slice.size()) {
        auto start = data_slice.find("mul(", pos);
        if (start == std::string::npos) {
            break;
        }
        start += 4;
        auto end = data_slice.find(',', start);
        long a = 0, b = 0;
        if (!parse_number(data_slice, start, end, a)) {
            pos = start;
            continue;
        }
        start = end + 1;
        end = data_slice.find(')', start);
        if (!parse_number(data_slice, start, end, b)) {
            pos = start;
            continue;
        }
        total += a * b;
        pos = end;
    }
    return total;
}


ResultType Day3::solvePart1() {
    return getInstructions(input_data);
}

ResultType Day3::solvePart2() {
    long total = 0;
    bool is_processing = true;
    size_t pos = 0;
    while (pos < input_data.size()) {
        size_t start = pos;
        if (is_processing) {
            auto next_stop = input_data.find("don't()", start);
            if (next_stop == std::string::npos) {
                next_stop = input_data.size();
            }
            auto data_slice = input_data.substr(start, next_stop - start);
            total += getInstructions(data_slice);
            pos = next_stop + 7;
            is_processing = false;
        } else {
            auto next_start = input_data.find("do()", start);
            if (next_start == std::string::npos) {
                break;
            }
            pos = next_start + 4;
            is_processing = true;
        }
    }
    return total;
}

}
