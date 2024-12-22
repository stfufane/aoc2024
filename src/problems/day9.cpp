#include "day9.h"

#include <algorithm>
#include <numeric>
#include <ranges>

namespace adventofcode
{
Day9::Day9() : DaySolver(9) {
    // Data for tests
    test_data = R"(2333133121414131402)";
    test_results = { 1928, 2858 };
}

void Day9::parse() {
    long id = 0;
    memory.reserve(input_data.size());
    for (const auto& pair: input_data | std::views::chunk(2)) {
        int used_count = pair.front() - '0';
        std::ranges::fill_n(std::back_inserter(memory), used_count, MemoryBlock {MemType::Used, id, static_cast<size_t>(used_count) });

        // There's no free memory after the last element so the pair will only have one element.
        if (pair.size() > 1) {
            int free_count = pair.back() - '0';
            std::ranges::fill_n(std::back_inserter(memory), free_count, MemoryBlock {MemType::Free, -1, static_cast<size_t>(free_count) });
        }
        ++id;
    }
}

long Day9::compute_checksum() const {
    auto indexed_memory = memory | std::views::enumerate;
    return std::transform_reduce(indexed_memory.begin(), indexed_memory.end(), 0L, std::plus<long>(), [](const auto& indexed_block) {
        const auto& [index, block] = indexed_block;
        return block.type == MemType::Free ? 0 : index * block.id;
    });
}

long Day9::solvePart1() {
    parse();
    for (auto block = memory.begin(); block != memory.end(); ++block) {
        if (block->type == MemType::Used) {
            continue;
        }
        auto search_end = memory.rend() - std::distance(memory.begin(), block);
        auto first_used_block = std::find_if(memory.rbegin(), search_end, [&](const MemoryBlock& b) { return b.type == MemType::Used; });
        if (first_used_block != search_end) {
            *block = *first_used_block;
            first_used_block->type = MemType::Free;
        }
    }
    return compute_checksum();
}

long Day9::solvePart2() {
    parse();
    for (auto block = memory.rbegin(); block != memory.rend(); ++block) {
        if (block->type == MemType::Free) {
            continue;
        }
        auto block_size = block->size;
        auto search_end = memory.begin() + std::distance(block, memory.rend());
        auto first_available_block = std::find_if(memory.begin(), search_end, [&](const MemoryBlock& b) { return b.type == MemType::Free && b.size >= block_size; });
        if (first_available_block != search_end) {
            auto free_size = first_available_block->size;
            // Update the free space size for later searches.
            if (free_size > block_size) {
                std::for_each(first_available_block + static_cast<long>(block_size), first_available_block + static_cast<long>(free_size), [&](MemoryBlock& b) { 
                    b.size = free_size - block_size; 
                });
            }
            // Copy block->size blocks in the free space.
            std::ranges::fill_n(first_available_block, static_cast<long>(block_size), *block);
            // Reset the moved blocks.
            std::ranges::fill_n(block, static_cast<long>(block_size), MemoryBlock {MemType::Free, -1, block_size });
        }
    }
    return compute_checksum();
}

}
