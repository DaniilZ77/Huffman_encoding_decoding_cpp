#pragma once

#include <cstddef>
#include <memory>
#include <vector>

namespace huffman_archiver
{
    class huffman_tree_node
    {
    private:
        std::size_t _freq;
        bool _is_leaf;
        uint8_t _byte;

        huffman_tree_node *_left;
        huffman_tree_node *_right;

    public:
        huffman_tree_node(std::size_t freq, bool is_leaf, uint8_t byte, huffman_tree_node *left = nullptr, huffman_tree_node * = nullptr);

        std::size_t get_freq() const;
        bool is_leaf() const;
        char get_byte() const;
        huffman_tree_node *get_left() const;
        huffman_tree_node *get_right() const;

        void set_left(huffman_tree_node *node);
        void set_right(huffman_tree_node *node);
    };

    class huffman_tree_node_comparator
    {
    public:
        bool operator()(const huffman_tree_node *lhs, const huffman_tree_node *rhs) const;
    };
}