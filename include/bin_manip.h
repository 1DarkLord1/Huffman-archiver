#pragma once

#include <fstream>
#include <cstdint>
#include <cstddef>
#include <vector>
#include <climits>

template <typename T>
struct read_uint {
    read_uint(T& _data) noexcept: data(_data) {}
    template <typename V> friend std::ifstream& operator>>(std::ifstream&, const read_uint <V>&);
private:
    T& data;
};

template <typename T>
struct write_uint {
    write_uint(T _data) noexcept: data(_data) {}
    template <typename V> friend std::ofstream& operator<<(std::ofstream&, const write_uint <V>&);
private:
    T data;
};

template <typename T>
struct write_vector_uint {
    write_vector_uint(const std::vector <T>& _data) noexcept: data(_data) {}
    template <typename V> friend std::ofstream& operator<<(std::ofstream&, const write_vector_uint <V>&);
private:
    const std::vector <T>& data;
};

template <typename T>
struct read_vector_uint {
    read_vector_uint(std::vector <T>& _data) noexcept: data(_data) {}
    template <typename V> friend std::ifstream& operator>>(std::ifstream&, const read_vector_uint <V>&);
private:
    std::vector <T>& data;
};

struct write_string {
    write_string(const std::string& _data) noexcept: data(_data) {}
    friend std::ofstream& operator<<(std::ofstream&, const write_string&);
private:
    const std::string& data;
};

struct read_unfixed_len_string {
    read_unfixed_len_string(std::string& _data) noexcept: data(_data) {}
    friend std::ifstream& operator>>(std::ifstream&, const read_unfixed_len_string&);
private:
    std::string& data;
};

struct write_vector_bool {
    write_vector_bool(const std::vector <bool>& _data) noexcept: data(_data) {}
    friend std::ofstream& operator<<(std::ofstream&, const write_vector_bool&);
private:
    const std::vector <bool>& data;
};

struct read_vector_bool {
    read_vector_bool(std::vector <bool>& _data) noexcept: data(_data) {}
    friend std::ifstream& operator>>(std::ifstream&, const read_vector_bool&);
private:
    std::vector <bool>& data;
};


template <typename T>
std::ofstream& operator<<(std::ofstream& ofs, const write_uint <T>& d) {
	static_assert(CHAR_BIT == 8);
	for (std::size_t i = 0; i < sizeof(d.data); ++i) {
		char chunk = (d.data >> (i * CHAR_BIT)) & 0xFF;
		ofs.write(&chunk, sizeof(char));
	}
	return ofs;
}

template <typename T>
std::ifstream& operator>>(std::ifstream& ifs, const read_uint <T> &d) {
	static_assert(CHAR_BIT == 8);
	d.data = 0;
	for (std::size_t i = 0; i < sizeof(d.data); ++i) {
		char chunk = 0;
		ifs.read((char *)&chunk, sizeof(char));
		d.data |= (unsigned char)(chunk) << (i * CHAR_BIT);
	}
	return ifs;
}

template <typename T>
std::ofstream& operator<<(std::ofstream& ofs, const write_vector_uint <T>& d) {
	for(T num: d.data) {
		ofs << write_uint <T>(num);
	}
	return ofs;
}

template <typename T>
std::ifstream& operator>>(std::ifstream& ifs, const read_vector_uint <T>& d) {
	for(T& num: d.data) {
		ifs >> read_uint <T>(num);
	}
	return ifs;
}
