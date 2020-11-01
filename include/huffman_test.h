#pragma once

#include <fstream>
#include <ios>
#include <cassert>
#include "autotest.h"
#include "huffman_encoder.h"
#include "huffman_decoder.h"
#include "bin_manip.h"
#include "huffman.h"

class huff_test: public Test {
private:
    void get_code_test_small_balanced() noexcept;
    void get_code_test_average_chain() noexcept;
    void get_code_test_big_balanced() noexcept;

    void tree_encode_test_small() noexcept;
    void tree_encode_test_average_balanced() noexcept;

    void decode_test_small() noexcept;
    void decode_test_average_balanced() noexcept;
    void decode_test_big_chain() noexcept;

    void read_write_u_short_test_0() noexcept;
    void read_write_u_short_test_12334() noexcept;
    void read_write_u_short_test_891() noexcept;

    void read_write_vector_u_short_test_small() noexcept;
    void read_write_vector_test_u_short_test_average() noexcept;
    void read_write_vector_test_u_short_test_big() noexcept;

    void read_write_string_test_small() noexcept;
    void read_write_string_test_average() noexcept;
    void read_write_string_test_big() noexcept;

    void read_write_vector_bool_small() noexcept;
    void read_write_vector_bool_average() noexcept;
    void read_write_vector_bool_big() noexcept;

    void archive_unarchive_test_empty() noexcept;
    void archive_unarchive_test_one_type_symbol() noexcept;
    void archive_unarchive_test_small() noexcept;
    void archive_unarchive_test_average() noexcept;
    void archive_unarchive_test_big() noexcept;
    void archive_unarchive_test_big_extra_symb() noexcept;

    bool check_data(const std::string& F, const std::string& S) noexcept;

public:
    void run_all_tests() override;
};
