#pragma once

#include <climits>
#include "bin_manip.h"
#include "huffman_encoder.h"
#include "huffman_decoder.h"
#include "huffman_exception.h"

namespace huff_arch {

class huffman_archiver {
private:
    std::size_t data_size = 0, encd_data_size = 0, extra_data_size = 0;

public:
    void archive(std::ifstream& src, std::ofstream& dest) noexcept;
    void unarchive(std::ifstream& src, std::ofstream& dest) noexcept;

    std::size_t get_data_size() const noexcept;
    std::size_t get_encd_data_size() const noexcept;
    std::size_t get_extra_data_size() const noexcept;

private:
    void size_info_init(std::size_t _data_size, std::size_t _encd_data_size, std::size_t _extra_data_size) noexcept;
};

}
