#include "huffman_decoder.h"

using namespace huff_arch;

huffman_decoder::huffman_decoder(const std::vector <u_short>& encd_tree,
    const std::vector <bool>& encd_data) noexcept: htree(encd_tree), data(encd_data) {}

u_char huffman_decoder::token_feed(std::vector <bool>::const_iterator& It) const noexcept {
    tree_node node = htree.root();
    while(!htree.is_terminal(node)) {
        node = (!(*It) ? htree.l_node(node): htree.r_node(node));
        It++;
    }
    It--;
    return u_char(htree.get_num(node));
}

std::string huffman_decoder::decode() const noexcept {
    std::string decd_data = "";
    for(auto It = data.begin(); It != data.end(); It++) {
        decd_data += token_feed(It);
    }
    return decd_data;
}
