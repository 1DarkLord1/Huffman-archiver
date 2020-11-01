#include "huffman.h"

using namespace huff_arch;

void huffman_archiver::size_info_init(std::size_t _data_size, std::size_t _encd_data_size,
    std::size_t _extra_data_size) noexcept {
    data_size = _data_size * sizeof(char);
    encd_data_size = (_encd_data_size + CHAR_BIT - 1) / CHAR_BIT;
    extra_data_size = _extra_data_size * sizeof(uint16_t) + sizeof(uint16_t) + sizeof(uint32_t);
}

void huffman_archiver::archive(std::ifstream& src, std::ofstream& dest) noexcept {
    if(src.peek() == EOF) {
        return;
    }
    std::string data = "";
    src >> read_unfixed_len_string(data);

    huffman_encoder huff_enc(data);
    std::vector <u_short> encd_tree = huff_enc.tree_encode();
    std::vector <bool> encd_data = huff_enc.encode();

    size_info_init(data.size(), encd_data.size(), encd_tree.size());

    dest << write_uint <u_short>(encd_tree.size()) << write_vector_uint <u_short> (encd_tree) <<
    write_uint <u_int>(encd_data.size()) << write_vector_bool(encd_data);

    src.clear();
    dest.clear();
}

void huffman_archiver::unarchive(std::ifstream& src, std::ofstream& dest) noexcept {
    if(src.peek() == EOF) {
        return;
    }
    u_short encd_tree_len;
    u_int encd_data_len;

    src >> read_uint <u_short>(encd_tree_len);

    std::vector <u_short> encd_tree(encd_tree_len);
    src >> read_vector_uint <u_short>(encd_tree);

    src >> read_uint <u_int>(encd_data_len);

    std::vector <bool> encd_data(encd_data_len);
    src >> read_vector_bool(encd_data);

    huffman_decoder huff_dec(encd_tree, encd_data);
    std::string data = huff_dec.decode();

    size_info_init(data.size(), encd_data.size(), encd_tree.size());

    dest << write_string(data);

    src.clear();
    dest.clear();
}

std::size_t huffman_archiver::get_data_size() const noexcept {
    return data_size;
}

std::size_t huffman_archiver::get_encd_data_size() const noexcept {
    return encd_data_size;
}

std::size_t huffman_archiver::get_extra_data_size() const noexcept {
    return extra_data_size;
}
