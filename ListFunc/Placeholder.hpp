#pragma once
#include "Expression.hpp"

class Placeholder : public Expression {
public:
	Placeholder(size_t index)
		: Expression(ExpressionType::PLACEHOLDER), index(index) {}

	size_t getIndex() const {
		return index;
	}

private:
	size_t index;
};