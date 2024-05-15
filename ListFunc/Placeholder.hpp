#pragma once
#include "Expression.hpp"

class Placeholder : public Expression {
public:
	Placeholder(size_t index)
		: Expression(ExpressionType::PLACEHOLDER), index(index) {}

	virtual Expression* clone() const override {
		return new Placeholder(*this);
	}

	size_t getIndex() const {
		return index;
	}

private:
	size_t index;
};