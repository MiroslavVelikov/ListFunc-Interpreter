#pragma once
#include "Expression.h"

class RealNumber : public Expression {
public:
	RealNumber(const std::string& name, double value)
		: Expression(name, ExpressionType::REAL_NUMBER), value(value) {}

	~RealNumber() = default;

	double getValue() const {
		return value;
	}

private:
	double value;
};