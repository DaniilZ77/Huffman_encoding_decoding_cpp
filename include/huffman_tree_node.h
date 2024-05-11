#pragma once

#include <cstddef>
#include <memory>
#include <vector>
#include <memory>

namespace huffman_archiver
{
    class huffman_tree_node
    {
    private:
        std::size_t _freq;
        bool _is_leaf;
        uint8_t _byte;

        std::shared_ptr<huffman_tree_node> _left;
        std::shared_ptr<huffman_tree_node> _right;

    public:
        huffman_tree_node(std::size_t freq, bool is_leaf, uint8_t byte, std::shared_ptr<huffman_tree_node> left = nullptr, std::shared_ptr<huffman_tree_node> right = nullptr);

        std::size_t get_freq() const;
        bool is_leaf() const;
        char get_byte() const;
        std::shared_ptr<huffman_tree_node> get_left() const;
        std::shared_ptr<huffman_tree_node> get_right() const;

        void set_left(std::shared_ptr<huffman_tree_node> node);
        void set_right(std::shared_ptr<huffman_tree_node> node);
    };

    class huffman_tree_node_comparator
    {
    public:
        bool operator()(const std::shared_ptr<huffman_tree_node> lhs, const std::shared_ptr<huffman_tree_node> rhs) const;
    };
}