#pragma once
#include "oaHashTable.hpp"
#include "functionDeclaration.hpp"
#include "functionCall.h"

class functionEnvironment {
private:
	struct funcHasher {
		size_t operator()(const std::string& name) {
			size_t result = 0;

			for (char sym : name) {
				result += sym;
			}

			return result;
		}
	};

	functionEnvironment() = default;
	~functionEnvironment() {
		///...
	}
public:
	functionEnvironment(const functionEnvironment&) = delete;
	functionEnvironment& operator=(const functionEnvironment&) = delete;

	static functionEnvironment& getInstance() {
		static functionEnvironment functionEnvironment;
		return functionEnvironment;
	}

	bool find(const std::string& key) const {
		return functions.find(key);
	}

	expression* get(const std::string& key) {
		try {
			return functions.get(key);
		}
		catch (const std::invalid_argument&) {
			return nullptr;
		}
	}

private:
	oaHashTable<std::string, expression*, funcHasher> functions = oaHashTable<std::string, expression*, funcHasher>(funcHasher{});
};