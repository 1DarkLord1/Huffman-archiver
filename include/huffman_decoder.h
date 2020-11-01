#pragma once

#include "huffman_tree.h"

namespace huff_arch {

class huffman_decoder {
private:
    mutable huff_tree htree;
    const std::vector <bool>& data;

public:
    huffman_decoder(const std::vector <u_short>& encd_tree, const std::vector <bool>& encd_data) noexcept;
    std::string decode() const noexcept;

private:
    u_char token_feed(std::vector <bool>::const_iterator& It) const noexcept;
};

}
