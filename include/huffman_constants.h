#pragma once

#include <cstddef>
#include <cstdint>

namespace huffman_constants
{
    const char BIT_ON = '1';
    const char BIT_OFF = '0';
    const std::size_t BYTE_LEN = 8;
    const char DEFAULT_CHAR = 0;
    const bool LEAF = true;
    const bool INTERNAL_NODE = false;
}