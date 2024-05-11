#pragma once
#include "Expression.h"
#include <stdexcept> // invalid_argument

class Placeholder : public Expression {
public:
	Placeholder(const std::string& argumentNumber) 
		: Expression(argumentNumber, ExpressionType::PLACEHOLDER) {}

	~Placeholder() = default;

	int getValue() const {
		const std::string* str = &getName();
		
		if (str->at(0) == '#' && str->length() > 1)
			return std::atoi(str->c_str() + 1);
	
		throw std::invalid_argument("Invalid placeholder value\n");
	}
};