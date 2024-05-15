#pragma once
#include "Expression.hpp"
#include "ListLiteral.hpp"


class Function : public Expression {
public:
	Function(const char* expression);



private:
	ListLiteral<Expression> args;
};