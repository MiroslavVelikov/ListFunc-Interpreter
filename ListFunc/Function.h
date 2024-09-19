#pragma once
#include "Expression.hpp"
#include "ListLiteral.h"
#include <string>
#include "Operation.hpp"
#include "Stack.hpp"
#include "EmbeddedFunctions.hpp"
#include "Placeholder.hpp"

class Function : public Expression {
public:
	Function(const std::string& funcName = "", Operation* operation = nullptr, size_t requiredArgs = 0);
	~Function();

	void setOperations(Operation* operation);
	void setArguments(size_t argsCount);

	Expression* operator()(const std::vector<Expression*>& args) const;

private:
	Expression* evaluateEmbeddedFun(const class BaseEmbedded* func, Stack<Expression*>& args) const;

private:
	std::string funcName;
	Operation* operationOrder;
	size_t requiredArgs;
};