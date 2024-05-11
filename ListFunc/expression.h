#pragma once
#include <string>

enum class ExpressionType {
	UNKNOWN,
	REAL_NUMBER,
	LIST_FUNCTION,
	PLACEHOLDER,
	FUNCTION,
	STATIC_FUNCTION,
	RESULT
};

class Expression {
public:
	Expression(const std::string& name, ExpressionType type);
	virtual ~Expression() = 0;

	const std::string& getName() const;

	ExpressionType getType() const;

private:
	void setName(const std::string& value);
	void setType(ExpressionType type);

private:
	std::string name;
	ExpressionType type;
};