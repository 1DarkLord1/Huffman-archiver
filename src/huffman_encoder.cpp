#include "huffman_encoder.h"
#include <cassert>
using namespace huff_arch;

huffman_encoder::huffman_encoder(const std::string& _data) noexcept: htree(_data), data(_data) {}


std::vector <bool> huffman_encoder::get_code(u_char symb) const noexcept {
    std::vector <bool> code;
    tree_node node = htree.get_node(symb);
    while(htree.par(node) != node) {
        code.push_back(htree.type(node));
        node = htree.par(node);
    }
    std::reverse(code.begin(), code.end());
    return code;
}


std::vector <bool> huffman_encoder::encode() const noexcept {
    std::vector <bool> code;
    for(u_char ch: data) {
        std::vector <bool> ch_code = get_code(ch);
        code.insert(code.end(), ch_code.begin(), ch_code.end());
    }
    return code;
}


std::vector <u_short> huffman_encoder::tree_encode() const noexcept {
    return htree.tree_encode();
}
