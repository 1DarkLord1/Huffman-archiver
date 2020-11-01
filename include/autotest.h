#pragma once

#include <cstddef>
#define DO_CHECK(EXPR) check(EXPR, __func__, __FILE__, __LINE__)

class Test {
protected:
	static int failedNum;
	static int totalNum;

public:
	static void show_final_result();
	virtual void run_all_tests() = 0;

protected:
	static void check(bool expr, const char* func, const char* filename, size_t lineNum);
};
