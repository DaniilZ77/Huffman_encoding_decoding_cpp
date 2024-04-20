#pragma once

#include "huffman_tree_node.h"
#include <unordered_map>
#include <string>
#include <memory>

namespace huffman_archiver
{
    extern char DEFAULT_CHAR;

    class huffman_tree
    {
    private:
        huffman_tree_node *_head;
        std::size_t _size;

    public:
        huffman_tree(huffman_tree_node *head, std::size_t size);
        std::unordered_map<uint8_t, std::string> get_codes();
        ~huffman_tree();
        std::size_t get_size() const;
        const huffman_tree_node *get_head() const;
        static huffman_tree *build_tree(std::vector<uint8_t> &bytes);

    private:
        void get_codes_helper(const huffman_tree_node *cur, std::unordered_map<uint8_t, std::string> &codes, std::string code);
        void clear_tree(huffman_tree_node *cur);
    };
}
