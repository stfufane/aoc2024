#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
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
    Vector2 operator-(const Vector2& other) const { return { x - other.x, y - other.y }; }
    Vector2& operator+=(const Vector2& other) { x += other.x; y += other.y; return *this; }
    
    // For use in std::set
    bool operator<(const Vector2& other) const { return x < other.x || (x == other.x && y < other.y); }

    [[nodiscard]] std::string to_string() const { return "[" + std::to_string(x) + ", " + std::to_string(y) + "]"; }
};

inline constexpr Vector2 Vector2Up { 0, -1 };
inline constexpr Vector2 Vector2Down { 0, 1 };
inline constexpr Vector2 Vector2Left { -1, 0 };
inline constexpr Vector2 Vector2Right { 1, 0 };

/**
 * A representation of a grid-like string
    * @tparam T The type of the grid data (string or string_view depending on its mutability)
 */
template <typename T>
struct Grid {
    Grid() = default;
    explicit Grid(std::string_view input) : grid_data(input) {
        rows = input 
            | std::views::split('\n') 
            | std::views::transform([](auto&& r) { return std::string_view(r.data(), r.size()); })
            | std::ranges::to<std::vector<std::string_view>>();
        width = rows.front().size();
        height = static_cast<size_t>(std::ranges::distance(rows));
    }

    T grid_data;
    std::vector<std::string_view> rows;
    size_t width = 0;
    size_t height = 0;

    [[nodiscard]] size_t getIndex(size_t x, size_t y) const { 
        assert(x < width && y < height);
        return y * (width + 1) + x; // +1 to include the eol character
    } 
    [[nodiscard]] size_t getIndex(const Vector2& v) const { return getIndex(static_cast<size_t>(v.x), static_cast<size_t>(v.y)); }
    [[nodiscard]] Vector2 getCoords(size_t index) const {
        const auto row = index / (width + 1);
        const auto col = index % (width + 1);
        return {static_cast<int>(col), static_cast<int>(row) };
    }
    [[nodiscard]] char get(size_t x, size_t y) const { return grid_data[getIndex(x, y)]; }
    [[nodiscard]] char get(const Vector2& pos) const { return get(static_cast<size_t>(pos.x), static_cast<size_t>(pos.y)); }

    [[nodiscard]] char operator[](size_t x, size_t y) const { return get(x, y); }
    [[nodiscard]] char operator[](size_t index) const { return grid_data[index]; }
    [[nodiscard]] char operator[](const Vector2& pos) const { return get(pos); }

    [[nodiscard]] bool isInside(const Vector2& pos) const {
        return pos.x >= 0 && pos.x < static_cast<int>(width) && pos.y >= 0 && pos.y < static_cast<int>(height);
    }
};

struct ImmutableGrid : Grid<std::string_view> {
    ImmutableGrid() = default;
    explicit ImmutableGrid(std::string_view input) : Grid(input) {}
};

struct MutableGrid : Grid<std::string> {
    MutableGrid() = default;
    explicit MutableGrid(std::string_view input) : Grid(input) {}

    void set(size_t x, size_t y, char c) { grid_data[getIndex(x, y)] = c; }
    void set(const Vector2& pos, char c) { set(static_cast<size_t>(pos.x), static_cast<size_t>(pos.y), c); }
    char& operator[](size_t index) { return grid_data[index]; }
    char& operator[](const Vector2& pos) { return grid_data[getIndex(pos)]; }
    char& operator[](size_t x, size_t y) { return grid_data[getIndex(x, y)]; }
    
    using Grid<std::string>::operator[];
};


} // namespace adventofcode::utils