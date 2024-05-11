#include "Expression.h"

Expression::Expression(const std::string& name, ExpressionType type) {
	setType(type);
	setName(name);
}

const std::string& Expression::getName() const {
	return name;
}

ExpressionType Expression::getType() const {
	return type;
}

void Expression::setName(const std::string& value) {
	// Add validation if needed
	name = value;
}

void Expression::setType(ExpressionType value) {
	type = value;
}