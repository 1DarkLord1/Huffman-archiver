#pragma once

#include <cstring>
#include <iostream>
#include "huffman.h"
#include "huffman_exception.h"

class handler {
private:
    static const int args_count = 6;
    static const int BAD_ACTION_TYPE = -1;
    static const int ARCH = 0;
    static const int UNARCH = 1;
    
    int _argc;
    char** _argv;

public:
    handler(int __argc, char** __argv) noexcept;
    void execute() const;

private:
    int get_action_type() const noexcept;
    bool check_f_argument() const noexcept;
    bool check_o_argument() const noexcept;
};
