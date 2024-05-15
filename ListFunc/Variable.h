#pragma once
#include "Expression.hpp"
#include <string>

class Variable {
public:
	Variable(const std::string& name, const Expression& expression)
		: expression(expression.clone()) {
		
	}

private:
	std::string name;
	Expression* expression;
};