#pragma once
#include "expression.h"

class realNumber : public expression {
public:
	realNumber(double value);
	~realNumber() = default;

	double getValue() const;
	expression* clone() const override {
		return new realNumber(*this);
	}

private:
	double value;
};

inline realNumber::realNumber(double value)
	: expression(ExpressionType::REAL_NUMBER), value(value) {}

inline double realNumber::getValue() const {
	return value;
}