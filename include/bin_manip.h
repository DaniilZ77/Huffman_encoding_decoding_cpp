#pragma once
#include <fstream>
#include <string>

namespace huffman_archiver
{
    template <class T>
    void print(std::ofstream &out, T item)
    {
        out.write(reinterpret_cast<char *>(&item), sizeof(T));
    }

    template <class T>
    T input(std::ifstream &in, T &item)
    {
        in.read(reinterpret_cast<char *>(&item), sizeof(T));
        return item;
    }

    template <>
    void print(std::ofstream &out, std::string item)
    {
        out.write(item.c_str(), item.size());
    }
}