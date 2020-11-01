#pragma once

#include <stdexcept>

namespace huff_arch {

class huff_exception: public std::logic_error {
public:
	huff_exception(const char* _msg) noexcept;
};

}
