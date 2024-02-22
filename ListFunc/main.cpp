#include <iostream>
#include "realNumber.h"
#include "listLiteral.h"
#include "placeHolder.h"
#include "oaHashTable.hpp"
#include "embeddedListFuncs.hpp"
#include "embeddedNumFuncs.hpp"
#include <string>

struct Print {
	void operator()(int a) {
		std::cout << a;
	}
};

struct A {
	size_t operator()(size_t a) const {
		return a;
	}
};

int main() {
	

	return 0;
}