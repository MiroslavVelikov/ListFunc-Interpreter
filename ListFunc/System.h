#pragma once
#include <iostream>
#include "oaHashTable.hpp"
#include "Expression.hpp"
#include <string>
#include <sstream>
#include "Operation.hpp"
#include "RealNumber.h"
#include "Placeholder.hpp"
#include "Function.h"
#include "EmbeddedFunctions.hpp"

enum class SystemMode {
	INVALID_MODE,
	CREATE_FUNCTION,
	EXECUTE_FUNCTION,
	OPEN_FILE
};

class System {
private:
	System();

	typedef OOHashTable<std::string, Expression*>::iterator iterator_t;

public:
	~System();

	System(const System&) = delete;
	System& operator=(const System&) = delete;
		
	static System& getInstance();
	void startProgram();

private:
	Expression* createFunction(const std::string& funcName, const std::string& expression, bool& existingFlag);

	void buildOperation(std::vector<std::string>& order, size_t& argsCount, Operation*& operation);
	void joinOperation(Operation*& operation, Expression* expr, bool isIf = false) const;

	Expression* executeFunction(const std::string& functionName, const std::vector<std::string>& arguments);
	Expression* executeFunction(const Function* func) const;

	bool isNumber(const std::string& str) const;
	void fillOrder(std::vector<std::string>& order, const std::string& str, size_t& argsCount) const;
	std::vector<std::string>& splitBySpace(const std::string& str) const;
	std::string popFirstWord(std::string& str) const;

private:
	OOHashTable<std::string, Expression*> data;
};