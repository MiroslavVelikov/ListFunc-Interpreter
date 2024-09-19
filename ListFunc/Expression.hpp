#pragma once
#include <fstream>

enum class ExpressionType {
	UNKNOWN,
	REAL_NUMBER,
	LIST_LITERAL,
	LIST_INFINITY,
	PLACEHOLDER,
	FUNCTION,
	EMBEDDED_FUNCTION
};

class RealNumber;

class BaseList {
public:
	BaseList() = default;
	virtual ~BaseList() = default;

	virtual RealNumber operator[](size_t index) const = 0;
};

class Expression {
public:
	Expression(ExpressionType type) : type(type) {};
	virtual ~Expression() = 0;

	ExpressionType getType() const {
		return type;
	}

private:
	ExpressionType type;
};

inline Expression::~Expression() {}

class Variable : public Expression {
public:
	Variable(ExpressionType type) : Expression(type) {}
	virtual ~Variable() = default;

	virtual bool operator!() const = 0;
};

class Comparable : public Variable {
public:
	Comparable(ExpressionType type) : Variable(type) {};
	virtual ~Comparable() = default;

	virtual void print(std::ostream&) const = 0;

	virtual bool operator==(const Comparable* other) const = 0;

	virtual bool operator==(const class RealNumber*) const { return false; }
	virtual bool operator==(const class ListLiteral*) const { return false; }
};