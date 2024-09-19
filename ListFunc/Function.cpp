#include "Function.h"

Function::Function(const std::string& funcName, Operation* operation, size_t requiredArgs)
	: Expression(ExpressionType::FUNCTION),
	funcName(funcName),
	operationOrder(operation),
	requiredArgs(requiredArgs) {}

Function::~Function() {
	delete operationOrder;
	operationOrder = nullptr;
	requiredArgs = 0;
}

Expression* Function::evaluateEmbeddedFun(const BaseEmbedded* func, Stack<Expression*>& args) const {
	if (func->getEmbType() == EmbeddedType::IF) {

	}
	else if (func->getEmbType() == EmbeddedType::NAND) {

	}
	else {
		Expression* result = func->callFunction(args);
		return result;
	}
}

void Function::setOperations(Operation* operation) {
	operationOrder = operation;
}

void Function::setArguments(size_t argsCount) {
	requiredArgs = argsCount;
}

Expression* Function::operator()(const std::vector<Expression*>& args) const {
	Operation* currenOperation = operationOrder;

	std::vector<Expression*> forDestruction;
	Stack<Expression*> operations;

	while (currenOperation->expr) {
		if (currenOperation->expr->getType() == ExpressionType::FUNCTION) {
			Function* func = (Function*)currenOperation->expr;
			std::vector<Expression*> args;

			for (size_t i = 0; i < func->requiredArgs; ++i) {
				args.push_back(operations.pop());
			}

			operations.push((*func)(args));
			forDestruction.push_back(operations.top());
		}
		else if (currenOperation->expr->getType() == ExpressionType::EMBEDDED_FUNCTION) {
			BaseEmbedded* embedFunc = (BaseEmbedded*)currenOperation->expr;
			Expression* result = evaluateEmbeddedFun(embedFunc, operations);

			operations.push(result);
			forDestruction.push_back(result);
		}
		else if (currenOperation->expr->getType() == ExpressionType::PLACEHOLDER) {
			Placeholder* ph = (Placeholder*)operationOrder->expr;
			size_t index = ph->getIndex();

			if (args.size() < index) {
				throw std::invalid_argument("Invalid argument\n");
			}

			operations.push(args[index]);
		}
		else {
			operations.push(currenOperation->expr);
		}

		currenOperation = currenOperation->operations[1];
	}

	for (size_t i = 0; i < forDestruction.size() - 1; ++i) {
		delete forDestruction[i];
	}

	if (operations.getSize() != 1) {
		throw std::invalid_argument("Invalid result\n");
	}

	return operations.pop();
}

