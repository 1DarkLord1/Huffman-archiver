#include "huffman_exception.h"

using namespace huff_arch;

huff_exception::huff_exception(const char* _msg) noexcept: std::logic_error(_msg) {}
