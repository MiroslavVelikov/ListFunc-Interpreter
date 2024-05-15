#pragma once
#include "Expression.hpp"

class RealNumber : public Expression {
public:
	RealNumber(double value)
		: Expression(ExpressionType::REAL_NUMBER), value(value) {}

	virtual Expression* clone() const override {
		return new RealNumber(*this);
	}

	double getValue() const {
		return value;
	}

private:
	double value;
};