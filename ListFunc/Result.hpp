#pragma once
#include "Expression.h"

class Result : private Expression {
public:
	Result(double value) 
		: Expression("", ExpressionType::RESULT), value(value) {}

	double getValue() const {
		return value;
	}

	ExpressionType getType() const {
		return Expression::getType();
	}

private:
	double value;
};