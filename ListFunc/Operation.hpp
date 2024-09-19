#pragma once
#include "Expression.hpp"

struct Operation {
	typedef Operation* Operations;

	Expression* expr;

	// Index 0: previous operation
	// Index 1: next operation
	// Expression IF -> Index 1 = True Line And Index 2 = False Line
	Operations* operations;
	size_t size;

	Operation(bool isIf = false) : expr(nullptr), size(2) {
		if (isIf) {
			++size;
		}

		operations = new Operations[size] { nullptr };
	}

	~Operation() {
		expr = nullptr;

		for (size_t i = 0; i < size; ++i) {
			if (operations[i]) {
				operations[i]->operations[0] = nullptr;
				delete operations[i];
			}
		}

		delete[] operations;
		operations = nullptr;
	}
};