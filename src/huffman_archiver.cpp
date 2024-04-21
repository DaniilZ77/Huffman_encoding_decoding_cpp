#include "huffman_archiver.h"
#include "huffman_tree.h"
#include <queue>
#include <bitset>
#include <string>
#include <algorithm>

namespace huffman_archiver
{
    const char ON = '1';
    const char OFF = '0';
    const std::size_t BYTE_LEN = 8;

    huffman_archiver::huffman_archiver(std::string text) : _bytes(std::vector<uint8_t>(text.begin(), text.end())), _tree(nullptr), _bytes_size(text.size()) {}

    std::string huffman_archiver::get_bytes()
    {
        return std::string(_bytes.begin(), _bytes.end());
    }

    std::size_t huffman_archiver::get_amount_of_bytes() const
    {
        return _bytes.size();
    }

    std::size_t huffman_archiver::get_amount_of_codes_bytes() const
    {
        std::size_t bytes = 0;
        for (auto &code_pair : _codes)
        {
            bytes += code_pair.second.size() + 2;
        }
        return bytes;
    }

    std::ofstream &operator<<(std::ofstream &out, huffman_archiver &archiver)
    {
        out.write(reinterpret_cast<char *>(&archiver._bytes_size), sizeof(archiver._bytes_size));
        uint8_t codes_size = archiver._codes.size();
        out.write(reinterpret_cast<char *>(&codes_size), sizeof(codes_size));
        std::for_each(archiver._codes.begin(), archiver._codes.end(), [&](auto &code)
                      {
            char code_value = code.first;
            out.write(&code_value, sizeof(code_value));

            char code_size = code.second.size();
            out.write(&code_size, sizeof(code_size));
            out.write(code.second.c_str(), code_size); });

        std::string bytes_str = archiver.get_bytes();
        out.write(bytes_str.c_str(), bytes_str.size());
        return out;
    }

    std::ifstream &operator>>(std::ifstream &in, huffman_archiver &archiver)
    {
        in.read(reinterpret_cast<char *>(&archiver._bytes_size), sizeof(archiver._bytes_size));
        uint8_t codes_size;
        in.read(reinterpret_cast<char *>(&codes_size), sizeof(codes_size));
        while (codes_size--)
        {
            char code_value;
            in.read(&code_value, sizeof(code_value));

            char code_size;
            in.read(&code_size, sizeof(code_size));

            std::string code_str(code_size, DEFAULT_CHAR);
            in.read(&code_str[0], code_size);
            archiver._codes[code_value] = code_str;
        }
        archiver._bytes.resize(0);
        while (true)
        {
            char byte;
            in.read(&byte, sizeof(byte));
            if (in.eof() || in.fail())
                break;
            archiver._bytes.push_back(byte);
        }
        return in;
    }

    void huffman_archiver::archive()
    {
        _tree = huffman_tree::build_tree(_bytes);
        _codes = _tree->get_codes();
        std::bitset<BYTE_LEN> cur_byte;
        std::vector<uint8_t> bytes;
        std::size_t cur_byte_index = 0;
        for (std::size_t i = 0; i < _bytes.size(); ++i)
        {
            auto code = _codes[_bytes[i]];
            for (std::size_t j = 0; j < code.size(); ++j)
            {
                if (cur_byte_index % BYTE_LEN == 0 && cur_byte_index > 0)
                {
                    bytes.push_back(static_cast<uint8_t>(cur_byte.to_ulong()));
                    cur_byte_index = 0;
                    cur_byte.reset();
                }
                cur_byte.set(cur_byte_index++, code[j] == ON);
            }
        }
        if (cur_byte_index > 0)
            bytes.push_back(static_cast<uint8_t>(cur_byte.to_ulong()));
        delete _tree;
        _bytes = bytes;
    }

    void huffman_archiver::unarchive()
    {
        std::unordered_map<std::string, uint8_t> codes;
        std::vector<uint8_t> bytes;
        for (auto &code_pair : _codes)
            codes[code_pair.second] = code_pair.first;

        std::string code;
        for (std::size_t i = 0; i < _bytes.size(); ++i)
        {
            for (std::size_t j = 0; j < BYTE_LEN; ++j)
            {
                if (_bytes[i] & (1 << j))
                    code.push_back(ON);
                else
                    code.push_back(OFF);

                if (codes.find(code) != codes.end())
                {
                    bytes.push_back(codes[code]);
                    code.clear();
                }
            }
        }
        bytes.resize(_bytes_size);
        _bytes = bytes;
    }
} // namespace huffman_archiver
