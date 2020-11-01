#pragma once

#include "huffman_tree.h"

namespace huff_arch {

class huffman_encoder {
private:
    mutable huff_tree htree;
    const std::string& data;

public:
    huffman_encoder(const std::string& _data) noexcept;

    std::vector <bool> get_code(u_char symb) const noexcept;
    std::vector <bool> encode() const noexcept;
    std::vector <u_short> tree_encode() const noexcept;
};

}
