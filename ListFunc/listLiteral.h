#pragma once
#include "expression.h"
#include <vector>

class listLiteral : public expression {
public:
	listLiteral(const std::vector<expression*>& elements);
	~listLiteral();

	const expression* at(size_t index) const;
	expression* clone() const override {
		return new listLiteral(*this);
	}

	listLiteral* tail() const {
		if (elements.empty()) return new listLiteral(std::vector<expression*>());

		return new listLiteral(std::vector<expression*>(elements.begin() + 1, elements.end()));
	}

	listLiteral* operator+(const listLiteral& rhs) const {
		std::vector<expression*> result(elements);

		for (size_t i = 0; i < rhs.elements.size(); ++i) {
			result.push_back(rhs.elements[i]);
		}

		return new listLiteral(result);
	}

private:
	std::vector<expression*> elements;
};