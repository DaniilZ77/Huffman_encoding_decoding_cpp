#pragma once

#include "huffman_tree.h"
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <map>
#include <memory>

namespace huffman_archiver
{
    class huffman_archiver
    {
    private:
        std::shared_ptr<huffman_tree> _tree;
        std::vector<uint8_t> _bytes;
        std::size_t _bytes_size;
        std::unordered_map<uint8_t, std::string> _codes;
        std::map<uint8_t, std::size_t> _freqs;

    public:
        huffman_archiver(std::string text = std::string());
        friend std::ofstream &operator<<(std::ofstream &out, huffman_archiver &archiver);
        friend std::ifstream &operator>>(std::ifstream &in, huffman_archiver &archiver);
        std::size_t get_amount_of_bytes() const;
        std::size_t get_amount_of_additional_bytes() const;
        std::string get_bytes();
        void archive();
        void unarchive();

    private:
        void calc_freqs(std::map<uint8_t, std::size_t> &freqs);
    };
}