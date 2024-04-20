#include "huffman_tree.h"
#include "huffman_tree_node.h"
#include <algorithm>
#include <memory>
#include <queue>

namespace huffman_archiver
{
    char DEFAULT_CHAR = '\0';

    const bool LEAF = true;
    const bool INTERNAL_NODE = false;
    huffman_tree::huffman_tree(huffman_tree_node *head, std::size_t size) : _head(head), _size(size) {}

    void huffman_tree::clear_tree(huffman_tree_node *cur)
    {
        if (cur == nullptr)
            return;
        clear_tree(cur->get_left());
        clear_tree(cur->get_right());
        delete cur;
    }

    huffman_tree::~huffman_tree()
    {
        clear_tree(_head);
    }

    void huffman_tree::get_codes_helper(const huffman_tree_node *cur, std::unordered_map<uint8_t, std::string> &codes, std::string code)
    {
        if (cur->is_leaf())
        {
            codes[cur->get_byte()] = code;
            return;
        }
        get_codes_helper(cur->get_left(), codes, code + "0");
        get_codes_helper(cur->get_right(), codes, code + "1");
    }

    std::unordered_map<uint8_t, std::string> huffman_tree::get_codes()
    {
        std::unordered_map<uint8_t, std::string> codes;
        get_codes_helper(_head, codes, std::string());
        return codes;
    }

    std::size_t huffman_tree::get_size() const
    {
        return _size;
    }

    const huffman_tree_node *huffman_tree::get_head() const
    {
        return _head;
    }

    huffman_tree *huffman_tree::build_tree(std::vector<uint8_t> &bytes)
    {
        std::unordered_map<uint8_t, std::size_t> freqs;
        for (uint8_t byte : bytes)
            ++freqs[byte];
        std::priority_queue<huffman_tree_node *, std::vector<huffman_tree_node *>, huffman_tree_node_comparator> nodes;
        for (auto &item : freqs)
            nodes.push(new huffman_tree_node(item.second, LEAF, item.first));

        while (nodes.size() > 1)
        {
            huffman_tree_node *min1 = nodes.top();
            nodes.pop();
            huffman_tree_node *min2 = nodes.top();
            nodes.pop();
            huffman_tree_node *new_node = new huffman_tree_node(min1->get_freq() + min2->get_freq(), INTERNAL_NODE, DEFAULT_CHAR, min1, min2);
            nodes.push(new_node);
        }
        return new huffman_tree(nodes.top(), 2 * freqs.size() - 1);
    }

} // namespace huffman_archiver