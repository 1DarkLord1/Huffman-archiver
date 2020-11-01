#include <cstdio>
#include "autotest.h"

int Test::failedNum = 0;
int Test::totalNum = 0;

void Test::check(bool expr, const char* func, const char* filename, size_t lineNum) {
	totalNum++;
	if (expr) {
		printf("Test #%d: OK\n", totalNum);
	}
	else {
		failedNum++;
		printf("Test #%d: FAILED\n", totalNum);
		printf("In file %s, function %s, line %zu\n", filename, func, lineNum);
	}
}

void Test::show_final_result() {
	if (failedNum == 0) {
		printf("All %d tests passed\n", totalNum);
	}
	else{
		printf("Failed %d / %d tests\n", failedNum, totalNum);
	}
}
