#include "huffman_tree_node.h"
#include <cstddef>
#include <exception>

namespace huffman_archiver
{
    huffman_tree_node::huffman_tree_node(
        std::size_t freq, bool is_leaf, uint8_t byte,
        std::shared_ptr<huffman_tree_node> left,
        std::shared_ptr<huffman_tree_node> right) : _freq(freq), _is_leaf(is_leaf), _byte(byte), _left(left), _right(right) {}

    std::shared_ptr<huffman_tree_node> huffman_tree_node::get_left() const { return _left; }

    std::shared_ptr<huffman_tree_node> huffman_tree_node::get_right() const { return _right; }

    void huffman_tree_node::set_left(std::shared_ptr<huffman_tree_node> node)
    {
        _left = node;
    }

    void huffman_tree_node::set_right(std::shared_ptr<huffman_tree_node> node)
    {
        _right = node;
    }

    std::size_t huffman_tree_node::get_freq() const
    {
        return _freq;
    }

    char huffman_tree_node::get_byte() const
    {
        if (!_is_leaf)
            throw std::invalid_argument("Этот node не лист, но попытка посмотреть байт у этого node");
        return _byte;
    }

    bool huffman_tree_node::is_leaf() const
    {
        return _is_leaf;
    }

    bool huffman_tree_node_comparator::operator()(const std::shared_ptr<huffman_tree_node> lhs, const std::shared_ptr<huffman_tree_node> rhs) const
    {
        return lhs->get_freq() > rhs->get_freq();
    }
} // namespace huffman_archiver
