#pragma once
#include <string>
#include "expression.h"
#include <vector>

class functionDeclaration {
public:
	functionDeclaration(const std::string& name, expression const * body)
		: name(name), body(body) {}

	expression* evaluate(const std::vector<expression*>& args) const;

private:
	std::string name;
	expression const * body;
};