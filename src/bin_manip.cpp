#include "bin_manip.h"

static int char_bit() noexcept {
	int cnt = 1;
	char ch = 1;
	while(ch <<= 1) {
		cnt++;
	}
	return cnt;
}

std::ofstream& operator<<(std::ofstream& ofs, const write_string& d) {
	for(char ch: d.data) {
		ofs.put(ch);
	}
	return ofs;
}

std::ifstream& operator>>(std::ifstream& ifs, const read_unfixed_len_string& d) {
	char ch;
 	while(ifs.get(ch)) {
		d.data += ch;
	}
	return ifs;
}


std::ofstream& operator<<(std::ofstream& ofs, const write_vector_bool& d) {
	auto char_fill = [](char& ch, std::vector <bool>::const_iterator first,
		std::vector <bool>::const_iterator last) {
		ch = 0;
		for(auto It = first; It != last; It++){
			ch |= ((1 << (It - first)) * (*It));
		}
	};
	char ch;
	int bit_cnt = char_bit();
	for(auto It = d.data.begin(); It != d.data.end(); It = std::min(It + bit_cnt, d.data.end())) {
		char_fill(ch, It, std::min(It + bit_cnt, d.data.end()));
		ofs.put(ch);
	}
	return ofs;
}

std::ifstream& operator>>(std::ifstream& ifs, const read_vector_bool& d) {
	auto char_inserter = [](char ch, std::vector <bool>::iterator first,
		std::vector <bool>::iterator last) {
			for(auto It = first; It != last; It++) {
			*It = ((ch >> (It - first)) & 1);
		}
	};
	char ch;
	int bit_cnt = char_bit();
	for(auto It = d.data.begin(); It != d.data.end(); It = std::min(It + bit_cnt, d.data.end())) {
		ifs.get(ch);
		char_inserter(ch, It, std::min(It + bit_cnt, d.data.end()));
	}
	return ifs;
}
