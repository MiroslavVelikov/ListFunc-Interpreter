#pragma once
#include "Expression.hpp"
#include "RealNumber.h"
#include <iostream>

class ListInfinity : public Expression, BaseList {
public:
	ListInfinity(double num, double step = 1)
		: Expression(ExpressionType::LIST_INFINITY),
			start(num), step(step) {}

	int getSize() const {
		return -1;
	}

	virtual RealNumber operator[](size_t index) const override {
		return RealNumber(start + (index * step));
	}

private:
	double start;
	double step;
};