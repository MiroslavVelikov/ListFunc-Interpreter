#pragma once

enum class ExpressionType {
	UNKOWN,
	REAL_NUMBER,
	PLACE_HOLDER,
	LIST_LITERAL,
	INFINITE_LIST,
	FUNCTION_CALL,
	EMBEDDED
};

class expression {
public:
	expression(ExpressionType type) : type(type) {}
	virtual ~expression() = 0;

	ExpressionType getType() const {
		return type;
	}
	virtual expression* clone() const = 0;

private:
	ExpressionType type;
};

inline expression::~expression() = default;