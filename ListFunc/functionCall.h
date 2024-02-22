#pragma once
#include "expression.h"
#include <vector>
#include <string>

class functionCall : public expression {
public:
	functionCall(const std::string& body);
	~functionCall();

	expression* evaluate(const std::vector<expression*>& params) const;
	
	expression* clone() const override {
		return new functionCall(*this);
	}
	
private:
	size_t getEndPos(const std::string& expr, size_t pos = 0) const {
		size_t byComma = expr.find(',', pos);
		size_t byClBracket = expr.find(')', pos);

		return byComma > byClBracket ? byClBracket : byComma;
	}

	void skipBracket(const std::string& expr, size_t& it) const {
		int opBracket = 1;

		while (it < expr.length() && opBracket) {
			if (expr[it] == '(') ++opBracket;
			else if (expr[it] == ')') --opBracket;

			++it;
		}
	}

private:
	size_t placeHolderCount;
	std::vector<expression*> args; // It might be better if it is poiters to declarations so i can search them inside hash table
};