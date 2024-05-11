#include "huffman_tree.h"
#include "huffman_tree_node.h"
#include <algorithm>
#include <memory>
#include <queue>
#include <utility>
#include <map>
#include "huffman_constants.h"

namespace huffman_archiver
{
    huffman_tree::huffman_tree(std::shared_ptr<huffman_tree_node> head, std::size_t size) : _head(head), _cur(head), _size(size) {}

    void huffman_tree::get_codes_helper(const std::shared_ptr<huffman_tree_node> cur, std::unordered_map<uint8_t, std::string> &codes, std::string code)
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
        if (_size > 1)
            get_codes_helper(_head, codes, std::string());
        else
            codes[_head->get_byte()] = "0";
        return codes;
    }

    std::size_t huffman_tree::get_size() const
    {
        return _size;
    }

    std::shared_ptr<huffman_tree> huffman_tree::build_tree(std::map<uint8_t, std::size_t> &freqs)
    {
        std::priority_queue<std::shared_ptr<huffman_tree_node>, std::vector<std::shared_ptr<huffman_tree_node>>, huffman_tree_node_comparator> nodes;
        for (auto &item : freqs)
            nodes.push(std::make_shared<huffman_tree_node>(item.second, huffman_constants::LEAF, item.first));

        while (nodes.size() > 1)
        {
            std::shared_ptr<huffman_tree_node> min1 = nodes.top();
            nodes.pop();
            std::shared_ptr<huffman_tree_node> min2 = nodes.top();
            nodes.pop();
            std::shared_ptr<huffman_tree_node> new_node = std::make_shared<huffman_tree_node>(min1->get_freq() + min2->get_freq(), huffman_constants::INTERNAL_NODE, huffman_constants::DEFAULT_CHAR, min1, min2);
            nodes.push(new_node);
        }
        return nodes.empty() ? nullptr : std::make_shared<huffman_tree>(nodes.top(), 2 * freqs.size() - 1);
    }

    void huffman_tree::go_left()
    {
        if (_cur == nullptr)
            return;
        _cur = _cur->get_left();
    }

    void huffman_tree::go_right()
    {
        if (_cur == nullptr)
            return;
        _cur = _cur->get_right();
    }

    std::pair<bool, uint8_t> huffman_tree::get_byte_of_cur()
    {
        if (_cur == nullptr || !_cur->is_leaf())
            return {false, huffman_constants::DEFAULT_CHAR};
        return {true, _cur->get_byte()};
    }

    void huffman_tree::reset_cur()
    {
        _cur = _head;
    }

} // namespace huffman_archiver