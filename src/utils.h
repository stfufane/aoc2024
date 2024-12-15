#pragma once

#include <algorithm>
#include <ranges>
#include <utility>

namespace adventofcode::utils
{
constexpr inline auto enum_range = []<typename EnumType>(EnumType front, EnumType back) {
    return std::views::iota(std::to_underlying(front), std::to_underlying(back) + 1) |
           std::views::transform([](auto e) { return EnumType(e); });
};

struct Vector2
{
    int x = 0;
    int y = 0;

    Vector2() = default;
    constexpr Vector2(int in_x, int in_y) : x(in_x), y(in_y) {}

    Vector2 operator+(const Vector2& other) const { return { x + other.x, y + other.y }; }

    [[nodiscard]] std::string to_string() const { return "[" + std::to_string(x) + ", " + std::to_string(y) + "]"; }
};

} // namespace adventofcode::utils