#pragma once
#include "expression.h"
#include <vector>

struct embedded : public expression{
public:
	embedded() : expression(ExpressionType::EMBEDDED) {}

	virtual expression* evaluate(const std::vector<expression*>& args) const = 0;
};