#include "RealNumber.h"

RealNumber::RealNumber(double value)
	: Comparable(ExpressionType::REAL_NUMBER), value(value) {}

double RealNumber::getValue() const {
	return value;
}

bool RealNumber::operator==(const Comparable* other) const {
	return *other == this;
}

bool RealNumber::operator!() const {
	return !value;
}

void RealNumber::print(std::ostream& os) const {
	os << value;
}

bool RealNumber::operator==(const RealNumber* other) const {
	return value == other->value;
}

bool RealNumber::operator==(const ListLiteral* other) const {
	return (const Expression*)other == this;
}
