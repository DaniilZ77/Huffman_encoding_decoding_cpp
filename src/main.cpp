#include <iostream>
#include <exception>
#include <fstream>
#include <string>
#include "huffman_archiver.h"
#include <cstring>

typedef huffman_archiver::huffman_archiver ha;

int main(int argc, char *argv[])
{
    if (argc != 6)
        throw std::invalid_argument("Не хватает аргументов");

    if (std::strcmp(argv[1], "-c") == 0 || std::strcmp(argv[2], "-c") == 0)
    {
        std::ifstream in(argv[3]);
        std::string text;
        getline(in, text);
        in.close();

        ha ha(text);

        std::cout << ha.get_amount_of_bytes() << std::endl;

        ha.archive();

        std::cout << ha.get_amount_of_bytes() << std::endl;
        std::cout << ha.get_amount_of_codes_bytes() << std::endl;

        std::ofstream out(argv[5]);
        out << ha;
    }
    else
    {
        ha ha;
        std::ifstream in(argv[3]);
        in >> ha;
        in.close();

        std::cout << ha.get_amount_of_bytes() << std::endl;

        ha.unarchive();

        std::cout << ha.get_amount_of_bytes() << std::endl;
        std::cout << ha.get_amount_of_codes_bytes() << std::endl;

        std::ofstream out(argv[5]);
        out << ha.get_bytes() + "\n";
    }
}