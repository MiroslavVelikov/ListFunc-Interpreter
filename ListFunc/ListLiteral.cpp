#include "ListLiteral.h"

ListLiteral::ListLiteral(const std::vector<const RealNumber*> data)
	: Comparable(ExpressionType::LIST_LITERAL),
	data(data) {}

size_t ListLiteral::getSize() const {
	return data.size();
}

RealNumber ListLiteral::operator[](size_t index) const {
	return *data[index];
}

bool ListLiteral::operator==(const Comparable* other) const {
	return other == this;
}

bool ListLiteral::operator!() const {
	return !getSize();
}

void ListLiteral::print(std::ostream& os) const {
	os << '[';

	for (const RealNumber* rn : data) {
		rn->print(os);
		os << ' ';
	}

	os << "]\n";
}

bool ListLiteral::operator==(const RealNumber* other) const {
	if (getSize() != 1) {
		return false;
	}

	return *data[0] == (Comparable*)this;
}

bool ListLiteral::operator==(const ListLiteral* other) const {
	if (getSize() != other->getSize()) {
		return false;
	}

	for (size_t i = 0; i < getSize(); ++i) {
		if (data[i] != other->data[i]) {
			return false;
		}
	}

	return true;
}