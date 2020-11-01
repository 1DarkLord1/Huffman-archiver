#include "huffman_test.h"

using namespace huff_arch;

void huff_test::get_code_test_small_balanced() noexcept {
    std::string data = "a bc aaaa bbbb cc";
    huffman_encoder huff_enc(data);
    DO_CHECK((huff_enc.get_code('a') == std::vector<bool>{1, 0}));
    DO_CHECK((huff_enc.get_code('b') == std::vector<bool>{1, 1}));
    DO_CHECK((huff_enc.get_code('c') == std::vector<bool>{0, 0}));
    DO_CHECK((huff_enc.get_code(' ') == std::vector<bool>{0, 1}));
}

void huff_test::get_code_test_average_chain() noexcept {
    std::string data = "aaaaaaaaaaaaaaaabbbbbbbbccccdde";
    for(std::size_t i = 0; i < 5; i++) {
        data += data;
    }
    huffman_encoder huff_enc(data);
    DO_CHECK((huff_enc.get_code('a') == std::vector <bool>{1}));
    DO_CHECK((huff_enc.get_code('b') == std::vector <bool>{0, 1}));
    DO_CHECK((huff_enc.get_code('c') == std::vector <bool>{0, 0, 1}));
    DO_CHECK((huff_enc.get_code('d') == std::vector <bool>{0, 0, 0, 1}));
    DO_CHECK((huff_enc.get_code('e') == std::vector <bool>{0, 0, 0, 0}));
}

void huff_test::get_code_test_big_balanced() noexcept {
    std::string data = "123456789";
    for(std::size_t i = 0; i < 15; i++) {
        data += data;
    }
    huffman_encoder huff_enc(data);
    DO_CHECK((huff_enc.get_code('1') == std::vector <bool>{1, 1, 1, 0}));
    DO_CHECK((huff_enc.get_code('2') == std::vector <bool>{1, 1, 1, 1}));
    DO_CHECK((huff_enc.get_code('3') == std::vector <bool>{0, 0, 0}));
    DO_CHECK((huff_enc.get_code('4') == std::vector <bool>{0, 0, 1}));
    DO_CHECK((huff_enc.get_code('5') == std::vector <bool>{0, 1, 0}));
    DO_CHECK((huff_enc.get_code('6') == std::vector <bool>{0, 1, 1}));
    DO_CHECK((huff_enc.get_code('7') == std::vector <bool>{1, 0, 0}));
    DO_CHECK((huff_enc.get_code('8') == std::vector <bool>{1, 0, 1}));
    DO_CHECK((huff_enc.get_code('9') == std::vector <bool>{1, 1, 0}));
}

void huff_test::tree_encode_test_small() noexcept {
    std::string data = "abc";
    huffman_encoder huff_enc(data);
    DO_CHECK((huff_enc.tree_encode() == std::vector <u_short>{256, 97, 98, 257, 99, 256}));
}

void huff_test::tree_encode_test_average_balanced() noexcept {
    std::string data = "a bc aaaa bbbb cc";
    for(std::size_t i = 0; i < 5; i++) {
        data += data;
    }
    huffman_encoder huff_enc(data);
    DO_CHECK((huff_enc.tree_encode() == std::vector <u_short>{256, 99, 32, 257, 97, 98, 258, 256, 257}));
}

void huff_test::decode_test_small() noexcept {
    std::vector <u_short> tree = {256, 97, 98, 257, 99, 256};
    std::vector <bool> code = {1, 0, 1, 1, 0, 0, 1, 1, 1, 0};
    huffman_decoder huff_dec(tree, code);
    DO_CHECK((huff_dec.decode() == "abccba"));
}

void huff_test::decode_test_average_balanced() noexcept {
    std::vector <u_short> tree = {256, 99, 32, 257, 97, 98, 258, 256, 257};
    std::vector <bool> code = {1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 0, 1, 0, 0, 0, 0};
    for(std::size_t i = 0; i < 2; i++) {
        code.insert(code.end(), code.begin(), code.end());
    }
    huffman_decoder huff_dec(tree, code);
    DO_CHECK((huff_dec.decode() == "a bc aaaa bbbb cca bc aaaa bbbb cca bc aaaa bbbb cca bc aaaa bbbb cc"));
}

void huff_test::decode_test_big_chain() noexcept {
    std::vector <u_short> tree = {256, 101, 100, 257, 256, 99, 258, 257, 98, 259, 258, 97};
    std::vector <bool> code = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0,
    0, 0, 1, 0, 0, 0, 0};
    std::string answer = "aaaaaaaaaaaaaaaabbbbbbbbccccdde";
    for(std::size_t i = 0; i < 10; i++) {
        code.insert(code.end(), code.begin(), code.end());
        answer += answer;
    }
    huffman_decoder huff_dec(tree, code);
    DO_CHECK((huff_dec.decode() == answer));
}

void huff_test::read_write_u_short_test_0() noexcept {
    std::string dir = "testfile.bin";
    std::ofstream ofs(dir);
    ofs << write_uint <u_short>(0);
    ofs.close();

    std::ifstream ifs(dir);
    u_short d;
    ifs >> read_uint <u_short>(d);
    ifs.close();
    remove(dir.c_str());

    DO_CHECK((d == 0));
}

void huff_test::read_write_u_short_test_12334() noexcept {
    std::string dir = "testfile.bin";
    std::ofstream ofs(dir);
    ofs << write_uint <u_short>(12334);
    ofs.close();

    std::ifstream ifs(dir);
    u_short d;
    ifs >> read_uint <u_short>(d);
    ifs.close();
    remove(dir.c_str());

    DO_CHECK((d == 12334));
}

void huff_test::read_write_u_short_test_891() noexcept {
    std::string dir = "testfile.bin";
    std::ofstream ofs(dir);
    ofs << write_uint <u_short>(891);
    ofs.close();

    std::ifstream ifs(dir);
    u_short d;
    ifs >> read_uint <u_short>(d);
    ifs.close();
    remove(dir.c_str());

    DO_CHECK((d == 891));
}

void huff_test::read_write_vector_u_short_test_small() noexcept {
    std::string dir = "testfile.bin";
    std::ofstream ofs(dir);
    std::vector <u_short> d = {1, 2, 3, 4, 5};
    ofs << write_vector_uint <u_short>(d);
    ofs.close();

    std::ifstream ifs(dir);
    std::vector <u_short> read_d(d.size());
    ifs >> read_vector_uint <u_short>(read_d);
    ifs.close();
    remove(dir.c_str());

    DO_CHECK((d == read_d));
}

void huff_test::read_write_vector_test_u_short_test_average() noexcept {
    std::string dir = "testfile.bin";
    std::ofstream ofs(dir);
    std::vector <u_short> d;
    for(std::size_t i = 0; i < 10000; i++) {
        d.push_back(i);
    }
    ofs << write_vector_uint <u_short>(d);
    ofs.close();

    std::ifstream ifs(dir);
    std::vector <u_short> read_d(d.size());
    ifs >> read_vector_uint <u_short>(read_d);
    ifs.close();
    remove(dir.c_str());

    DO_CHECK((d == read_d));
}

void huff_test::read_write_vector_test_u_short_test_big() noexcept {
    std::string dir = "testfile.bin";
    std::ofstream ofs(dir);
    std::vector <u_short> d;
    for(std::size_t i = 0; i <= UINT16_MAX; i++) {
        d.push_back(UINT16_MAX - i);
    }
    ofs << write_vector_uint <u_short>(d);
    ofs.close();

    std::ifstream ifs(dir);
    std::vector <u_short> read_d(d.size());
    ifs >> read_vector_uint <u_short>(read_d);
    ifs.close();
    remove(dir.c_str());

    DO_CHECK((d == read_d));
}

void huff_test::read_write_string_test_small() noexcept {
    std::string dir = "testfile.bin";
    std::ofstream ofs(dir);
    std::string d = "a b c d";
    ofs << write_string(d);
    ofs.close();

    std::ifstream ifs(dir);
    std::string read_d = "";
    ifs >> read_unfixed_len_string(read_d);
    ifs.close();
    remove(dir.c_str());

    DO_CHECK((d == read_d));
}

void huff_test::read_write_string_test_average() noexcept {
    std::string dir = "testfile.bin";
    std::ofstream ofs(dir);
    std::string d = "a\n\n\nb";
    for(std::size_t i = 0; i < 10; i++) {
        d += d;
    }
    ofs << write_string(d);
    ofs.close();

    std::ifstream ifs(dir);
    std::string read_d = "";
    ifs >> read_unfixed_len_string(read_d);
    ifs.close();
    remove(dir.c_str());

    DO_CHECK((d == read_d));
}

void huff_test::read_write_string_test_big() noexcept {
    std::string dir = "testfile.bin";
    std::ofstream ofs(dir);
    std::string d = "ab cde fgh ";
    for(std::size_t i = 0; i < 17; i++) {
        d += d;
    }
    ofs << write_string(d);
    ofs.close();

    std::ifstream ifs(dir);
    std::string read_d = "";
    ifs >> read_unfixed_len_string(read_d);
    ifs.close();
    remove(dir.c_str());

    DO_CHECK((d == read_d));
}

void huff_test::read_write_vector_bool_small() noexcept {
    std::string dir = "testfile.bin";
    std::ofstream ofs(dir);
    std::vector <bool> d = {1};
    ofs << write_vector_bool(d);
    ofs.close();

    std::ifstream ifs(dir);
    std::vector <bool> read_d(d.size());
    ifs >> read_vector_bool(read_d);
    ifs.close();
    remove(dir.c_str());

    DO_CHECK((d == read_d));
}

void huff_test::read_write_vector_bool_average() noexcept {
    std::string dir = "testfile.bin";
    std::ofstream ofs(dir);
    std::vector <bool> d;
    for(std::size_t i = 0; i < 100000; i++) {
        d.push_back(i & 1);
    }
    ofs << write_vector_bool(d);
    ofs.close();

    std::ifstream ifs(dir);
    std::vector <bool> read_d(d.size());
    ifs >> read_vector_bool(read_d);
    ifs.close();
    remove(dir.c_str());

    DO_CHECK((d == read_d));
}

void huff_test::read_write_vector_bool_big() noexcept {
    std::string dir = "testfile.bin";
    std::ofstream ofs(dir);
    std::vector <bool> d;
    for(std::size_t i = 0; i < 1000000; i++) {
        d.push_back(i % 4 == 0);
    }
    ofs << write_vector_bool(d);
    ofs.close();

    std::ifstream ifs(dir);
    std::vector <bool> read_d(d.size());
    ifs >> read_vector_bool(read_d);
    ifs.close();
    remove(dir.c_str());

    DO_CHECK((d == read_d));
}

bool huff_test::check_data(const std::string& F, const std::string& S) noexcept {
    std::ifstream _F(F);
    std::ifstream _S(S);
    std::string _F_data = "";
    std::string _S_data = "";
    _F >> read_unfixed_len_string(_F_data);
    _S >> read_unfixed_len_string(_S_data);
    /*for(char ch: _F_data) {
        std::cerr << u_int(ch) << ' ';
    }
    for(char ch: _S_data) {
        std::cerr << u_int(ch) << ' ';
    }
    std::cerr << '\n';*/
    return _F_data == _S_data;
}

void huff_test::archive_unarchive_test_empty() noexcept {
    std::string src_arch_dir = "src_arch.bin";
    std::string dest_arch_dir = "dest_arch.bin";
    std::string dest_unarch_dir = "dest_unarch.bin";

    std::ofstream ofs(src_arch_dir);
    ofs.close();

    std::ifstream src_arch(src_arch_dir);
    std::ofstream dest_arch(dest_arch_dir);

    huffman_archiver arch;
    arch.archive(src_arch, dest_arch);

    dest_arch.close();

    std::ifstream src_unarch(dest_arch_dir);
    std::ofstream dest_unarch(dest_unarch_dir);

    huffman_archiver unarch;
    unarch.unarchive(src_unarch, dest_unarch);

    src_arch.close();
    src_unarch.close();
    dest_unarch.close();

    DO_CHECK((check_data(src_arch_dir, dest_unarch_dir)));

    remove(src_arch_dir.c_str());
    remove(dest_arch_dir.c_str());
    remove(dest_unarch_dir.c_str());
}

void huff_test::archive_unarchive_test_one_type_symbol() noexcept {
    std::string src_arch_dir = "src_arch.bin";
    std::string dest_arch_dir = "dest_arch.bin";
    std::string dest_unarch_dir = "dest_unarch.bin";

    std::ofstream ofs(src_arch_dir);
    for(std::size_t i = 0; i < 10; i++) {
        ofs.put(0);
    }
    ofs.close();

    std::ifstream src_arch(src_arch_dir);
    std::ofstream dest_arch(dest_arch_dir);

    huffman_archiver arch;
    arch.archive(src_arch, dest_arch);

    dest_arch.close();

    std::ifstream src_unarch(dest_arch_dir);
    std::ofstream dest_unarch(dest_unarch_dir);

    huffman_archiver unarch;
    unarch.unarchive(src_unarch, dest_unarch);

    src_arch.close();
    src_unarch.close();
    dest_unarch.close();

    DO_CHECK((check_data(src_arch_dir, dest_unarch_dir)));

    remove(src_arch_dir.c_str());
    remove(dest_arch_dir.c_str());
    remove(dest_unarch_dir.c_str());
}

void huff_test::archive_unarchive_test_small() noexcept {
    std::string src_arch_dir = "src_arch.bin";
    std::string dest_arch_dir = "dest_arch.bin";
    std::string dest_unarch_dir = "dest_unarch.bin";

    std::ofstream ofs(src_arch_dir);
    ofs.put('f');
    ofs.close();

    std::ifstream src_arch(src_arch_dir);
    std::ofstream dest_arch(dest_arch_dir);

    huffman_archiver arch;
    arch.archive(src_arch, dest_arch);

    dest_arch.close();

    std::ifstream src_unarch(dest_arch_dir);
    std::ofstream dest_unarch(dest_unarch_dir);

    huffman_archiver unarch;
    unarch.unarchive(src_unarch, dest_unarch);

    src_arch.close();
    src_unarch.close();
    dest_unarch.close();

    DO_CHECK((check_data(src_arch_dir, dest_unarch_dir)));

    remove(src_arch_dir.c_str());
    remove(dest_arch_dir.c_str());
    remove(dest_unarch_dir.c_str());
}

void huff_test::archive_unarchive_test_average() noexcept {
    std::string src_arch_dir = "src_arch.bin";
    std::string dest_arch_dir = "dest_arch.bin";
    std::string dest_unarch_dir = "dest_unarch.bin";

    std::ofstream ofs(src_arch_dir);
    for(std::size_t i = 0; i < 10000; i++) {
        ofs << write_uint <u_short>(i);
    }
    ofs.close();

    std::ifstream src_arch(src_arch_dir);
    std::ofstream dest_arch(dest_arch_dir);

    huffman_archiver arch;
    arch.archive(src_arch, dest_arch);

    dest_arch.close();

    std::ifstream src_unarch(dest_arch_dir);
    std::ofstream dest_unarch(dest_unarch_dir);

    huffman_archiver unarch;
    unarch.unarchive(src_unarch, dest_unarch);

    src_arch.close();
    src_unarch.close();
    dest_unarch.close();

    DO_CHECK((check_data(src_arch_dir, dest_unarch_dir)));

    remove(src_arch_dir.c_str());
    remove(dest_arch_dir.c_str());
    remove(dest_unarch_dir.c_str());
}

void huff_test::archive_unarchive_test_big() noexcept {
    std::string src_arch_dir = "src_arch.bin";
    std::string dest_arch_dir = "dest_arch.bin";
    std::string dest_unarch_dir = "dest_unarch.bin";

    std::ofstream ofs(src_arch_dir);
    for(std::size_t i = 0; i < 5 * 1000 * 1000; i++) {
        ofs << write_uint <u_short>(i % UINT16_MAX);
    }
    ofs.close();

    std::ifstream src_arch(src_arch_dir);
    std::ofstream dest_arch(dest_arch_dir);

    huffman_archiver arch;
    arch.archive(src_arch, dest_arch);

    dest_arch.close();

    std::ifstream src_unarch(dest_arch_dir);
    std::ofstream dest_unarch(dest_unarch_dir);

    huffman_archiver unarch;
    unarch.unarchive(src_unarch, dest_unarch);

    src_arch.close();
    src_unarch.close();
    dest_unarch.close();

    DO_CHECK((check_data(src_arch_dir, dest_unarch_dir)));

    remove(src_arch_dir.c_str());
    remove(dest_arch_dir.c_str());
    remove(dest_unarch_dir.c_str());
}

void huff_test::archive_unarchive_test_big_extra_symb() noexcept {
    std::string src_arch_dir = "src_arch.bin";
    std::string dest_arch_dir = "dest_arch.bin";
    std::string dest_unarch_dir = "dest_unarch.bin";

    std::ofstream ofs(src_arch_dir);
    std::string d = "\n\n\n  \r\r \t\'";
    for(std::size_t i = 0; i < 15; i++) {
        d += d;
    }
    ofs << write_string(d);
    ofs.close();

    std::ifstream src_arch(src_arch_dir);
    std::ofstream dest_arch(dest_arch_dir);

    huffman_archiver arch;
    arch.archive(src_arch, dest_arch);

    dest_arch.close();

    std::ifstream src_unarch(dest_arch_dir);
    std::ofstream dest_unarch(dest_unarch_dir);

    huffman_archiver unarch;
    unarch.unarchive(src_unarch, dest_unarch);

    src_arch.close();
    src_unarch.close();
    dest_unarch.close();

    DO_CHECK((check_data(src_arch_dir, dest_unarch_dir)));

    remove(src_arch_dir.c_str());
    remove(dest_arch_dir.c_str());
    remove(dest_unarch_dir.c_str());
}

void huff_test::run_all_tests() {
    get_code_test_small_balanced();
    get_code_test_average_chain();
    get_code_test_big_balanced();

    tree_encode_test_small();
    tree_encode_test_average_balanced();

    decode_test_small();
    decode_test_average_balanced();
    decode_test_big_chain();

    read_write_u_short_test_0();
    read_write_u_short_test_12334();
    read_write_u_short_test_891();

    read_write_vector_u_short_test_small();
    read_write_vector_test_u_short_test_average();
    read_write_vector_test_u_short_test_big();

    read_write_string_test_small();
    read_write_string_test_average();
    read_write_string_test_big();

    read_write_vector_bool_small();
    read_write_vector_bool_average();
    read_write_vector_bool_big();

    archive_unarchive_test_empty();
    archive_unarchive_test_one_type_symbol();
    archive_unarchive_test_small();
    archive_unarchive_test_average();
    archive_unarchive_test_big();
    archive_unarchive_test_big_extra_symb();
}
