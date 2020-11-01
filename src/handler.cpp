#include "handler.h"

using namespace huff_arch;

handler::handler(int __argc, char** __argv) noexcept: _argc(__argc), _argv(__argv) {}

int handler::get_action_type() const noexcept{
    if(strcmp(_argv[1], "-c") != 0 && strcmp(_argv[1], "-u") != 0) {
        return BAD_ACTION_TYPE;
    }
    return (strcmp(_argv[1], "-c") == 0 ? ARCH: UNARCH);
}
bool handler::check_f_argument() const noexcept {
    return (strcmp(_argv[2], "-f") == 0 || strcmp(_argv[2], "--file") == 0);
}

bool handler::check_o_argument() const noexcept {
    return (strcmp(_argv[4], "-o") == 0 || strcmp(_argv[4], "--output") == 0);
}

void handler::execute() const {
    if(_argc != args_count) {
        throw huff_exception("Invalid count of arguments");
    }
    if(!check_f_argument()) {
        throw huff_exception((std::string("Invalid argument ") + _argv[2]).c_str());
    }
    if(!check_o_argument()) {
        throw huff_exception((std::string("Invalid argument ") + _argv[4]).c_str());
    }

    int action_type = get_action_type();
    if(action_type == BAD_ACTION_TYPE) {
        throw huff_exception((std::string("Invalid argument ") + _argv[1]).c_str());
    }

    std::ifstream src(_argv[3]);
    if(!src) {
        throw huff_exception((std::string("Error with opening file ") + _argv[3] + " (maybe this file doesn't exist)").c_str());
    }
    std::ofstream dest(_argv[5]);
    huffman_archiver arch;

    if(action_type == ARCH) {
        arch.archive(src, dest);
        std::cout << arch.get_data_size() << std::endl << arch.get_encd_data_size() << std::endl;
    }
    else{
        arch.unarchive(src, dest);
        std::cout << arch.get_encd_data_size() << std::endl << arch.get_data_size() << std::endl;
    }
    std::cout << arch.get_extra_data_size() << std::endl;
}
