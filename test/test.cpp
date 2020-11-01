#include "huffman_test.h"
#include "autotest.h"

int main() {
	huff_test ht;
	ht.run_all_tests();
	Test::show_final_result();
	return 0;
}
