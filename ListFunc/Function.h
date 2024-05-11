#pragma once
#include "Expression.h"
#include "ListLiteral.hpp"

class Function : public Expression {
public:
	
private:
	ListLiteral<Expression> d;
};