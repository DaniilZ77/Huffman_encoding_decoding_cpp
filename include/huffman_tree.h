#pragma once

#include "huffman_tree_node.h"
#include <map>
#include <unordered_map>
#include <string>
#include <memory>
#include <utility>

namespace huffman_archiver
{
    class huffman_tree
    {
    private:
        std::shared_ptr<huffman_tree_node> _head;
        std::shared_ptr<huffman_tree_node> _cur;
        std::size_t _size;

    public:
        huffman_tree(std::shared_ptr<huffman_tree_node> head, std::size_t size);
        std::unordered_map<uint8_t, std::string> get_codes();
        std::size_t get_size() const;
        static std::shared_ptr<huffman_tree> build_tree(std::map<uint8_t, std::size_t> &freqs);
        void go_left();
        void go_right();
        std::pair<bool, uint8_t> get_byte_of_cur();
        void reset_cur();

    private:
        void get_codes_helper(const std::shared_ptr<huffman_tree_node> cur, std::unordered_map<uint8_t, std::string> &codes, std::string code);
    };
}
