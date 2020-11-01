#include "handler.h"

int main(int argc, char** argv) {
    handler hnd(argc, argv);
    try {
        hnd.execute();
    }
    catch(const huff_arch::huff_exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
