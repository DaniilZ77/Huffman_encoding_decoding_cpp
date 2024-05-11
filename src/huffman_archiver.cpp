#include "huffman_tree.h"
#include "huffman_archiver.h"
#include "huffman_constants.h"
#include "bin_manip.h"
#include <queue>
#include <bitset>
#include <string>
#include <algorithm>
#include <iostream>
#include <array>
#include <map>

namespace huffman_archiver
{
    huffman_archiver::huffman_archiver(std::string text) : _bytes(std::vector<uint8_t>(text.begin(), text.end())), _tree(nullptr), _bytes_size(text.size()) {}

    std::string huffman_archiver::get_bytes()
    {
        return std::string(_bytes.begin(), _bytes.end());
    }

    std::size_t huffman_archiver::get_amount_of_bytes() const
    {
        return _bytes.size();
    }

    std::size_t huffman_archiver::get_amount_of_additional_bytes() const
    {
        return _freqs.size() * (sizeof(std::size_t) + sizeof(uint8_t)) + sizeof(_bytes_size) + sizeof(uint16_t);
    }

    std::ofstream &operator<<(std::ofstream &out, huffman_archiver &archiver)
    {
        print(out, archiver._bytes_size);
        print<uint16_t>(out, archiver._freqs.size());
        std::for_each(archiver._freqs.begin(), archiver._freqs.end(), [&](auto &freq)
                      {
            print(out, freq.first);
            print(out, freq.second); });
        print(out, archiver.get_bytes());
        return out;
    }

    std::ifstream &operator>>(std::ifstream &in, huffman_archiver &archiver)
    {
        input(in, archiver._bytes_size);
        uint16_t freqs_size = 0;
        input(in, freqs_size);
        while (freqs_size--)
        {
            uint8_t freq_key = 0;
            input(in, freq_key);
            std::size_t freq_value = 0;
            input(in, freq_value);
            archiver._freqs[freq_key] = freq_value;
        }
        archiver._bytes.resize(0);
        while (true)
        {
            uint8_t byte;
            input(in, byte);
            if (in.eof() || in.fail())
                break;
            archiver._bytes.push_back(byte);
        }
        return in;
    }

    void huffman_archiver::calc_freqs(std::map<uint8_t, std::size_t> &freqs)
    {
        for (uint8_t byte : _bytes)
            ++freqs[byte];
    }

    void huffman_archiver::archive()
    {
        if (_bytes.empty())
            return;

        std::map<uint8_t, std::size_t> freqs;
        calc_freqs(freqs);
        _freqs = freqs;

        _tree = huffman_tree::build_tree(freqs);
        _codes = _tree->get_codes();

        std::bitset<huffman_constants::BYTE_LEN> cur_byte;
        std::vector<uint8_t> bytes;
        std::size_t cur_byte_index = 0;

        for (std::size_t i = 0; i < _bytes.size(); ++i)
        {
            auto code = _codes[_bytes[i]];
            for (const char &bit : code)
            {
                if (cur_byte_index == huffman_constants::BYTE_LEN)
                {
                    bytes.push_back(cur_byte.to_ulong());
                    cur_byte.reset();
                    cur_byte_index = 0;
                }
                cur_byte.set(cur_byte_index++, bit == huffman_constants::BIT_ON);
            }
        }

        if (cur_byte_index > 0)
            bytes.push_back(cur_byte.to_ulong());
        _bytes = bytes;
    }

    void huffman_archiver::unarchive()
    {
        _tree = huffman_tree::build_tree(_freqs);
        std::vector<uint8_t> bytes;
        if (_tree == nullptr)
        {
            _bytes = {};
            return;
        }
        _tree->reset_cur();

        if (_tree->get_size() == 1)
        {
            _bytes = {};
            for (std::size_t i = 0; i < _bytes_size; ++i)
                _bytes.push_back(_tree->get_byte_of_cur().second);
            return;
        }

        for (std::size_t i = 0; i < _bytes.size(); ++i)
        {
            for (std::size_t j = 0; j < huffman_constants::BYTE_LEN; ++j)
            {
                if (_bytes[i] & (1 << j))
                    _tree->go_right();
                else
                    _tree->go_left();
                if (_tree->get_byte_of_cur().first)
                {
                    bytes.push_back(_tree->get_byte_of_cur().second);
                    _tree->reset_cur();
                }
            }
        }
        bytes.resize(_bytes_size);
        _bytes = bytes;
    }
} // namespace huffman_archiver
