#pragma once

#include <algorithm>
#include <iostream>
#include <map>
#include <ranges>
#include <string_view>
#include <utility>
#include <vector>

namespace adventofcode::utils
{
constexpr inline auto enum_range = []<typename EnumType>(EnumType front, EnumType back) {
    return std::views::iota(std::to_underlying(front), std::to_underlying(back) + 1) |
           std::views::transform([](auto e) { return EnumType(e); });
};

// Define a concept to check if a type is a range
template <typename T>
concept Range = requires(T t) {
    std::ranges::begin(t);
    std::ranges::end(t);
};

template <Range R>
void print_range(const R& r) {
    std::ranges::for_each(r, [](const auto& v) {
        std::cout << v << ", ";
    });
    std::cout << '\n';
}

template <typename K, Range V>
void print_map(const std::map<K, V>& inMap) {
    for (const auto& [k, v]: inMap) {
        std::cout << "Key [" << k << "] : \n";
        print_range(v);
    }
}

struct Vector2
{
    int x = 0;
    int y = 0;

    Vector2() = default;
    constexpr Vector2(int in_x, int in_y) : x(in_x), y(in_y) {}

    Vector2 operator+(const Vector2& other) const { return { x + other.x, y + other.y }; }

    [[nodiscard]] std::string to_string() const { return "[" + std::to_string(x) + ", " + std::to_string(y) + "]"; }
};

struct Grid {
    Grid() = default;
    Grid(std::string_view input) {
        grid_data = input;
        rows = input 
            | std::views::split('\n') 
            | std::views::transform([](auto&& r) { return std::string_view(r.data(), r.size()); })
            | std::ranges::to<std::vector<std::string_view>>();
        width = rows.front().size();
        height = static_cast<size_t>(std::ranges::distance(rows));
    }

    std::string_view grid_data;
    std::vector<std::string_view> rows;
    size_t width = 0;
    size_t height = 0;

    size_t getIndex(size_t x, size_t y) const { return y * (width + 1) + x; } // +1 to include the eol character
    char get(size_t x, size_t y) const { return grid_data[getIndex(x, y)]; }
    char get(const Vector2& pos) const { return get(static_cast<size_t>(pos.x), static_cast<size_t>(pos.y)); }
};


} // namespace adventofcode::utils