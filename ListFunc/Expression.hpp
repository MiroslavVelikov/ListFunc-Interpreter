#pragma once

enum class ExpressionType {
	UNKNOWN,
	REAL_NUMBER,
	LIST_LITERAL,
	PLACEHOLDER,
	FUNCTION,
	STATIC_FUNCTION,
};

class Expression {
public:
	Expression(ExpressionType type) : type(type) {};

	virtual Expression* clone() const = 0;

	ExpressionType getType() const {
		return type;
	}

private:
	ExpressionType type;
};